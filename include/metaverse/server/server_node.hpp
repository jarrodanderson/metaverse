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
#ifndef MVS_SERVER_SERVER_NODE_HPP
#define MVS_SERVER_SERVER_NODE_HPP

#include <cstdint>
#include <atomic>
#include <memory>
#include <metaverse/node.hpp>
#include <metaverse/protocol.hpp>
#include <metaverse/server/configuration.hpp>
#include <metaverse/server/define.hpp>
#include <metaverse/server/messages/message.hpp>
#include <metaverse/server/messages/route.hpp>
#include <metaverse/server/services/block_service.hpp>
#include <metaverse/server/services/heartbeat_service.hpp>
#include <metaverse/server/services/query_service.hpp>
#include <metaverse/server/services/transaction_service.hpp>
#include <metaverse/server/utility/authenticator.hpp>
#include <metaverse/server/workers/notification_worker.hpp>
#include <metaverse/bitcoin/utility/path.hpp>
#include <metaverse/consensus/miner.hpp>

#include <boost/shared_ptr.hpp>

namespace mgbubble{
    class HttpServ;
    class WsPushServ;
}
namespace libbitcoin {
namespace server {

class notification_worker;

class BCS_API server_node
  : public node::p2p_node
{
public:
    typedef std::shared_ptr<server_node> ptr;

    /// Compute the minimum threadpool size required to run the server.
    static uint32_t threads_required(const configuration& configuration);

    /// Construct a server node.
    server_node(const configuration& configuration);

    /// Ensure all threads are coalesced.
    virtual ~server_node();

    /// Invoke startup and seeding sequence, call from constructing thread.
    void start(result_handler handler) override;

    // Properties.
    // ----------------------------------------------------------------------------

    /// Server configuration settings.
    virtual const settings& server_settings() const;

    // Run sequence.
    // ------------------------------------------------------------------------

    /// Synchronize the blockchain and then begin long running sessions,
    /// call from start result handler. Call base method to skip sync.
    virtual void run(result_handler handler) override;

    // Shutdown.
    // ------------------------------------------------------------------------

    /// Idempotent call to signal work stop, start may be reinvoked after.
    /// Returns the result of file save operation.
    virtual bool stop() override;

    /// Blocking call to coalesce all work and then terminate all threads.
    /// Call from thread that constructed this class, or don't call at all.
    /// This calls stop, and start may be reinvoked after calling this.
    virtual bool close() override;

    // Notification.
    // ------------------------------------------------------------------------

    /// Subscribe to address (including stealth) prefix notifications.
    /// Stealth prefix is limited to 32 bits, address prefix to 256 bits.
    virtual void subscribe_address(const route& reply_to, uint32_t id,
        const binary& prefix_filter, chain::subscribe_type type);

    /// Subscribe to transaction penetration notifications.
    virtual void subscribe_penetration(const route& reply_to, uint32_t id,
        const hash_digest& tx_hash);

    /// Get miner.
    virtual consensus::miner& miner();

    virtual bool is_use_testnet_rules() const override;

    bool is_blockchain_sync() const { return under_blockchain_sync_.load(std::memory_order_relaxed); }

private:
    void handle_running(const code& ec, result_handler handler);

    bool start_services();
    bool start_authenticator();
    bool start_query_services();
    bool start_heartbeat_services();
    bool start_block_services();
    bool start_transaction_services();
    bool start_query_workers(bool secure);

    bool open_ui();

    std::atomic<bool> under_blockchain_sync_;

    const configuration& configuration_;
    static boost::filesystem::path webpage_path_;

    consensus::miner miner_;
    boost::shared_ptr<mgbubble::HttpServ> rest_server_;
    boost::shared_ptr<mgbubble::WsPushServ> push_server_;
    // These are thread safe.
    authenticator authenticator_;
    query_service secure_query_service_;
    query_service public_query_service_;
    heartbeat_service secure_heartbeat_service_;
    heartbeat_service public_heartbeat_service_;
    block_service secure_block_service_;
    block_service public_block_service_;
    transaction_service secure_transaction_service_;
    transaction_service public_transaction_service_;
    notification_worker secure_notification_worker_;
    notification_worker public_notification_worker_;
};

} // namespace server
} // namespace libbitcoin

#endif
