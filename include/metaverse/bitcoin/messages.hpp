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
#ifndef MVS_MESSAGES_HPP
#define MVS_MESSAGES_HPP

#include <cstdint>
#include <metaverse/bitcoin/message/address.hpp>
#include <metaverse/bitcoin/message/block_message.hpp>
#include <metaverse/bitcoin/message/block_transactions.hpp>
#include <metaverse/bitcoin/message/compact_block.hpp>
#include <metaverse/bitcoin/message/fee_filter.hpp>
#include <metaverse/bitcoin/message/filter_add.hpp>
#include <metaverse/bitcoin/message/filter_clear.hpp>
#include <metaverse/bitcoin/message/filter_load.hpp>
#include <metaverse/bitcoin/message/get_address.hpp>
#include <metaverse/bitcoin/message/get_block_transactions.hpp>
#include <metaverse/bitcoin/message/get_blocks.hpp>
#include <metaverse/bitcoin/message/get_data.hpp>
#include <metaverse/bitcoin/message/get_headers.hpp>
#include <metaverse/bitcoin/message/headers.hpp>
#include <metaverse/bitcoin/message/heading.hpp>
#include <metaverse/bitcoin/message/inventory.hpp>
#include <metaverse/bitcoin/message/inventory_vector.hpp>
#include <metaverse/bitcoin/message/memory_pool.hpp>
#include <metaverse/bitcoin/message/merkle_block.hpp>
#include <metaverse/bitcoin/message/network_address.hpp>
#include <metaverse/bitcoin/message/not_found.hpp>
#include <metaverse/bitcoin/message/ping.hpp>
#include <metaverse/bitcoin/message/pong.hpp>
#include <metaverse/bitcoin/message/reject.hpp>
#include <metaverse/bitcoin/message/send_compact_blocks.hpp>
#include <metaverse/bitcoin/message/send_headers.hpp>
#include <metaverse/bitcoin/message/transaction_message.hpp>
#include <metaverse/bitcoin/message/verack.hpp>
#include <metaverse/bitcoin/message/version.hpp>
#include <metaverse/bitcoin/utility/data.hpp>

// Minimum conditional protocol version: 31800

// libbitcoin-network
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// version      v2      70001           added relay field
// verack       v1
// getaddr      v1
// addr         v1
// ping         v1
// ping         v2      60001   BIP031  added nonce field
// pong         v1      60001   BIP031
// reject       v3      70002   BIP061
// ----------------------------------------------------------------------------
// alert        --                      no intent to support
// checkorder   --                      obsolete
// reply        --                      obsolete
// submitorder  --                      obsolete
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// libbitcoin-node
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// getblocks    v1
// inv          v1
// getdata      v1
// getdata      v3      70001   BIP037  allows filtered_block flag
// block        v1
// tx           v1
// notfound     v2      70001
// getheaders   v3      31800
// headers      v3      31800
// mempool      --      60002   BIP035
// mempool      v3      70002           allow multiple inv messages in reply
// sendheaders  v3      70012   BIP130
// feefilter    v3      70013   BIP133
// blocktxn     v3      70014   BIP152
// cmpctblock   v3      70014   BIP152
// getblocktxn  v3      70014   BIP152
// sendcmpct    v3      70014   BIP152
// merkleblock  v3      70001   BIP037  no bloom filters so unfiltered only
// ----------------------------------------------------------------------------
// filterload   --      70001   BIP037  no intent to support
// filteradd    --      70001   BIP037  no intent to support
// filterclear  --      70001   BIP037  no intent to support
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

namespace libbitcoin {
namespace message {

/**
* Serialize a message object to the Bitcoin wire protocol encoding.
*/
template <typename Message>
data_chunk serialize(uint32_t version, const Message& packet,
    uint32_t magic)
{
    // Serialize the payload (required for header size).
    const auto payload = packet.to_data(version);

    // Construct the payload header.
    heading head;
    head.magic = magic;
    head.command = Message::command;
    head.payload_size = static_cast<uint32_t>(payload.size());
    head.checksum = bitcoin_checksum(payload);

    // Serialize header and copy the payload into a single message buffer.
    auto message = head.to_data();
    extend_data(message, payload);
    return message;
}

} // namespace message
} // namespace libbitcoin

#endif
