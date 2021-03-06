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
#include "parse_encrypted_public.hpp"

#include <cstdint>
#include <cstddef>
#include <metaverse/bitcoin/math/checksum.hpp>
#include <metaverse/bitcoin/math/hash.hpp>
#include <metaverse/bitcoin/utility/data.hpp>
#include <metaverse/bitcoin/wallet/encrypted_keys.hpp>
#include "parse_encrypted_key.hpp"
#include "parse_encrypted_prefix.hpp"

namespace libbitcoin {
namespace wallet {

// This prefix results in the prefix "cfrm" in the base58 encoding but is
// modified when the payment address is Bitcoin mainnet (0).
const byte_array<parse_encrypted_public::magic_size>
parse_encrypted_public::magic_
{
    { 0x64, 0x3b, 0xf6, 0xa8 }
};

byte_array<parse_encrypted_public::prefix_size>
parse_encrypted_public::prefix_factory(uint8_t address)
{
    const auto context = default_context_ + address;
    return splice(magic_, to_array(context));
}

parse_encrypted_public::parse_encrypted_public(const encrypted_public& key)
  : parse_encrypted_key<prefix_size>(
        slice<0, 5>(key),
        slice<5, 6>(key),
        slice<6, 10>(key),
        slice<10, 18>(key)),
    sign_(slice<18, 19>(key)),
    data_(slice<19, 51>(key))
{
    valid(verify_magic() && verify_checksum(key));
}

uint8_t parse_encrypted_public::address_version() const
{
    return context() - default_context_;
}

hash_digest parse_encrypted_public::data() const
{
    return data_;
}

one_byte parse_encrypted_public::sign() const
{
    return sign_;
}

bool parse_encrypted_public::verify_magic() const
{
    return slice<0, magic_size>(prefix()) == magic_;
}

} // namespace wallet
} // namespace libbitcoin
