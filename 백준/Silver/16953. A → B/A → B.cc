#include <stdio.h>
#include <algorithm>
#include <queue>
#define min(a,b) a>b?b:a
using namespace std;

int MIN = 1e9;
void dfs(long long a, long long b, int cnt) {
	if (a == b) {
		MIN = min(MIN, cnt);
		return;
	}
	if (a > b) {
		return;
	}
	dfs(a * 2, b, cnt + 1);
	dfs(a * 10 + 1, b, cnt + 1);
}

int main() {
	long long from, to;
	scanf("%lld %lld", &from, &to);
	getchar();
	dfs(from, to, 1);
	// 변화 하지 않았다면??
	if (MIN == 1e9) {
		printf("-1\n");
	}
	else {
		printf("%d\n", MIN);
	}
}