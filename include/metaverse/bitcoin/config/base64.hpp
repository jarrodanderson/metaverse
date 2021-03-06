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
#ifndef MVS_CONFIG_BASE64_HPP
#define MVS_CONFIG_BASE64_HPP

#include <iostream>
#include <string>
#include <metaverse/bitcoin/define.hpp>
#include <metaverse/bitcoin/utility/data.hpp>

namespace libbitcoin {
namespace config {

/**
 * Serialization helper for base64 encoded data.
 */
class BC_API base64
{
public:

    /**
     * Default constructor.
     */
    base64();

    /**
     * Initialization constructor.
     * @param[in]  base64  The value to initialize with.
     */
    base64(const std::string& base64);

    /**
     * Initialization constructor.
     * @param[in]  value  The value to initialize with.
     */
    base64(const data_chunk& value);

    /**
     * Copy constructor.
     * @param[in]  other  The object to copy into self on construct.
     */
    base64(const base64& other);
    base64& operator=(const base64& other) = default;

    /**
     * Overload cast to internal type.
     * @return  This object's value cast to internal type reference.
     */
    operator const data_chunk&() const;

    /**
     * Overload cast to generic data reference.
     * @return  This object's value cast to a generic data.
     */
    operator data_slice() const;

    /**
     * Overload stream in. Throws if input is invalid.
     * @param[in]   input     The input stream to read the value from.
     * @param[out]  argument  The object to receive the read value.
     * @return                The input stream reference.
     */
    friend std::istream& operator>>(std::istream& input,
        base64& argument);

    /**
     * Overload stream out.
     * @param[in]   output    The output stream to write the value to.
     * @param[out]  argument  The object from which to obtain the value.
     * @return                The output stream reference.
     */
    friend std::ostream& operator<<(std::ostream& output,
        const base64& argument);

private:

    /**
     * The state of this object.
     */
    data_chunk value_;
};

} // namespace config
} // namespace libbitcoin

#endif
