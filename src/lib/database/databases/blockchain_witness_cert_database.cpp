/**
 * Copyright (c) 2011-2021 libbitcoin developers (see AUTHORS)
 * Copyright (c) 2016-2021 metaverse core developers (see MVS-AUTHORS)
 *
 * This file is part of metaverse.
 *
 * metaverse is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License with
 * additional permissions to the one published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version. For more information see LICENSE.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include <metaverse/database/databases/blockchain_witness_cert_database.hpp>

#include <cstddef>
#include <cstdint>
#include <memory>
#include <boost/filesystem.hpp>
#include <metaverse/bitcoin.hpp>
#include <metaverse/database/memory/memory.hpp>

namespace libbitcoin {
namespace database {

using namespace boost::filesystem;

BC_CONSTEXPR size_t number_buckets = 997;
BC_CONSTEXPR size_t header_size = slab_hash_table_header_size(number_buckets);
BC_CONSTEXPR size_t initial_map_file_size = header_size + minimum_slabs_size;

blockchain_witness_cert_database::blockchain_witness_cert_database(const path& map_filename,
    std::shared_ptr<shared_mutex> mutex)
  : lookup_file_(map_filename, mutex),
    lookup_header_(lookup_file_, number_buckets),
    lookup_manager_(lookup_file_, header_size),
    lookup_map_(lookup_header_, lookup_manager_)
{
}

// Close does not call stop because there is no way to detect thread join.
blockchain_witness_cert_database::~blockchain_witness_cert_database()
{
    close();
}

// Create.
// ----------------------------------------------------------------------------

// Initialize files and start.
bool blockchain_witness_cert_database::create()
{
    // Resize and create require a started file.
    if (!lookup_file_.start())
        return false;

    // This will throw if insufficient disk space.
    lookup_file_.resize(initial_map_file_size);

    if (!lookup_header_.create() ||
        !lookup_manager_.create())
        return false;

    // Should not call start after create, already started.
    return
        lookup_header_.start() &&
        lookup_manager_.start();
}

// Startup and shutdown.
// ----------------------------------------------------------------------------

// Start files and primitives.
bool blockchain_witness_cert_database::start()
{
    return
        lookup_file_.start() &&
        lookup_header_.start() &&
        lookup_manager_.start();
}

// Stop files.
bool blockchain_witness_cert_database::stop()
{
    return lookup_file_.stop();
}

// Close files.
bool blockchain_witness_cert_database::close()
{
    return lookup_file_.close();
}

// ----------------------------------------------------------------------------

void blockchain_witness_cert_database::remove(const hash_digest& hash)
{
    DEBUG_ONLY(bool success =) lookup_map_.unlink(hash);
    BITCOIN_ASSERT(success);
}

void blockchain_witness_cert_database::sync()
{
    lookup_manager_.sync();
}

std::shared_ptr<chain::blockchain_cert> blockchain_witness_cert_database::get(const hash_digest& hash) const
{
    std::shared_ptr<chain::blockchain_cert> detail(nullptr);

    const auto raw_memory = lookup_map_.find(hash);
    if (raw_memory) {
        const auto memory = REMAP_ADDRESS(raw_memory);
        detail = std::make_shared<chain::blockchain_cert>();
        auto deserial = make_deserializer_unsafe(memory);
        detail->from_data(deserial);
    }

    return detail;
}

std::shared_ptr<std::vector<chain::blockchain_cert>> blockchain_witness_cert_database::get_certs() const
{
    auto vec_acc = std::make_shared<std::vector<chain::blockchain_cert>>();
    for( uint64_t i = 0; i < number_buckets; i++ ) {
        auto memo = lookup_map_.find(i);
        if (memo->size()) {
            const auto action = [&](memory_ptr elem)
            {
                const auto memory = REMAP_ADDRESS(elem);
                auto deserial = make_deserializer_unsafe(memory);
                vec_acc->push_back(chain::blockchain_cert::factory_from_data(deserial));
            };
            std::for_each(memo->begin(), memo->end(), action);
        }
    }
    return vec_acc;
}

void blockchain_witness_cert_database::store(const chain::blockchain_cert& bc_cert)
{
    auto&& key_str = bc_cert.get_cert().get_key();
    const data_chunk& data = data_chunk(key_str.begin(), key_str.end());
    const auto key = sha256_hash(data);

#ifdef MVS_DEBUG
    log::debug("blockchain_witness_cert_database::store") << bc_cert.to_string();
#endif

    // Write block data.
    const auto sp_size = bc_cert.serialized_size();
    BITCOIN_ASSERT(sp_size <= max_size_t);
    const auto value_size = static_cast<size_t>(sp_size);

    auto write = [bc_cert](memory_ptr data)
    {
        auto serial = make_serializer(REMAP_ADDRESS(data));
        serial.write_data(bc_cert.to_data());
    };
    lookup_map_.store(key, write, value_size);
}


} // namespace database
} // namespace libbitcoin
