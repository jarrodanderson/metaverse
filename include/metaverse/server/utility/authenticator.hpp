/**
 * Copyright (c) 2011-2021 libbitcoin developers (see AUTHORS)
 * Copyright (c) 2016-2021 metaverse core developers (see MVS-AUTHORS)
 *
 * This file is part of metaverse-server.
 *
 * metaverse-server is free software: you can redistribute it and/or
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
#ifndef MVS_SERVER_SECURE_AUTHENTICATOR_HPP
#define MVS_SERVER_SECURE_AUTHENTICATOR_HPP

#include <memory>
#include <metaverse/protocol.hpp>
#include <metaverse/server/define.hpp>
#include <metaverse/server/settings.hpp>

namespace libbitcoin {
namespace server {

class server_node;

class BCS_API authenticator
  : public bc::protocol::zmq::authenticator
{
public:
    typedef std::shared_ptr<authenticator> ptr;

    /// Construct an instance of the authenticator.
    authenticator(server_node& node);

    /// This class is not copyable.
    authenticator(const authenticator&) = delete;
    void operator=(const authenticator&) = delete;

    /// Apply authentication to the socket.
    bool apply(bc::protocol::zmq::socket& socket, const std::string& domain,
        bool secure);
};

} // namespace server
} // namespace libbitcoin

#endif
