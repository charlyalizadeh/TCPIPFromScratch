#include "../include/ipv4/ipv4.h"
#include "../include/utils/file.h"
#include <assert.h>

void test_ipv4_checksum() {
    uint8_t* bytes[4];
    ipv4_t ipv4[4];
    uint16_t checksum[4];
    char path[16];

    for(int i = 0; i < 4; i++) {
        sprintf(path, "./test/data/ip%d", i + 1);
        bytes[i] = read_bytes(path);
        ipv4_from_bytes(bytes[i], &ipv4[i]);
        checksum[i] = ipv4header_compute_header_checksum(&ipv4[i].header);
        assert(checksum[i] == ipv4[i].header.checksum);
    }
}
