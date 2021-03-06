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
#ifndef MVS_RANDOM_HPP
#define MVS_RANDOM_HPP

#include <random>
#include <cstdint>
#include <metaverse/bitcoin/define.hpp>
#include <metaverse/bitcoin/utility/asio.hpp>
#include <metaverse/bitcoin/utility/data.hpp>
#include <metaverse/bitcoin/constants.hpp>

namespace libbitcoin {

class BC_API pseudo_random
{
  public:
    /**
     * Fill a container with randomness using the default random engine.
     */
    template<class Container>
    static void fill(Container& out)
    {
        // uniform_int_distribution is undefined for sizes < 16 bits.
        std::uniform_int_distribution<uint16_t> distribution(0, max_uint8);
        auto& twister = pseudo_random::get_twister();

        const auto fill = [&distribution, &twister](uint8_t)
        {
            return static_cast<uint8_t>(distribution(twister));
        };

        std::transform(out.begin(), out.end(), out.begin(), fill);
    }

    /**
     * Shuffle a container using the default random engine.
     */
    template<class Container>
    static void shuffle(Container& out)
    {
        std::shuffle(out.begin(), out.end(), get_twister());
    }

    /**
     * Generate a pseudo random number within the domain.
     * @return  The 64 bit number.
     */
    static uint64_t next();

    /**
     * Generate a pseudo random number within [begin, end].
     * @return  The 64 bit number.
     */
    static uint64_t next(uint64_t begin, uint64_t end);

    /**
     * Convert a time duration to a value in the range [max/ratio, max].
     * @param[in]  maximum  The maximum value to return.
     * @param[in]  ratio    The determinant of the minimum duration as the inverse
     *                      portion of the maximum duration.
     * @return              The randomized duration.
     */
    static asio::duration duration(const asio::duration& maximum,
        uint8_t ratio=2);

  private:
    static std::mt19937& get_twister();
};

/**
 * Generate a pseudo random number within the domain.
 * @return  The 64 bit number (use % to subset domain).
 */
BC_API uint64_t pseudo_random();

/**
 * Generate a non-zero pseudo random number within the domain.
 * @return  The 64 bit number (use % to subset domain).
 */
BC_API uint64_t nonzero_pseudo_random();

/**
 * Generate a pseudo random number within [begin, end].
 * @return  The 64 bit number.
 */
BC_API uint64_t pseudo_random(uint64_t begin, uint64_t end);

/**
 * Fill a buffer with randomness using the default random engine.
 * @param[in]  chunk  The buffer to fill with randomness.
 */
BC_API void pseudo_random_fill(data_chunk& chunk);

/**
 * Convert a time duration to a value in the range [max/ratio, max].
 * @param[in]  maximum  The maximum value to return.
 * @param[in]  ratio    The determinant of the minimum duration as the inverse
 *                      portion of the maximum duration.
 * @return              The randomized duration.
 */
BC_API asio::duration pseudo_randomize(const asio::duration& maximum,
    uint8_t ratio=2);

} // namespace libbitcoin

#endif
