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
#include <metaverse/bitcoin/wallet/ek_public.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <boost/program_options.hpp>
#include <metaverse/bitcoin/define.hpp>
#include <metaverse/bitcoin/formats/base_58.hpp>
#include <metaverse/bitcoin/math/checksum.hpp>

namespace libbitcoin {
namespace wallet {

ek_public::ek_public()
  : valid_(false), public_()
{
}

ek_public::ek_public(const std::string& encoded)
  : ek_public(from_string(encoded))
{
}

ek_public::ek_public(const ek_public& other)
  : valid_(other.valid_), public_(other.public_)
{
}

ek_public::ek_public(const encrypted_public& value)
  : valid_(true), public_(value)
{
}

// Factories.
// ----------------------------------------------------------------------------

ek_public ek_public::from_string(const std::string& encoded)
{
    // TODO: incorporate existing parser here, setting new members.

    encrypted_public key;
    return decode_base58(key, encoded) && verify_checksum(key) ?
        ek_public(key) : ek_public();
}

// Cast operators.
// ----------------------------------------------------------------------------

ek_public::operator const bool() const
{
    return valid_;
}

ek_public::operator const encrypted_public&() const
{
    return public_;
}

// Serializer.
// ----------------------------------------------------------------------------

std::string ek_public::encoded() const
{
    return encode_base58(public_);
}

// Accessors.
// ----------------------------------------------------------------------------

const encrypted_public& ek_public::public_key() const
{
    return public_;
}

// Operators.
// ----------------------------------------------------------------------------

ek_public& ek_public::operator=(const ek_public& other)
{
    valid_ = other.valid_;
    public_ = other.public_;
    return *this;
}

bool ek_public::operator<(const ek_public& other) const
{
    return encoded() < other.encoded();
}

bool ek_public::operator==(const ek_public& other) const
{
    return valid_ == other.valid_ && public_ == other.public_;
}

bool ek_public::operator!=(const ek_public& other) const
{
    return !(*this == other);
}

std::istream& operator>>(std::istream& in, ek_public& to)
{
    std::string value;
    in >> value;
    to = ek_public(value);

    if (!to)
    {
        using namespace boost::program_options;
        BOOST_THROW_EXCEPTION(invalid_option_value(value));
    }

    return in;
}

std::ostream& operator<<(std::ostream& out, const ek_public& of)
{
    out << of.encoded();
    return out;
}

} // namespace wallet
} // namespace libbitcoin
