#include "../../include/ipv4/ipv4.h"



void ipv4_init(ipv4_t* ipv4) {
    ipv4->data_length = 0;
    ipv4header_init(&ipv4->header);
    ipv4option_init(&ipv4->option);
}
void ipv4_build_bytes(uint8_t* buffer, ipv4_t* ipv4) {
    ipv4header_t* header;
    ipv4option_t* option;

    header = &ipv4->header;
    option = &ipv4->option;
    header->length = 20 + option->length;
    ipv4header_to_bytes(header, buffer);
    ipv4option_to_bytes(buffer + 20, option);
    memcpy(buffer + header->length, ipv4->data, ipv4->data_length);
}
void ipv4_from_bytes(ipv4_t* ipv4, uint8_t* buffer, uint8_t size) {
    ipv4_init(ipv4);
    ipv4header_from_bytes(buffer, &ipv4->header);
    if(size > 20)
        ipv4option_from_bytes(&ipv4->option, buffer + 20, size - 20);
}

void ipv4_print_dec(ipv4_t* ipv4) {
    ipv4header_print_dec(&ipv4->header);
    ipv4option_print(&ipv4->option);
}
void ipv4_print_hex(ipv4_t* ipv4) {
    ipv4header_print_hex(&ipv4->header);
    ipv4option_print(&ipv4->option);
}
void ipv4_print_bin(ipv4_t* ipv4) {
    ipv4header_print_bin(&ipv4->header);
    ipv4option_print(&ipv4->option);
}

/* Header Checksum */
uint16_t ipv4header_get_16bit(const ipv4header_t* header, uint8_t index) {
    switch(index) {
        case 0: return header->version << 12 | header->length << 8 | header->type_of_service;
        case 1: return header->total_length;
        case 2: return header->identification;
        case 3: return header->flags << 13 | header->fragment_offset;
        case 4: return header->time_to_live << 8| header->protocol;
        case 5: return 0;
        case 6: return header->source >> 16;
        case 7: return header->source & 0xFFFF;
        case 8: return header->destination >> 16;
        case 9: return header->destination & 0xFFFF;
    }
    return 0;
}
uint16_t ipv4_compute_header_checksum(ipv4_t* ipv4) {
    uint32_t checksum;

    checksum = 0;
    for(int i = 0; i < 10; i++) {
        checksum += ipv4header_get_16bit(&ipv4->header, i);
    }
    for(size_t i = 0; i < ipv4->option.length / 2; i++) {
        checksum += ((uint16_t)ipv4->option.buffer[i * 2] << 8) | (uint16_t)ipv4->option.buffer[i * 2 + 1];
    }
    while((checksum & 0xFFFF0000) != 0) {
        checksum = (checksum & 0x0000FFFF) + (checksum >> 16);
    }

    return ~checksum;
}
