#include "test_ipv4_checksum.c"
#include "test_ipv4option.c"
#include "soft_assert.h"

int main(void) {
    printf("====RUNNING TESTS====\n");

    // IPV4 option
    // // Init
    printf("- IPV4: Option (init)\n");
    test_ipv4option_init();
    // // No option
    printf("- IPV4: Option (no option)\n");
    test_ipv4option_push_no_option();
    // // Stream id
    printf("- IPV4: Option (stream id)\n");
    test_ipv4option_push_stream_id();

    // IPV4 Checksum
    printf("- IPV4: Checksum computation\n");
    test_ipv4_checksum();

    return soft_assert_failed;
}
