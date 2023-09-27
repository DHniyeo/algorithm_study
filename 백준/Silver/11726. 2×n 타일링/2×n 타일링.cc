#include<stdio.h>
#define max(x,y) x>y?x:y
int memo[1001] = { 0, 1, 2 };
int dp(int n) {
	for (int i = 3; i <= n; i++) {
		memo[i] = (memo[i - 1] + memo[i - 2]) %10007;
	}
	return memo[n];
}

int main() {
	int n;
	scanf("%d", &n);
	printf("%d", dp(n));
}