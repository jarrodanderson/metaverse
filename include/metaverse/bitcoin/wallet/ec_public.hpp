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
#ifndef MVS_EC_PUBLIC_HPP
#define MVS_EC_PUBLIC_HPP

#include <cstdint>
#include <string>
#include <metaverse/bitcoin/define.hpp>
#include <metaverse/bitcoin/math/hash.hpp>
#include <metaverse/bitcoin/math/elliptic_curve.hpp>
#include <metaverse/bitcoin/utility/data.hpp>

namespace libbitcoin {
namespace wallet {

class ec_private;
class payment_address;

/// Use to pass an ec point as either ec_compressed or ec_uncompressed.
/// ec_public doesn't carry a version for address creation or base58 encoding.
class BC_API ec_public
{
public:
    static const uint8_t compressed_even;
    static const uint8_t compressed_odd;
    static const uint8_t uncompressed;
    // chenhao bad modify
    static uint8_t mainnet_p2kh;

    /// Constructors.
    ec_public();
    ec_public(const ec_public& other);
    ec_public(const ec_private& secret);
    ec_public(const data_chunk& decoded);
    ec_public(const std::string& base16);
    ec_public(const ec_compressed& point, bool compress=true);
    ec_public(const ec_uncompressed& point, bool compress=false);

    /// Operators.
    bool operator<(const ec_public& other) const;
    bool operator==(const ec_public& other) const;
    bool operator!=(const ec_public& other) const;
    ec_public& operator=(const ec_public& other);
    friend std::istream& operator>>(std::istream& in, ec_public& to);
    friend std::ostream& operator<<(std::ostream& out, const ec_public& of);

    /// Cast operators.
    operator const bool() const;
    operator const ec_compressed&() const;

    /// Serializer.
    std::string encoded() const;

    /// Accessors.
    const ec_compressed& point() const;
    const uint16_t version() const;
    const uint8_t payment_version() const;
    const uint8_t wif_version() const;
    const bool compressed() const;

    /// Methods.
    bool to_data(data_chunk& out) const;
    bool to_uncompressed(ec_uncompressed& out) const;
    payment_address to_payment_address(uint8_t version=mainnet_p2kh) const;

private:
    /// Validators.
    static bool is_point(data_slice decoded);

    /// Factories.
    static ec_public from_data(const data_chunk& decoded);
    static ec_public from_private(const ec_private& secret);
    static ec_public from_string(const std::string& base16);
    static ec_public from_point(const ec_uncompressed& point, bool compress);

    /// Members.
    /// These should be const, apart from the need to implement assignment.
    bool valid_;
    bool compress_;
    uint8_t version_;
    ec_compressed point_;
};

} // namespace wallet
} // namespace libbitcoin

#endif
