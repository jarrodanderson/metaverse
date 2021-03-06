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
#ifndef MVS_CONFIG_SODIUM_HPP
#define MVS_CONFIG_SODIUM_HPP

#include <iostream>
#include <string>
#include <vector>
#include <metaverse/bitcoin/define.hpp>
#include <metaverse/bitcoin/utility/data.hpp>
#include <metaverse/bitcoin/math/hash.hpp>

namespace libbitcoin {
namespace config {

/**
 * Serialization helper for base58 sodium keys.
 */
class BC_API sodium
{
public:
    /**
     * A list of base85 values.
     * This must provide operator<< for ostream in order to be used as a
     * boost::program_options default_value.
     */
    typedef std::vector<sodium> list;

    /**
     * Default constructor.
     */
    sodium();

    /**
     * Initialization constructor.
     * @param[in]  base85  The value to initialize with.
     */
    sodium(const std::string& base85);

    /**
     * Initialization constructor.
     * @param[in]  value  The value to initialize with.
     */
    sodium(const hash_digest& value);

    /**
     * Copy constructor.
     * @param[in]  other  The object to copy into self on construct.
     */
    sodium(const sodium& other);
    sodium& operator=(const sodium&) = default;

    /**
     * Getter.
     * @return True if the key is initialized.
     */
    operator bool() const;

    /**
     * Overload cast to internal type.
     * @return  This object's value cast to internal type.
     * chenhao
     */
    operator hash_digest() const;

    /**
     * Overload cast to generic data reference.
     * @return  This object's value cast to generic data.
     */
    operator data_slice() const;

    /**
     * Get the key as a base85 encoded (z85) string.
     * @return The encoded key.
     */
    std::string to_string() const;

    /**
     * Overload stream in. Throws if input is invalid.
     * @param[in]   input     The input stream to read the value from.
     * @param[out]  argument  The object to receive the read value.
     * @return                The input stream reference.
     */
    friend std::istream& operator>>(std::istream& input,
        sodium& argument);

    /**
     * Overload stream out.
     * @param[in]   output    The output stream to write the value to.
     * @param[out]  argument  The object from which to obtain the value.
     * @return                The output stream reference.
     */
    friend std::ostream& operator<<(std::ostream& output,
        const sodium& argument);

private:

    /**
     * The state of this object.
     */
    hash_digest value_;
};

} // namespace config
} // namespace libbitcoin

#endif
