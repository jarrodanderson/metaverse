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
#include <metaverse/bitcoin/wallet/ek_private.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <boost/program_options.hpp>
#include <metaverse/bitcoin/define.hpp>
#include <metaverse/bitcoin/formats/base_58.hpp>
#include <metaverse/bitcoin/math/checksum.hpp>

namespace libbitcoin {
namespace wallet {

ek_private::ek_private()
  : valid_(false), private_()
{
}

ek_private::ek_private(const std::string& encoded)
  : ek_private(from_string(encoded))
{
}

ek_private::ek_private(const ek_private& other)
  : valid_(other.valid_), private_(other.private_)
{
}

ek_private::ek_private(const encrypted_private& value)
  : valid_(true), private_(value)
{
}

// Factories.
// ----------------------------------------------------------------------------

ek_private ek_private::from_string(const std::string& encoded)
{
    // TODO: incorporate existing parser here, setting new members.

    encrypted_private key;
    return decode_base58(key, encoded) && verify_checksum(key) ?
        ek_private(key) : ek_private();
}

// Cast operators.
// ----------------------------------------------------------------------------

ek_private::operator const bool() const
{
    return valid_;
}

ek_private::operator const encrypted_private&() const
{
    return private_;
}

// Serializer.
// ----------------------------------------------------------------------------

std::string ek_private::encoded() const
{
    return encode_base58(private_);
}

// Accessors.
// ----------------------------------------------------------------------------

const encrypted_private& ek_private::private_key() const
{
    return private_;
}

// Operators.
// ----------------------------------------------------------------------------

ek_private& ek_private::operator=(const ek_private& other)
{
    valid_ = other.valid_;
    private_ = other.private_;
    return *this;
}

bool ek_private::operator<(const ek_private& other) const
{
    return encoded() < other.encoded();
}

bool ek_private::operator==(const ek_private& other) const
{
    return valid_ == other.valid_ && private_ == other.private_;
}

bool ek_private::operator!=(const ek_private& other) const
{
    return !(*this == other);
}

std::istream& operator>>(std::istream& in, ek_private& to)
{
    std::string value;
    in >> value;
    to = ek_private(value);

    if (!to)
    {
        using namespace boost::program_options;
        BOOST_THROW_EXCEPTION(invalid_option_value(value));
    }

    return in;
}

std::ostream& operator<<(std::ostream& out, const ek_private& of)
{
    out << of.encoded();
    return out;
}

} // namespace wallet
} // namespace libbitcoin
