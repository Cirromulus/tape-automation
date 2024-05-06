#pragma once

#include <bit>

/**
 * This file exists because, after 10 mins of googling,
 * I thought it was faster to just write an own constexpr endianswapper.
*/

template <typename T>
constexpr
T
swapIfNotNetworkOrder(const T& networkOrder)
{
    using namespace std;
    static_assert(
        endian::native == endian::big ||
        endian::native == endian::little,
    "I can't even!");

    if constexpr (endian::native == endian::big)
    {
        return byteswap(networkOrder);
    }
    else
    {
        return networkOrder;
    }
}