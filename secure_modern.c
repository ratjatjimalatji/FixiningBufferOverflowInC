/* secure_modern.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void secret_action() {
    printf("Secret action triggered! (This indicates overflow smashed return address)\n");
}

void process_input(const char *label) {
    char buf[64];
    char small_msg[16];        
    printf("%s: enter text> ", label);

    char temp[256];
    if (!fgets(temp, sizeof(temp), stdin)) {
        return;
    }

    temp[strcspn(temp, "\n")] = '\0';

    snprintf(buf, sizeof(buf), "%s", temp);
    snprintf(small_msg, sizeof(small_msg), "OK");

    printf("Processed: %s\n", buf);
}

int main(int argc, char **argv) {
    printf("I hold all the keys!\n");
    process_input("Stage 1");
    printf("Program completed normally.\n");
    return 0;
}