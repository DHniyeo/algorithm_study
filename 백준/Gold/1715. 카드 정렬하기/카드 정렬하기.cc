#include <stdio.h>
#include <algorithm>
#include <queue>


int main() {

	int n;
	std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		int tmp;
		scanf(" %d", &tmp);
		pq.push(tmp);
	}

	int sum = 0;
	if (n == 1) {
		printf("0\n");
		return 0;
	}

	while (!pq.empty()) {
		int tmp1 = pq.top(); pq.pop();
		int tmp2 = pq.top(); pq.pop();
		int tmp_sum = tmp1 + tmp2;
		sum += tmp_sum;
		if (pq.empty()) break;
		pq.push(tmp_sum);
	}

	printf("%d\n", sum);

}