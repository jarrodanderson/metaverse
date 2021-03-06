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
#ifndef MVS_CHAIN_HISTORY_HPP
#define MVS_CHAIN_HISTORY_HPP

#include <cstdint>
#include <vector>
#include <metaverse/bitcoin/define.hpp>
#include <metaverse/bitcoin/chain/point.hpp>
#include <metaverse/bitcoin/chain/output_point.hpp>

namespace libbitcoin {
namespace chain {

/// Use "kind" for union differentiation.
enum class point_kind : uint32_t
{
    output = 0,
    spend = 1
};

/// This structure models the client-server protocol in v1/v2/v3.
/// The height value here is 64 bit, but 32 bits on the wire.
struct BC_API history_compact
{
    typedef std::vector<history_compact> list;

    // The type of point (output or spend).
    point_kind kind;

    /// The point that identifies the record.
    chain::point point;

    /// The height of the point.
    uint64_t height;

    union
    {
        /// If output, then satoshi value of output.
        uint64_t value;

        /// If spend, then checksum hash of previous output point
        /// To match up this row with the output, recompute the
        /// checksum from the output row with spend_checksum(row.point)
        uint64_t previous_checksum;
    };
};

/// This structure is used between client and API callers in v3.
/// This structure models the client-server protocol in v1/v2.
/// The height values here are 64 bit, but 32 bits on the wire.
struct BC_API history
{
    typedef std::vector<history> list;

    /// If there is no output this is null_hash:max.
    output_point output;
    uint64_t output_height;

    /// The satoshi value of the output.
    uint64_t value;

    /// If there is no spend this is null_hash:max.
    input_point spend;

    union
    {
        /// The height of the spend or max if no spend.
        uint64_t spend_height;

        /// During expansion this value temporarily doubles as a checksum.
        uint64_t temporary_checksum;
    };
};

} // namespace chain
} // namespace libbitcoin

#endif
