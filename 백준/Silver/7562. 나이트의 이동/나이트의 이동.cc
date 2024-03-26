#include <stdio.h>
#include <queue>
#include <string.h>
using namespace std;
struct info {
	int y, x, cnt;
};
int dy[] = { -2,-2,-1,-1,1,1,2,2 };
int dx[] = { 1,-1,-2,2,-2,2,1,-1 };

int visited[301][301];
void init() {
	memset(visited, 0, sizeof(visited));
}

int main() {
	int tc;
	int l;
	info start, end;
	scanf("%d", &tc);
	for (int T = 1; T <= tc; T++) {
		init();
		start.cnt = 0;
		scanf(" %d", &l);
		scanf(" %d %d", &start.y, &start.x);
		scanf(" %d %d", &end.y, &end.x);

		queue<info> q;
		q.push(start);
		visited[start.y][start.x] = 1;

		int result = 0;
		while (!q.empty()) {
			info tmp = q.front(); q.pop();

			if (tmp.y == end.y && tmp.x == end.x) {
				result = tmp.cnt;
				break;
			}
			for (int i = 0; i < 8; i++) {
				int ny = tmp.y + dy[i];
				int nx = tmp.x + dx[i];
				if (ny >= l || nx >= l || nx < 0 || ny < 0) continue;
				if (visited[ny][nx] == 1) continue;
				visited[ny][nx] = 1;
				q.push({ ny, nx, tmp.cnt + 1 });
			}
		}
		printf("%d\n", result);
	}
}