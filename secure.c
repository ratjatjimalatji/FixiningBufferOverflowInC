
/* secure.c
 * Fixed version with comprehensive bounds checking.
 * Educational example demonstrating secure coding practices.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Define buffer sizes as constants for maintainability */
#define BUF_SIZE 64
#define SMALL_MSG_SIZE 16
#define TEMP_SIZE 256

void secret_action() {
    printf("Secret action triggered! (This indicates overflow smashed return address)\n");
}

void process_input(const char *label) {
    char buf[BUF_SIZE];
    char small_msg[SMALL_MSG_SIZE];
    char temp[TEMP_SIZE];
    
    /* Initialize buffers to prevent undefined behavior */
    memset(buf, 0, BUF_SIZE);
    memset(small_msg, 0, SMALL_MSG_SIZE);
    memset(temp, 0, TEMP_SIZE);
    
    /* Bounds check: Validate label parameter */
    if (label == NULL) {
        fprintf(stderr, "Error: NULL label provided\n");
        return;
    }
    
    printf("%s: enter text> ", label);
    fflush(stdout);
    
    /* Bounds check: Read with size limit for temp */
    if (!fgets(temp, TEMP_SIZE, stdin)) {
        fprintf(stderr, "Error: Failed to read input\n");
        return;
    }
    
    /* Remove newline character safely */
    size_t temp_len = strcspn(temp, "\n");
    if (temp_len < TEMP_SIZE) {
        temp[temp_len] = '\0';
    }
    
    /* Bounds check: Validate temp length before copying to buf */
    size_t input_len = strlen(temp);
    if (input_len >= BUF_SIZE) {
        fprintf(stderr, "Warning: Input too long (%zu chars), truncating to %d chars\n", 
                input_len, BUF_SIZE - 1);
    }
    
    /* Safe copy with explicit bounds checking */
    size_t copy_len = (input_len < BUF_SIZE - 1) ? input_len : BUF_SIZE - 1;
    memcpy(buf, temp, copy_len);
    buf[copy_len] = '\0';
    
    /* Bounds check: Verify buf is properly terminated */
    if (buf[BUF_SIZE - 1] != '\0') {
        buf[BUF_SIZE - 1] = '\0';
        fprintf(stderr, "Warning: Buffer termination enforced\n");
    }
    
    /* Bounds check: Safe copy to small_msg with size validation */
    const char *status_msg = "OK";
    size_t status_len = strlen(status_msg);
    
    if (status_len >= SMALL_MSG_SIZE) {
        fprintf(stderr, "Error: Status message too large for buffer\n");
        return;
    }
    
    memcpy(small_msg, status_msg, status_len);
    small_msg[status_len] = '\0';
    
    /* Bounds check: Verify small_msg is properly terminated */
    if (small_msg[SMALL_MSG_SIZE - 1] != '\0') {
        small_msg[SMALL_MSG_SIZE - 1] = '\0';
    }
    
    /* Safe output using bounded format */
    printf("Processed: %.*s\n", BUF_SIZE - 1, buf);
    
    /* Runtime assertion: Verify buffer integrity */
    if (strlen(buf) >= BUF_SIZE) {
        fprintf(stderr, "CRITICAL: Buffer integrity violation detected!\n");
        abort();
    }
}

int main(int argc, char **argv) {
    printf("I hold all the keys!\n");
    
    /* Bounds check: Validate command line arguments if used */
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            if (argv[i] == NULL) {
                fprintf(stderr, "Error: NULL argument at position %d\n", i);
                return 1;
            }
        }
    }
    
    process_input("Stage 1");
    printf("Program completed normally.\n");
    return 0;
}
