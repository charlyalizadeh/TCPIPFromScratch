#include "../include/ipv4/ipv4.h"
#include "../include/utils/file.h"
#include "soft_assert.h"


void test_ipv4_checksum() {
    uint8_t* bytes;
    uint8_t size;
    ipv4_t ipv4;
    uint16_t checksum;
    char path[16];

    for(int i = 0; i < 5; i++) {
        sprintf(path, "./test/data/ip%d", i + 1);
        bytes = read_bytes(path, &size);
        ipv4_from_bytes(&ipv4, bytes, size);
        printf("=======\n");
        ipv4_print_hex(&ipv4);
        checksum = ipv4_compute_header_checksum(&ipv4);
        soft_assert_equal_int(checksum, ipv4.header.checksum);
        free(bytes);
    }
}
