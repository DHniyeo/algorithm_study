#include<stdio.h>
#define max(x,y) x>y?x:y
int score[301] = { 0 };
int memo[301] = { 0 };
int dp(int n) {
	memo[1] = score[1];
	memo[2] = score[1] + score[2];
	memo[3] = max(score[1] + score[3], score[2] + score[3]);
	
	for (int i = 4; i <= n; i++) {
		memo[i] = max(memo[i - 3] + score[i - 1] + score[i], memo[i - 2] + score[i]);
	}
	return memo[n];
}

int main() {
	int n;

	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf(" %d", &score[i]);
	}
	printf("%d", dp(n));
}