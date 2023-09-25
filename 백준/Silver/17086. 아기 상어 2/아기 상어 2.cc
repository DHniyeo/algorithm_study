#include <stdio.h>
#include <queue>
#include <tuple>
#include <string.h>
using namespace std;

int n, m;
int map[50][50];
int dy[] = {-1,-1,-1,0,0,1,1,1};
int dx[] = { -1,0,1,-1,1,-1,0,1 };


int bfs(int a, int b) {
	int visited[50][50] = {0};
	queue<pair<int, int>> q;
	q.push({ a,b });
	visited[a][b] = 1;
	while (!q.empty()) {
		int y, x;
		tie(y, x) = q.front(); q.pop();

		for (int i = 0; i < 8; i++) {
			int ny = y + dy[i];
			int nx = x + dx[i];
			if (ny >= n || nx >= m || ny < 0 || nx < 0) continue;
			if (visited[ny][nx] != 0) continue;
			if (map[ny][nx] == 0) {
				visited[ny][nx] = visited[y][x] + 1;
				q.push({ ny,nx });
			}
			else {
				return visited[y][x];
			}
		}

	}

	return 0;
}


int main()
{
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf(" %d", &map[i][j]);
		}
	}

	int max = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (map[i][j] == 0) {
				int tmp = bfs(i, j);
				if (max < tmp) {
					max = tmp;
				}
			}
		}
	}

	printf("%d", max);


}