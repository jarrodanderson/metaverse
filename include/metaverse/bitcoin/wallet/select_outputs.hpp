/**
 * Copyright (c) 2011-2021 libbitcoin developers (see AUTHORS)
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
#ifndef MVS_WALLET_SELECT_OUTPUTS_HPP
#define MVS_WALLET_SELECT_OUTPUTS_HPP

#include <cstdint>
#include <metaverse/bitcoin/define.hpp>
#include <metaverse/bitcoin/chain/output.hpp>
#include <metaverse/bitcoin/chain/output_point.hpp>

namespace libbitcoin {
namespace wallet {

struct BC_API select_outputs
{
    enum class algorithm
    {
        greedy
    };

    /// Select optimal outpoints for a spend from unspent outputs list.
    /// Return includes the amount of change remaining from the spend.
    static void select(chain::points_info& out,
        chain::output_point_info::list unspent, uint64_t minimum_value,
        algorithm option=algorithm::greedy);
};

} // namespace wallet
} // namespace libbitcoin

#endif
