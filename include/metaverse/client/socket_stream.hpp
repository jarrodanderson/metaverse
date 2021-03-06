/**
 * Copyright (c) 2011-2021 libbitcoin developers (see AUTHORS)
 * Copyright (c) 2016-2021 metaverse core developers (see MVS-AUTHORS)
 *
 * This file is part of metaverse-client.
 *
 * metaverse-client is free software: you can redistribute it and/or
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
#ifndef MVS_CLIENT_SOCKET_STREAM_HPP
#define MVS_CLIENT_SOCKET_STREAM_HPP

#include <memory>
#include <metaverse/protocol.hpp>
#include <metaverse/client/define.hpp>
#include <metaverse/client/stream.hpp>

namespace libbitcoin {
namespace client {

/// This is the only class in the client with a direct protocol dependency.
class BCC_API socket_stream
  : public stream
{
public:
    socket_stream(protocol::zmq::socket& socket);

    protocol::zmq::socket& socket();

    // stream interface.
    virtual int32_t refresh();
    virtual bool read(stream& stream);
    virtual bool write(const data_stack& data);

private:
    protocol::zmq::socket& socket_;
};

} // namespace client
} // namespace libbitcoin

#endif
