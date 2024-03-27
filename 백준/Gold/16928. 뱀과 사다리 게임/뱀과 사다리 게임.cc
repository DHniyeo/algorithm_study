#include <stdio.h>
#include <queue>

using namespace std;
int n, m;
int cnt = 0;
int move_map[101];
int visited[101];

int main() {
	scanf("%d %d", &n, &m);
	// 이동하는 구간 저장
	for (int i = 0; i < n + m; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		move_map[x] = y;
	}
	queue<int> q;
	q.push(1);

	int result = 0;
	while (!q.empty()) {
		int now = q.front();
		q.pop();
		if (now == 100) {
			result = visited[now];
			break;
		}
		for (int i = 1; i <= 6; i++) {
			int next = now + i;
			while (move_map[next] != 0) {
				next = move_map[next];
			}
			if (next > 100) continue;
			if (visited[next] != 0)	continue;
			visited[next] = visited[now] + 1;
			q.push(next);
		}
	}
	printf("%d", result);
}