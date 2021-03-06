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
#ifndef MVS_MESSAGE_HEADING_HPP
#define MVS_MESSAGE_HEADING_HPP

#include <cstdint>
#include <cstddef>
#include <istream>
#include <string>
#include <boost/array.hpp>
#include <metaverse/bitcoin/constants.hpp>
#include <metaverse/bitcoin/define.hpp>
#include <metaverse/bitcoin/math/checksum.hpp>
#include <metaverse/bitcoin/utility/data.hpp>
#include <metaverse/bitcoin/utility/reader.hpp>
#include <metaverse/bitcoin/utility/writer.hpp>

namespace libbitcoin {
namespace message {

enum class message_type
{
    unknown,
    address,
    alert,
    block_message,
    block_transactions,
    compact_block,
    fee_filter,
    filter_add,
    filter_clear,
    filter_load,
    get_address,
    get_block_transactions,
    get_blocks,
    get_data,
    get_headers,
    headers,
    inventory,
    memory_pool,
    merkle_block,
    not_found,
    ping,
    pong,
    reject,
    send_compact_blocks,
    send_headers,
    transaction_message,
    verack,
    version
};

class BC_API heading
{
public:
    static size_t maximum_size() ;
    static size_t maximum_payload_size(uint32_t version) ;
    static size_t serialized_size() ;
    static heading factory_from_data(const data_chunk& data);
    static heading factory_from_data(std::istream& stream);
    static heading factory_from_data(reader& source);

    bool from_data(const data_chunk& data);
    bool from_data(std::istream& stream);
    bool from_data(reader& source);
    data_chunk to_data() const;
    void to_data(std::ostream& stream) const;
    void to_data(writer& sink) const;
    bool is_valid() const;
    void reset();
    message_type type() const;

    uint32_t magic;
    std::string command;
    uint32_t payload_size;
    uint32_t checksum;
};

BC_API bool operator==(const heading& left, const heading& right);
BC_API bool operator!=(const heading& left, const heading& right);

} // namespace message
} // namespace libbitcoin

#endif
