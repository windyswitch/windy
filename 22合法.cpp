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

    printf("������һ���ַ�����: ");
    scanf("%s", sequence);

    length = 0;
    while (sequence[length] != '\0') {
        length++;
    }

    if (isValidOutSequence(sequence, length)) {
        printf("���� \"%s\" ���ǺϷ��ĳ�ջ���С�\n", sequence);
    } else {
        printf("���� \"%s\" �ǺϷ��ĳ�ջ���С�\n", sequence);
    }

    return 0;
}
