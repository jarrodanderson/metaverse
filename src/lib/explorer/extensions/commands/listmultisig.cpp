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

#include <metaverse/explorer/json_helper.hpp>
#include <metaverse/explorer/dispatch.hpp>
#include <metaverse/explorer/extensions/commands/listmultisig.hpp>
#include <metaverse/explorer/extensions/command_extension_func.hpp>
#include <metaverse/explorer/extensions/command_assistant.hpp>
#include <metaverse/explorer/extensions/exception.hpp>

namespace libbitcoin {
namespace explorer {
namespace commands {

using namespace bc::explorer::config;

console_result listmultisig::invoke(Json::Value& jv_output,
    libbitcoin::server::server_node& node)
{
    auto& blockchain = node.chain_impl();
    // parameter account name check
    auto acc = blockchain.is_account_passwd_valid(auth_.name, auth_.auth);

    Json::Value nodes;
    auto multisig_vec = acc->get_multisig_vec();
    auto helper = config::json_helper(get_api_version());
    for(auto& acc_multisig : multisig_vec) {
        Json::Value node = helper.prop_list(acc_multisig);
        nodes.append(node);
    }

    if (get_api_version() == 1 && nodes.isNull()) { // compatible for v1
        jv_output["multisig"] = "";
    }
    else if (get_api_version() <= 2) {
        jv_output["multisig"] = nodes;
    }
    else {
        if(nodes.isNull())
            nodes.resize(0);  

        jv_output = nodes;
    }

    return console_result::okay;
}


} // namespace commands
} // namespace explorer
} // namespace libbitcoin

