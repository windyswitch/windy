#include <stdio.h>

void findMinCoins(int coins[], int n, int amount) {
    int coinCount = 0;

    printf("Change amount: %d\n", amount);

    for (int i = 0; i < n; i++) {
        while (amount >= coins[i]) {
            amount -= coins[i];
            coinCount++;
            printf("Use %d cent coin\n", coins[i]);
        }
    }

    printf("Total number of coins used: %d\n", coinCount);
}

int main() {
    int coins[] = {25, 10, 5, 1};
    int n = sizeof(coins) / sizeof(coins[0]);

    int amount;
    printf("Enter the change amount: ");
    scanf("%d", &amount);

    findMinCoins(coins, n, amount);

    return 0;
}
