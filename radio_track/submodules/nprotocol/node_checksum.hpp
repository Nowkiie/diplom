#pragma once
#include <cstdint>
namespace nc
{
static uint32_t adler32mod(const uint8_t* data, uint32_t len)
{
    const uint32_t mod_adler = 65521;
    const uint32_t block_adler = 5552;
    const uint32_t xor_value = 0xA54D281C;
    const uint32_t block_count = len / block_adler;
    uint32_t a = 1, b = 0;

    for (uint32_t block = 0; block < block_count; ++block)
    {
        for (uint32_t i = 0; i < block_adler; ++i)
        {
            a += data[i];
            b += a;
        }
        a %= mod_adler;
        b %= mod_adler;
        data += block_adler;
        len -= block_adler;
    }

    for (uint32_t index = 0; index < len; ++index)
    {
        a = (a + data[index]) % mod_adler;
        b = (b + a) % mod_adler;
    }

    return xor_value ^ ((b << 16) | a);
}

}  // namespace nc
