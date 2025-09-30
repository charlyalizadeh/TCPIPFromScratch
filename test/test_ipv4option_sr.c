#include "../include/ipv4/source_route.h"
#include "soft_assert.h"


void test_ipv4option_sr_init() {
    ipv4option_sr_t sr;

    ipv4option_sr_init(&sr);
    soft_assert_equal_int(sr.length, 3);
    soft_assert_equal_int(sr.pointer, 4);
    for(size_t i = 0; i < 9; i++)
        soft_assert_equal_int(sr.route[i], 0);
    soft_assert_equal_int(sr.route_length, 0);
}

void test_ipv4option_sr_set_type() {
    ipv4option_sr_t sr;

    ipv4option_sr_init(&sr);

    for(size_t i = 0; i < 9; i++)
        sr.route[i] = 1;
    ipv4option_sr_set_type(&sr, RR);
    soft_assert_equal_int(sr.type, RR);
    for(size_t i = 0; i < 9; i++)
        soft_assert_equal_int(sr.route[i], 0);

    ipv4option_sr_set_type(&sr, LSRR);
    soft_assert_equal_int(sr.type, LSRR);

    ipv4option_sr_set_type(&sr, SSRR);
    soft_assert_equal_int(sr.type, SSRR);
}

void test_ipv4option_sr_push_address() {
    ipv4option_sr_t sr;
    uint32_t addr1, addr2;

    ipv4option_sr_init(&sr);

    addr1 = 0xAAAAAAAA;
    ipv4option_sr_push_address(&sr, addr1);
    soft_assert_equal_int(sr.length, 3 + 4);
    soft_assert_equal_int(sr.route_length, 1);
    soft_assert_equal_int(sr.route[0], addr1);

    addr2 = 0xBBBBBBBB;
    ipv4option_sr_push_address(&sr, addr2);
    soft_assert_equal_int(sr.length, 3 + 2 * 4);
    soft_assert_equal_int(sr.route_length, 2);
    soft_assert_equal_int(sr.route[0], addr1);
    soft_assert_equal_int(sr.route[1], addr2);
}

void test_ipv4option_sr_pop_address() {
    ipv4option_sr_t sr;
    uint32_t addr1, addr2;
    uint32_t addr1_pop, addr2_pop;

    ipv4option_sr_init(&sr);

    addr1 = 0xAAAAAAAA;
    addr2 = 0xBBBBBBBB;
    ipv4option_sr_push_address(&sr, addr1);
    ipv4option_sr_push_address(&sr, addr2);

    addr2_pop = ipv4option_sr_pop_address(&sr);
    soft_assert_equal_int(sr.length, 3 + 4);
    soft_assert_equal_int(sr.route_length, 1);
    soft_assert_equal_int(sr.route[0], addr1);
    soft_assert_equal_int(addr2, addr2_pop);

    addr1_pop = ipv4option_sr_pop_address(&sr);
    soft_assert_equal_int(sr.length, 3);
    soft_assert_equal_int(sr.pointer, 4);
    for(size_t i = 0; i < 9; i++)
        soft_assert_equal_int(sr.route[i], 0);
    soft_assert_equal_int(sr.route_length, 0);
    soft_assert_equal_int(addr1, addr1_pop);
}

void test_ipv4option_sr_set_address() {
    ipv4option_sr_t sr;
    uint32_t addr1, addr2;
    uint32_t addr3, addr4;

    ipv4option_sr_init(&sr);

    addr1 = 0xAAAAAAAA;
    addr2 = 0xBBBBBBBB;
    ipv4option_sr_push_address(&sr, addr1);
    ipv4option_sr_push_address(&sr, addr2);


    addr3 = 0xCCCCCCCC;
    addr4 = 0xDDDDDDDD;
    ipv4option_sr_set_address(&sr, 0, addr3);
    soft_assert_equal_int(sr.route[0], addr3);
    ipv4option_sr_set_address(&sr, 1, addr4);
    soft_assert_equal_int(sr.route[1], addr4);

    ipv4option_sr_set_address(&sr, 3, 0x01ABCDEF);
    soft_assert_equal_int(sr.route[3], 0);
}

void test_ipv4option_sr() {
    test_ipv4option_sr_init();
    test_ipv4option_sr_set_type();
    test_ipv4option_sr_push_address();
    test_ipv4option_sr_pop_address();
    test_ipv4option_sr_set_address();
}
