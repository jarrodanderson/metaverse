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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef MVS_MESSAGE_INVENTORY_HPP
#define MVS_MESSAGE_INVENTORY_HPP

#include <cstddef>
#include <cstdint>
#include <initializer_list>
#include <istream>
#include <memory>
#include <string>
#include <metaverse/bitcoin/define.hpp>
#include <metaverse/bitcoin/math/hash.hpp>
#include <metaverse/bitcoin/message/inventory_vector.hpp>
#include <metaverse/bitcoin/utility/data.hpp>
#include <metaverse/bitcoin/utility/reader.hpp>
#include <metaverse/bitcoin/utility/writer.hpp>

namespace libbitcoin {
namespace message {

class BC_API inventory
{
public:
    typedef std::shared_ptr<inventory> ptr;
    typedef inventory_vector::type_id type_id;

    static inventory factory_from_data(uint32_t version,
        const data_chunk& data);
    static inventory factory_from_data(uint32_t version, std::istream& stream);
    static inventory factory_from_data(uint32_t version, reader& source);

    inventory();
    inventory(const inventory_vector::list& values);
    inventory(const hash_list& hashes, type_id type);
    inventory(const std::initializer_list<inventory_vector>& values);

    virtual ~inventory() {}

    virtual bool from_data(uint32_t version, const data_chunk& data);
    virtual bool from_data(uint32_t version, std::istream& stream);
    virtual bool from_data(uint32_t version, reader& source);
    data_chunk to_data(uint32_t version) const;
    void to_data(uint32_t version, std::ostream& stream) const;
    void to_data(uint32_t version, writer& sink) const;
    void to_hashes(hash_list& out, type_id type) const;
    void reduce(inventory_vector::list& out, type_id type) const;
    bool is_valid() const;
    void reset();
    uint64_t serialized_size(uint32_t version) const;
    size_t count(type_id type) const;

    static const std::string command;
    static const uint32_t version_minimum;
    static const uint32_t version_maximum;

    inventory_vector::list inventories;
};

BC_API bool operator==(const inventory& left, const inventory& right);
BC_API bool operator!=(const inventory& left, const inventory& right);

} // namespace message
} // namespace libbitcoin

#endif
