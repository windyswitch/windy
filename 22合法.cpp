#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 100

bool isValidOutSequence(char sequence[], int length) {
    char stack[MAX_SIZE];
    int top = -1;

    for (int i = 0; i < length; i++) {
        if (sequence[i] == 'a') {
            stack[++top] = 'a';
        } else {
            while (top >= 0 && stack[top] == 'e') {
                top--;
            }
            if (top >= 0 && stack[top] == sequence[i] - 1) {
                top--;
            } else {
                return false;
            }
        }
    }

    return top == -1;
}

int main() {
    char sequence[MAX_SIZE];
    int length;

    printf("请输入一个字符序列: ");
    scanf("%s", sequence);

    length = 0;
    while (sequence[length] != '\0') {
        length++;
    }

    if (isValidOutSequence(sequence, length)) {
        printf("序列 \"%s\" 不是合法的出栈序列。\n", sequence);
    } else {
        printf("序列 \"%s\" 是合法的出栈序列。\n", sequence);
    }

    return 0;
}
