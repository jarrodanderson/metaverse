/**
 * Copyright (c) 2011-2021 libbitcoin developers (see AUTHORS)
 * Copyright (c) 2016-2021 metaverse core developers (see MVS-AUTHORS)
 *
 * This file is part of metaverse-explorer.
 *
 * metaverse-explorer is free software: you can redistribute it and/or
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
#ifndef BX_BIP39_LANGUAGE_HPP
#define BX_BIP39_LANGUAGE_HPP

#include <iostream>
#include <string>
#include <metaverse/bitcoin.hpp>
#include <metaverse/explorer/define.hpp>

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace libbitcoin {
namespace explorer {
namespace config {

/**
 * Serialization helper to convert between dictionary and string.
 */
class BCX_API language
{
public:

    /**
     * Default constructor.
     */
    language();

    /**
     * Initialization constructor.
     * @param[in]  token  The value to initialize with.
     */
    language(const std::string& token);

    /**
     * Initialization constructor.
     * @param[in]  languages  The value to initialize with.
     */
    language(bc::wallet::dictionary_list& languages);

    /**
     * Copy constructor.
     * @param[in]  other  The object to copy into self on construct.
     */
    language(const language& other);
    language& operator=(const language& other) = default;

    /**
     * Overload cast to internal type.
     * @return  This object's value cast to internal type.
     */
    operator const bc::wallet::dictionary_list() const;

    /**
     * Overload stream in. Throws if input is invalid.
     * @param[in]   input     The input stream to read the value from.
     * @param[out]  argument  The object to receive the read value.
     * @return                The input stream reference.
     */
    friend std::istream& operator>>(std::istream& input,
        language& argument);

    /**
     * Overload stream out.
     * @param[in]   output    The output stream to write the value to.
     * @param[out]  argument  The object from which to obtain the value.
     * @return                The output stream reference.
     */
    friend std::ostream& operator<<(std::ostream& output,
        const language& argument);

private:

    /**
     * The state of this object.
     */
    bc::wallet::dictionary_list value_;
};

} // namespace config
} // namespace explorer
} // namespace libbitcoin

#endif
