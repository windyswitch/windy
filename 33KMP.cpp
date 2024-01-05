#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int kmp_search(const char *text, const char *pattern) {
    int len_text = strlen(text);
    int len_pattern = strlen(pattern);

    int *lps = (int *)malloc(sizeof(int) * len_pattern);
    int i = 1, j = 0;

    while (i < len_pattern) {
        if (pattern[i] == pattern[j]) {
            j++;
            lps[i] = j;
            i++;
        } else {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }

    i = 0;
    j = 0;
    while (i < len_text) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == len_pattern) {
            free(lps);
            return i - j;
        } else if (i < len_text && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }

    free(lps);
    return -1;
}

int main() {
    char text[100];
    char pattern[50];

    printf("Enter the target string: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';

    printf("Enter the pattern string: ");
    fgets(pattern, sizeof(pattern), stdin);
    pattern[strcspn(pattern, "\n")] = '\0';

    int result = kmp_search(text, pattern);

    if (result != -1) {
        printf("Pattern found at position %d\n", result);
    } else {
        printf("Pattern not found\n");
    }

    return 0;
}
