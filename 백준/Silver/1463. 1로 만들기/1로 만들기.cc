#include<stdio.h>
#define min(x,y) x>y?y:x
using namespace std;

int memo[1000001] = {0};
int dp(int n) {
	if (n == 1) {
		return memo[n];
	}
	for (int i = 2; i <= n; i++) {
		memo[i] = memo[i - 1] + 1;
		if (i % 2 == 0) memo[i] = min(memo[i], memo[i / 2] + 1);
		if (i % 3 == 0) memo[i] = min(memo[i], memo[i / 3] + 1);
	}
	return memo[n];
}

int main()
{
	int n;
	scanf("%d", &n);
	printf("%d", dp(n));
}