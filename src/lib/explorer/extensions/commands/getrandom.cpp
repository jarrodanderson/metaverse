/**
 * Copyright (c) 2016-2021 mvs developers
 *
 * This file is part of metaverse-explorer.
 *
 * metaverse-explorer is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License with
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


#include <metaverse/explorer/extensions/commands/getrandom.hpp>
#include <metaverse/node/p2p_node.hpp>

namespace libbitcoin {
namespace explorer {
namespace commands {

/************************ getrandom *************************/

console_result getrandom::invoke(Json::Value& jv_output,
                                   libbitcoin::server::server_node& node)
{
    Json::Value result;

    auto r = std::minmax(argument_.point1, argument_.point2);
    auto begin = r.first;
    auto end = r.second;

    auto rand_num = pseudo_random(begin, end);

    auto chunk = to_chunk(std::to_string(rand_num));
    auto rand_hash = sha3(chunk).hex();

    result["begin"] = begin;
    result["end"] = end;
    result["random_num"] = rand_num;
    result["random_hash"] = rand_hash;

    jv_output = result;

    return console_result::okay;
}

} // namespace commands
} // namespace explorer
} // namespace libbitcoin

