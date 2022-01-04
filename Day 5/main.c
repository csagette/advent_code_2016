#include <stdio.h>
#include <stdint.h>
#include <openssl/md5.h>
//abbhdwsy
#define INPUT "abc"
#define ALOT 16

int main(void)
{
    uint8_t digest[MD5_DIGEST_LENGTH], data[sizeof(INPUT) + ALOT] = INPUT;
    uint8_t *end = data + sizeof(INPUT), *count = end - 1;
    uint32_t part1 = 0, part2 = 0, part1_shift = 32, part2_mask = 0xff;
    *count = '0';
    for (;;) {

        MD5(data, end - data, digest);
        uint8_t skip = digest[0] | digest[1] | (digest[2] & 0xf0);
        printf("%d\n",skip);
        if (!skip) {
            uint32_t six   = digest[2] & 0xf;
            uint32_t seven = digest[3] >> 4;
            printf("%d",six);
            if (part1_shift) {
                part1 |= six << (part1_shift -= 4);
                if (!part1_shift) {
                    printf("Part 1: %08x\n", part1);
                }
            }
            if (part2_mask & (1 << six)) {
                part2_mask ^= 1 << six;
                part2 |= seven << ((7 - six) << 2);
                if (!part2_mask) {
                    printf("Part 2: %08x\n", part2);
                    break;
                }
            }
        }
        for (uint8_t *p = end - 1; ; *p-- = '0') {
            if (*p != '9') {
                (*p)++;
                break;
            }
            if (p == count) {
                *p = '1';
                *end++ = '0';
                break;
            }
        }
    }

    return 0;
}
