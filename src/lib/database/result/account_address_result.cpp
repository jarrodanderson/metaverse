/**
 * Copyright (c) 2011-2021 metaverse developers (see AUTHORS)
 *
 * This file is part of mvs-node.
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
#include <metaverse/database/result/account_address_result.hpp>
#include <metaverse/bitcoin/chain/attachment/account/account_address.hpp>
#include <cstddef>
#include <cstdint>
#include <metaverse/bitcoin.hpp>
#include <metaverse/database/memory/memory.hpp>

namespace libbitcoin {
namespace database {

template <typename Iterator>
std::shared_ptr<chain::account_address> deserialize_account_address_detail(const Iterator first)
{
    auto detail = std::make_shared<chain::account_address>();
    auto deserial = make_deserializer_unsafe(first);
    detail->from_data(deserial);
    return detail;
}

account_address_result::account_address_result(const memory_ptr slab)
  : base_result(slab)
{
}

std::shared_ptr<chain::account_address> account_address_result::get_account_address_detail() const
{
    //BITCOIN_ASSERT(get_slab());
    std::shared_ptr<chain::account_address> addr(nullptr);
    if(get_slab())
    {
        const auto memory = REMAP_ADDRESS(get_slab());
        addr = deserialize_account_address_detail(memory);
    }
    return addr;
}
} // namespace database
} // namespace libbitcoin

