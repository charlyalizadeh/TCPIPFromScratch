#include "../include/ipv4/ipv4option.h"
#include "soft_assert.h"
#include <stdlib.h>
#include <time.h>


// Init
void test_ipv4option_init() {
    ipv4option_t option;

    ipv4option_init(&option);
    soft_assert_equal_int(option.nb, 0);
    soft_assert_equal_int(option.length, 0);
}

// No option
void test_ipv4option_push_no_option() {
    ipv4option_t option;
    uint8_t type;

    ipv4option_init(&option);

    ipv4option_push_no_option(&option);
    soft_assert_equal_int(option.nb, 1);
    soft_assert_equal_int(option.length, 1);
    soft_assert_equal_int(option.option_lengths[0], 1);
    soft_assert_equal_int(option.buffer[0], 1);

    ipv4option_push_no_option(&option);
    soft_assert_equal_int(option.nb, 2);
    soft_assert_equal_int(option.length, 2);
    soft_assert_equal_int(option.option_lengths[0], 1);
    soft_assert_equal_int(option.option_lengths[1], 1);
    soft_assert_equal_int(option.buffer[0], 1);
    soft_assert_equal_int(option.buffer[1], 1);

    type = ipv4option_pop_option(&option);
    soft_assert_equal_int(type, 1);
    soft_assert_equal_int(option.nb, 1);
    soft_assert_equal_int(option.length, 1);
    soft_assert_equal_int(option.option_lengths[0], 1);
    soft_assert_equal_int(option.buffer[0], 1);

    type = ipv4option_pop_option(&option);
    soft_assert_equal_int(type, 1);
    soft_assert_equal_int(option.nb, 0);
    soft_assert_equal_int(option.length, 0);

    ipv4option_push_no_option(&option);
    soft_assert_equal_int(option.nb, 1);
    soft_assert_equal_int(option.length, 1);
    soft_assert_equal_int(option.option_lengths[0], 1);
    soft_assert_equal_int(option.buffer[0], 1);
}

// Source route
void test_ipv4option_push_sr() {
    ipv4option_t option;
    ipv4option_sr_t sr;
    uint32_t addr1, addr2;

    ipv4option_init(&option);
    ipv4option_sr_init(&sr);

    addr1 = 0xAAAAAAAA;
    addr2 = 0xBBBBBBBB;
    ipv4option_sr_set_type(&sr, LSRR);
    ipv4option_sr_push_address(&sr, addr1);
    ipv4option_sr_push_address(&sr, addr2);

    ipv4option_push_sr(&option, &sr);
    soft_assert_equal_int(option.nb, 1);
    soft_assert_equal_int(option.option_lengths[0], sr.length);
    soft_assert_equal_int(option.buffer[0], LSRR);
    soft_assert_equal_int(option.buffer[1], sr.length);
    soft_assert_equal_int(option.buffer[2], sr.pointer);

    soft_assert_equal_int(option.buffer[3], addr1 >> 24);
    soft_assert_equal_int(option.buffer[4], (addr1 >> 16) & 0xFF);
    soft_assert_equal_int(option.buffer[5], (addr1 >> 8) & 0xFF);
    soft_assert_equal_int(option.buffer[6], addr1 & 0xFF);

    soft_assert_equal_int(option.buffer[7], addr2 >> 24);
    soft_assert_equal_int(option.buffer[8], (addr2 >> 16) & 0xFF);
    soft_assert_equal_int(option.buffer[9], (addr2 >> 8) & 0xFF);
    soft_assert_equal_int(option.buffer[10], addr2 & 0xFF);
}

// Stream id
void test_ipv4option_stream_id(ipv4option_t* option, uint16_t stream_id, size_t offset) {
    soft_assert_equal_int(option->buffer[offset], 136);
    soft_assert_equal_int(option->buffer[offset + 1], 4);
    soft_assert_equal_int(option->buffer[offset + 2], (stream_id & 0x00FF));
    soft_assert_equal_int(option->buffer[offset + 3], (stream_id >> 8));
}
void test_ipv4option_push_stream_id() {
    ipv4option_t option;
    uint16_t stream_id1, stream_id2;
    uint8_t type;

    srand(time(NULL));
    ipv4option_init(&option);

    stream_id1 = rand() % (uint16_t)0xFFFF;
    ipv4option_push_stream_id(&option, stream_id1);
    soft_assert_equal_int(option.nb, 1);
    soft_assert_equal_int(option.length, 4);
    soft_assert_equal_int(option.option_lengths[0], 4);
    test_ipv4option_stream_id(&option, stream_id1, 0);

    stream_id2 = rand() % (uint16_t)0xFFFF;
    ipv4option_push_stream_id(&option, stream_id2);
    soft_assert_equal_int(option.nb, 2);
    soft_assert_equal_int(option.length, 8);
    soft_assert_equal_int(option.option_lengths[0], 4);
    soft_assert_equal_int(option.option_lengths[1], 4);
    test_ipv4option_stream_id(&option, stream_id1, 0);
    test_ipv4option_stream_id(&option, stream_id2, 4);

    type = ipv4option_pop_option(&option);
    soft_assert_equal_int(type, 136);
    soft_assert_equal_int(option.nb, 1);
    soft_assert_equal_int(option.length, 4);
    soft_assert_equal_int(option.option_lengths[0], 4);
    test_ipv4option_stream_id(&option, stream_id1, 0);

    type = ipv4option_pop_option(&option);
    soft_assert_equal_int(type, 136);
    soft_assert_equal_int(option.nb, 0);
    soft_assert_equal_int(option.length, 0);

    stream_id1 = rand() % (uint16_t)0xFFFF;
    ipv4option_push_stream_id(&option, stream_id1);
    soft_assert_equal_int(option.nb, 1);
    soft_assert_equal_int(option.length, 4);
    soft_assert_equal_int(option.option_lengths[0], 4);
    test_ipv4option_stream_id(&option, stream_id1, 0);
}
