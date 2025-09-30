#include "../include/ipv4/ipv4.h"
#include "../include/utils/file.h"
#include "soft_assert.h"


void test_ipv4_checksum() {
    uint8_t* bytes[5];
    ipv4_t ipv4[5];
    uint16_t checksum[5];
    char path[16];

    for(int i = 0; i < 5; i++) {
        sprintf(path, "./test/data/ip%d", i + 1);
        bytes[i] = read_bytes(path);
        ipv4_from_bytes(bytes[i], &ipv4[i]);
        checksum[i] = ipv4_compute_header_checksum(&ipv4[i]);
        soft_assert_equal_int(checksum[i], ipv4[i].header.checksum);
    }
}
