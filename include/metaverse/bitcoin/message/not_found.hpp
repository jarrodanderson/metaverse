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
#ifndef MVS_MESSAGE_NOT_FOUND_HPP
#define MVS_MESSAGE_NOT_FOUND_HPP

#include <initializer_list>
#include <istream>
#include <memory>
#include <string>
#include <metaverse/bitcoin/define.hpp>
#include <metaverse/bitcoin/constants.hpp>
#include <metaverse/bitcoin/math/hash.hpp>
#include <metaverse/bitcoin/message/inventory.hpp>
#include <metaverse/bitcoin/message/inventory_vector.hpp>
#include <metaverse/bitcoin/utility/data.hpp>

namespace libbitcoin {
namespace message {

class BC_API not_found
  : public inventory
{
public:
    typedef std::shared_ptr<not_found> ptr;

    static not_found factory_from_data(uint32_t version,
        const data_chunk& data);
    static not_found factory_from_data(uint32_t version, std::istream& stream);
    static not_found factory_from_data(uint32_t version, reader& source);

    not_found();
    not_found(const inventory_vector::list& values);
    not_found(const hash_list& hashes, inventory::type_id type);
    not_found(const std::initializer_list<inventory_vector>& values);

    bool from_data(uint32_t version, const data_chunk& data) override;
    bool from_data(uint32_t version, std::istream& stream) override;
    bool from_data(uint32_t version, reader& source) override;

    static const std::string command;
    static const uint32_t version_minimum;
    static const uint32_t version_maximum;
};

} // namespace message
} // namespace libbitcoin

#endif
