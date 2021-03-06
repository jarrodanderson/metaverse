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
#ifndef MVS_PNG_HPP
#define MVS_PNG_HPP

#include <cstdint>
#include <istream>
#include <metaverse/bitcoin/compat.hpp>
#include <metaverse/bitcoin/define.hpp>
#include <metaverse/bitcoin/utility/color.hpp>
#include <metaverse/bitcoin/utility/data.hpp>

#ifdef WITH_PNG
#include <png.h>

namespace libbitcoin {

class BC_API png
{
public:
    static BC_CONSTEXPR uint32_t margin = 2;
    static BC_CONSTEXPR uint32_t dots_per_inch = 72;
    static BC_CONSTEXPR uint32_t inches_per_meter = (100.0 / 2.54);

    static const color get_default_foreground()
    {
        static BC_CONSTEXPR color default_foreground{ 0, 0, 0, 255 };
        return default_foreground;
    }

    static const color get_default_background()
    {
        static BC_CONSTEXPR color default_background{ 255, 255, 255, 255 };
        return default_background;
    }

    /**
     * A method that takes encoded qrcode as a data chunk and writes it to
     * an output stream in png format with the default parameters.  The
     * size parameter specifies the number of dots (pixels) per qr code
     * modules.
     */
    static bool write_png(const data_chunk& data, uint32_t size,
        std::ostream& out);

    /**
     * A method that takes encoded qrcode data as a data chunk and writes
     * it to an output stream in png format with the specified parameters.
     */
    static bool write_png(const data_chunk& data, uint32_t size,
        uint32_t dots_per_inch, uint32_t margin, uint32_t inches_per_meter,
        const color& foreground, const color& background, std::ostream& out);

    /**
     * A method that reads encoded qrcode data via an input stream and
     * writes it to an output stream in png format with the default
     * parameters.  The size parameter specifies the number of dots
     * (pixels) per qr code modules.
     */
    static bool write_png(std::istream& in, uint32_t size, std::ostream& out);

    /**
     * A method that reads encoded qrcode data via an input stream and
     * writes it to an output stream in png format with the specified
     * parameters.
     */
    static bool write_png(std::istream& in, uint32_t size,
        uint32_t dots_per_inch, const uint32_t margin,
        uint32_t inches_per_meter, const color& foreground,
        const color& background, std::ostream& out);
};

} // namespace libbitcoin

#endif // WITH_PNG

#endif
