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
#ifndef MVS_CHECKSUM_IPP
#define MVS_CHECKSUM_IPP

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <metaverse/bitcoin/utility/assert.hpp>
#include <metaverse/bitcoin/utility/data.hpp>
#include <metaverse/bitcoin/utility/endian.hpp>

namespace libbitcoin {

template <size_t Size>
bool build_checked_array(byte_array<Size>& out,
    const std::initializer_list<data_slice>& slices)
{
    return build_array(out, slices) && insert_checksum(out);
}

template<size_t Size>
bool insert_checksum(byte_array<Size>& out)
{
    if (out.size() < checksum_size)
        return false;

    data_chunk body(out.begin(), out.end() - checksum_size);
    const auto checksum = to_little_endian(bitcoin_checksum(body));
    std::copy(checksum.begin(), checksum.end(), out.end() - checksum_size);
    return true;
}

// std::array<> is used in place of byte_array<> to enable Size deduction.
template <size_t Size>
bool unwrap(uint8_t& out_version,
    std::array<uint8_t, UNWRAP_SIZE(Size)>& out_payload,
    const std::array<uint8_t, Size>& wrapped)
{
    uint32_t unused;
    return unwrap(out_version, out_payload, unused, wrapped);
}

// std::array<> is used in place of byte_array<> to enable Size deduction.
template <size_t Size>
bool unwrap(uint8_t& out_version,
    std::array<uint8_t, UNWRAP_SIZE(Size)>& out_payload,
    uint32_t& out_checksum, const std::array<uint8_t, Size>& wrapped)
{
    if (!verify_checksum(wrapped))
        return false;

    out_version = slice<0, 1>(wrapped)[0];
    out_payload = slice<1, Size - checksum_size>(wrapped);
    const auto bytes = slice<Size - checksum_size, Size>(wrapped);
    out_checksum = from_little_endian_unsafe<uint32_t>(bytes.begin());
    return true;
}

// std::array<> is used in place of byte_array<> to enable Size deduction.
template <size_t Size>
std::array<uint8_t, WRAP_SIZE(Size)> wrap(uint8_t version,
    const std::array<uint8_t, Size>& payload)
{
    byte_array<WRAP_SIZE(Size)> out;
    build_array(out, { to_array(version), payload });
    insert_checksum(out);
    return out;
}

} // namespace libbitcoin

#endif
