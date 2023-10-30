#include<stdio.h>
#include<queue>
using namespace std;

struct lc {
	int y;
	int x;
	int cnt;
};
int n, m;
int map[1001][1001];
int dy[] = { -1, 1, 0, 0 };
int dx[] = { 0, 0, -1, 1 };
int IsThereRaw() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (map[i][j] == 0) {
				return 1;
			}
		}
	}
	return 0;
}
int main() {

	scanf("%d %d", &m, &n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf(" %d", &map[i][j]);
		}
	}
	queue<lc> q;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (map[i][j] == 1) {
				q.push({ i,j,0});
			}
		}
	}
	int result = -1;
	int cnt_time = -1;
	while (!q.empty()) {
		lc tmp = q.front(); q.pop();
		if (cnt_time != tmp.cnt) {
			cnt_time = tmp.cnt;
			if (!IsThereRaw()) {
				result = cnt_time;
				break;
			}
		}
		
		for (int i = 0; i < 4; i++) {
			int ny = tmp.y + dy[i];
			int nx = tmp.x + dx[i];

			if (ny >= n || nx >= m || ny < 0 || nx < 0) continue;
			if (map[ny][nx] == 1 || map[ny][nx] == -1) continue;
			map[ny][nx] = 1;
			q.push({ ny, nx, tmp.cnt + 1 });
		}
	}
	printf("%d\n", result);


}