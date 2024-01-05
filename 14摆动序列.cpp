#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool isWiggleSequence(int nums[], int n) {
    if (n < 2) {
        return true;
    }
    
    int prevDiff = nums[1] - nums[0];
    int count = prevDiff != 0;
    
    for (int i = 2; i < n; i++) {
        int diff = nums[i] - nums[i-1];
        if ((diff > 0 && prevDiff <= 0) || (diff < 0 && prevDiff >= 0)) {
            count++;
            prevDiff = diff;
        }
    }
    
    return count > 1;
}

int main() {
    int capacity = 10; // �趨�������󳤶�
    int *nums = (int*)malloc(capacity * sizeof(int)); // �� C++ ����Ҫ��ʽ����ת��
    int n = 0;
    
    printf("�������������е�Ԫ�أ����������ϣ�������-1:\n ");
    int num;
    while (scanf("%d", &num) == 1 && num != -1) {
        if (n == capacity) { // ���������������Ҫ����
            capacity *= 2;
            nums = (int*)realloc(nums, capacity * sizeof(int)); // �� C++ ����Ҫ��ʽ����ת��
        }
        nums[n++] = num;
    }
    
    if (isWiggleSequence(nums, n)) {
        printf("�ǰڶ����С�\n");
    } else {
        printf("�ǰڶ����У���Ҫɾ�� %d ��Ԫ�ء�\n", n - 2);
    }
    
    free(nums);
    return 0;
}
