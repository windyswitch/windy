#include <stdio.h>

// ��������
void decimalToBinary(int num);
void decimalToOctal(int num);
void decimalToHexadecimal(int num);

int main() {
    int decimalNum;
    
    // ���û������ֶ�����һЩ����
    printf("������һ��ʮ������: ");
    scanf("%d", &decimalNum); // �����û������ʮ������
    
    printf("ʮ������ %d ��ת��������£�\n", decimalNum);
    printf("������: ");
    decimalToBinary(decimalNum);
    printf("\n");
    printf("�˽���: ");
    decimalToOctal(decimalNum);
    printf("\n");
    printf("ʮ������: ");
    decimalToHexadecimal(decimalNum);
    printf("\n");

    return 0;
}

// ����ʵ��
void decimalToBinary(int num) {
    if (num > 0) {
        decimalToBinary(num / 2);
        printf("%d", num % 2);
    } else if (num == 0) {
        return;
    } else {
        printf("0");
    }
}

void decimalToOctal(int num) {
    if (num > 0) {
        decimalToOctal(num / 8);
        printf("%d", num % 8);
    } else if (num == 0) {
        return;
    } else {
        printf("0");
    }
}

void decimalToHexadecimal(int num) {
    char hexDigits[] = "0123456789ABCDEF";
    if (num > 0) {
        decimalToHexadecimal(num / 16);
        printf("%c", hexDigits[num % 16]);
    } else if (num == 0) {
        return;
    } else {
        printf("0");
    }
}
