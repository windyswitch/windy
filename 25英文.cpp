#include <stdio.h>
#include <string.h>
#include <ctype.h>

void formatSentence(char *input) {
    int len = strlen(input);
    
    // Remove leading spaces
    while (len > 0 && isspace(input[0])) {
        memmove(input, input + 1, len);
        len--;
    }
    
    // Remove trailing spaces
    while (len > 0 && isspace(input[len - 1])) {
        input[len - 1] = '\0';
        len--;
    }
    
    // Remove extra spaces between words
    for (int i = 0; i < len - 1; i++) {
        if (isspace(input[i]) && isspace(input[i + 1])) {
            memmove(input + i, input + i + 1, len - i);
            len--;
            i--;
        }
    }
}

int main() {
    char input[1000];
    
    // Read input
    printf("Enter an English sentence: ");
    fgets(input, sizeof(input), stdin);
    
    // Format the sentence
    formatSentence(input);
    
    // Output the result
    printf("Formatted sentence: %s\n", input);
    
    return 0;
}
