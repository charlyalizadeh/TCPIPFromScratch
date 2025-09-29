#include "test_ipv4_checksum.c"

int main(void) {
    printf("====RUNNING TESTS====\n");
    printf("- IPV4 checksum computation: ");
    fflush(stdout);
    test_ipv4_checksum();
    printf("All test passed.\n");
    return 0;
}
