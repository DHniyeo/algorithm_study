#include <stdio.h>
#include <algorithm>
#include <queue>
using namespace std;
int main() {
	
	int n;
	scanf("%d", &n);
	getchar();
	int zeroflag = 0;
	priority_queue<int, vector<int>> plus_pq;
	priority_queue<int, vector<int>> minus_pq;
	
	for (int i = 0; i < n; i++) {
		int tmp;
		scanf("%d", &tmp);
		getchar();
		if (tmp == 0) {
			zeroflag = 1;
		}
		else if (tmp > 0) {
			plus_pq.push(tmp);
		}
		else if (tmp < 0) {
			tmp = -tmp;
			minus_pq.push(tmp);
		}
	}
	long long result = 0;
	while (!plus_pq.empty()) { // plus_queue 계산 처리하기
		long long tmp1 = plus_pq.top(); plus_pq.pop();
		if (tmp1 == 1) { // 1일경우 계산에서 곱셈에서 제외
			result += 1;
			continue;
		}
		if (plus_pq.empty()) { // 1개 빼고 빈다는 것은 plus queue가 홀수 개였다는것.
			result += tmp1;
			break;
		}
		long long tmp2 = plus_pq.top(); plus_pq.pop();
		if (tmp2 == 1) { // 1일경우 계산에서 곱셈에서 제외
			result += (tmp1+ 1);
			continue;
		}
		result += tmp1 * tmp2;
	}
	// -가 홀수 인경우
	// -끼리 곱하고 남은 1개(-가 최소인 값)를 0이 있으면 곱하고 아닐경우는 내비 두는게 이득.

	// -가 짝수개 있는경우
	// 무조건 - 끼리 곱하는게 이득 (0이 있든없든)
	while (!minus_pq.empty()) {
		long long tmp1 = minus_pq.top(); minus_pq.pop();
		if (minus_pq.empty()) { // 1개 빼고 빈다는 것은 plus queue가 홀수 개였다는것.
			if (zeroflag == 0) {
				result -= tmp1;
			}
			break;
		}
		long long tmp2 = minus_pq.top(); minus_pq.pop();
		result += tmp1 * tmp2;
	}
	printf("%lld\n", result);


	
}