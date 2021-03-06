/**
 * Copyright (c) 2011-2021 libbitcoin developers (see AUTHORS)
 * Copyright (c) 2016-2021 metaverse core developers (see MVS-AUTHORS)
 *
 * This file is part of metaverse-protocol.
 *
 * metaverse-protocol is free software: you can redistribute it and/or
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
#ifdef MVS_VERSION4

#include <metaverse/protocol/packet.hpp>

#include <metaverse/bitcoin.hpp>
#include <metaverse/protocol/zmq/message.hpp>
#include <metaverse/protocol/zmq/socket.hpp>

namespace libbitcoin {
namespace protocol {

packet::packet()
{
}

const data_chunk packet::origin() const
{
    return origin_;
}

const data_chunk packet::destination() const
{
    return destination_;
}

void packet::set_destination(const data_chunk& destination)
{
    destination_ = destination;
}

bool packet::receive(zmq::socket& socket)
{
    zmq::message message;

    if (socket.receive(message).value() != error::success || message.empty())
        return false;

    // Optional - ROUTER sockets strip this.
    if (message.size() > 2)
        origin_ = message.dequeue_data();

    // Remove empty delimiter frame.
    message.dequeue();

    return decode_payload(message.dequeue_data()) && message.empty();
}

////bool packet::receive(const std::shared_ptr<zmq::socket>& socket)
////{
////    return (socket != nullptr) && receive(*(socket.get()));
////}

bool packet::send(zmq::socket& socket)
{
    zmq::message message;

    // Optionally encode the destination.
    if (!destination_.empty())
        message.enqueue(destination_);

    // Add empty delimiter frame.
    message.enqueue(data_chunk{});

    return encode_payload(message) && socket.send(message).value() == error::success;
}

////bool packet::send(const std::shared_ptr<zmq::socket>& socket)
////{
////    return (socket != nullptr) && send(*(socket.get()));
////}

}
}

#endif
