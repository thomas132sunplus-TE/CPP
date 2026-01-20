#include <stdio.h>

int main() {
    char buf[10];  // Buffer to store the input
    int num_char_read;

    printf("Enter a sequence of characters (1-5): ");
    
    // Read characters from the input that are within the range '1' to '5'
    // The return value of scanf is the number of elements successfully read
    num_char_read = scanf("%[1-5]", buf);
    
    // Check if the reading was successful
    if (num_char_read > 0) {
        // If input was read successfully
        printf("You entered: %s\n", buf);
    } else {
        // If input was not read successfully or is invalid
        printf("Invalid input. Please enter a sequence of characters in the range 1-5.\n");
    }

    // Clear any remaining input to prevent interference with further input
    while (getchar() != '\n') {
        // Consume any remaining characters on the line
    }

    return 0;
}
