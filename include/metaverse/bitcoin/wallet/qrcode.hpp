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
#ifndef MVS_QRENCODE_HPP
#define MVS_QRENCODE_HPP

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <metaverse/bitcoin/compat.hpp>
#include <metaverse/bitcoin/define.hpp>
#include <metaverse/bitcoin/utility/data.hpp>

#ifdef WITH_QRENCODE
#include <qrencode.h>

namespace libbitcoin {
namespace wallet {

class BC_API qr
{
    typedef QRencodeMode encode_mode;
    typedef QRecLevel error_recovery_level;

  public:
    static BC_CONSTEXPR uint32_t version = 0;
    static BC_CONSTEXPR bool case_sensitive = true;
    static BC_CONSTEXPR encode_mode mode = QR_MODE_8;
    static BC_CONSTEXPR error_recovery_level level = QR_ECLEVEL_L;

    /**
     * A method that takes an input stream and writes the encoded qr data
     * to the specified output stream with default parameter values.
     */
    BC_API static bool encode(std::istream& in, std::ostream& out);

    /**
     * A method that takes a data chunk and returns the encoded qr data as
     * a data_chunk with default parameter values.
     */
    BC_API static data_chunk encode(const data_chunk& data);

    /**
     * A method that takes a data chunk and returns the encoded qr data as
     * a data chunk with the specified parameter values.
     */
    BC_API static data_chunk encode(const data_chunk& data,
        const uint32_t version, const error_recovery_level level,
        const encode_mode mode, const bool case_sensitive);

    /**
     * A method that takes an input stream and writes the encoded qr data
     * to the output stream with the specified parameter values.
     */
    BC_API static bool encode(std::istream& in, uint32_t version,
        error_recovery_level level, encode_mode mode, bool case_sensitive,
        std::ostream& out);
};

} // namespace wallet
} // namespace libbitcoin

#endif // WITH_QRENCODE

#endif
