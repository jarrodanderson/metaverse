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
#ifndef  MVS_SUBSCRIBER_HPP
#define  MVS_SUBSCRIBER_HPP

#include <functional>
#include <memory>
#include <string>
#include <vector>
#include <metaverse/bitcoin/utility/assert.hpp>
#include <metaverse/bitcoin/utility/dispatcher.hpp>
#include <metaverse/bitcoin/utility/enable_shared_from_base.hpp>
#include <metaverse/bitcoin/utility/thread.hpp>
#include <metaverse/bitcoin/utility/threadpool.hpp>
////#include <metaverse/bitcoin/utility/track.hpp>

namespace libbitcoin {

template <typename... Args>
class subscriber
  : public enable_shared_from_base<subscriber<Args...>>
    /*, track<subscriber<Args...>>*/
{
public:
    typedef std::function<void (Args...)> handler;
    typedef std::shared_ptr<subscriber<Args...>> ptr;

    subscriber(threadpool& pool, const std::string& class_name);
    ~subscriber();

    /// Enable new subscriptions.
    void start();

    /// Prevent new subscriptions.
    void stop();

    /// Subscribe to notifications (for one invocation only).
    void subscribe(handler handler, Args... stopped_args);

    /// Invoke and clear all handlers sequentially (blocking).
    void invoke(Args... args);

    /// Invoke and clear all handlers sequentially (non-blocking).
    void relay(Args... args);

private:
    typedef std::vector<handler> list;

    void do_invoke(Args... args);

    bool stopped_;
    list subscriptions_;
    dispatcher dispatch_;
    mutable upgrade_mutex invoke_mutex_;
    mutable upgrade_mutex subscribe_mutex_;
};

} // namespace libbitcoin

#include <metaverse/bitcoin/impl/utility/subscriber.ipp>

#endif
