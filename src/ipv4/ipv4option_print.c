#include "../../include/ipv4/ipv4option_print.h"


void ipv4option_print(ipv4option_t* option) {
    uint8_t offset;

    offset = 0;
    for(uint8_t i = 0; i < option->nb; i++) {
        printf("Option nb %u\n", i);
        printf("  Type: %u\n", option->buffer[offset]);
        printf("  Length: %u\n", option->option_lengths[i]);
        offset += option->option_lengths[i];
    }
    printf("Option total length: %u\n", option->length);
}
