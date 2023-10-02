#include<stdio.h>

int n;
struct INFO {
	int T;
	int P;
};
INFO arr[20];
int memo[20];
int DP(int n) {

	int max = 0;
	// DP 테이블 생성
	for (int i = 1; i <= n; i++) {
		max = memo[i] > max ? memo[i] : max;
		if (arr[i].T + i > n + 1) continue;
		int tmp = max + arr[i].P; // 현재 최고 금액 + 해당 상담 후 받을 금액
		memo[arr[i].T + i] = memo[arr[i].T + i] < tmp ? tmp : memo[arr[i].T + i];
	}
	max = memo[n + 1] > max ? memo[n + 1] : max;
	return max;
}
int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf(" %d %d", &arr[i].T, &arr[i].P);
	printf("%d\n",DP(n));
}