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
#ifndef MVS_OSTREAM_WRITER_IPP
#define MVS_OSTREAM_WRITER_IPP

#include <algorithm>
#include <boost/asio/streambuf.hpp>
#include <metaverse/bitcoin/utility/assert.hpp>
#include <metaverse/bitcoin/utility/endian.hpp>
#include <metaverse/bitcoin/utility/exceptions.hpp>

namespace libbitcoin {

template <typename T>
void ostream_writer::write_big_endian(T value)
{
    byte_array<sizeof(T)> bytes = to_big_endian(value);
    write_bytes<sizeof(T)>(bytes);
}

template <typename T>
void ostream_writer::write_little_endian(T value)
{
    stream_.write(reinterpret_cast<const char*>(&value), sizeof(T));
}

template <typename T>
void ostream_writer::write_data(T& value)
{
    const auto size = value.size();
    if (size > 0)
        stream_.write(reinterpret_cast<const char*>(value.data()), size);
}

template <unsigned Size>
void ostream_writer::write_bytes(const byte_array<Size>& value)
{
    //for (unsigned i = 0; i < Size; i++)
    //    write_byte(value[i]);

    const auto size = value.size();
    if (size > 0)
        stream_.write(reinterpret_cast<const char*>(value.data()), size);
}

template <unsigned Size>
void ostream_writer::write_bytes_reverse(const byte_array<Size>& value)
{
    for (unsigned i = 0; i < Size; i++)
        write_byte(value[Size - (i + 1)]);
}

} // libbitcoin

#endif
