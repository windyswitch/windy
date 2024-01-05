#include <stdio.h>
#include <stdlib.h>

// �ϲ����������������λ�����Һ���
float findMedianSortedArrays(int *a, int *b, int n) {
    int min_index = 0, max_index = n, i, j;
    float median;
    
    while (min_index <= max_index) {
        i = (min_index + max_index) / 2;
        j = n - i;
        
        if (i < n && j > 0 && b[j - 1] > a[i]) {
            min_index = i + 1;
        } else if (i > 0 && j < n && a[i - 1] > b[j]) {
            max_index = i - 1;
        } else {
            // �ﵽ�������
            if (i == 0) {
                median = b[j - 1];
            } else if (j == 0) {
                median = a[i - 1];
            } else {
                median = a[i - 1] > b[j - 1] ? a[i - 1] : b[j - 1];
            }
            break;
        }
    }
    
    // ���������ܳ���Ϊ���������
    if ((n + n) % 2 == 1)
        return median;
    
    // ���������ܳ���Ϊż�������
    if (i == n) {
        return (median + b[0]) / 2.0;
    } else if (j == n) {
        return (median + a[0]) / 2.0;
    }
    return (median + (a[i] < b[j] ? a[i] : b[j])) / 2.0;
}

// ���û���ʾ����ȡ�������еĺ���
int *readSequence(int *length) {
    printf("��������������(����������ַ�����): ");
    
    int input, size = 0, capacity = 10;
    int *arr = (int *)malloc(capacity * sizeof(int));
    
    while (scanf("%d", &input) == 1) {
        if (size >= capacity) {
            capacity *= 2;
            arr = (int *)realloc(arr, capacity * sizeof(int));
        }
        arr[size++] = input;
    }
    while (getchar() != '\n'); // ������뻺����

    *length = size;
    return arr;
}

int main() {
    int lengthA, lengthB;
    
    printf("�������� A:\n");
    int *arrA = readSequence(&lengthA);
    
    printf("�������� B:\n");
    int *arrB = readSequence(&lengthB);
    
    if (lengthA != lengthB) {
        printf("�������г��Ȳ���ȣ��޷�������λ����\n");
        free(arrA);
        free(arrB);
        return 1;
    }

    // ����ʹ�ӡ��λ��
    float median = findMedianSortedArrays(arrA, arrB, lengthA);
    printf("�������е���λ����: %f\n", median);

    // �ͷ��ڴ�
    free(arrA);
    free(arrB);

    return 0;
}
