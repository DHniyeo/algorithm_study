#include <stdio.h>
#include <queue>
#include <algorithm>

using namespace std;
int visited[100][100] = { 0 };
int n, m, k;
int map[100][101] = {0};
int dy[] = { -1,1,0,0 };
int dx[] = { 0,0,-1,1 };
struct info {
	int y;
	int x;
	int cnt;
};


int bfs(int y, int x) {
	visited[y][x] = 1;
	queue<info> q;
	q.push({ y,x,1 });

	int cnt = 0;
	while (!q.empty()) {
		info loc = q.front(); q.pop();
		cnt ++;
		for (int i = 0; i < 4; i++) {
			int ny = loc.y + dy[i];
			int nx = loc.x + dx[i];
			if (ny >= n || nx >= m || ny < 0 || nx < 0) continue;
			if (visited[ny][nx] == 1) continue;
			if (map[ny][nx] == 0) continue;
			visited[ny][nx] = 1;
			q.push({ ny,nx, loc.cnt + 1 });
		}
	}
	return cnt;
}

int main()
{

	scanf("%d %d %d", &n, &m, &k);
	getchar();
	
	for (int i = 0; i < k; i++) {
		int y, x;
		scanf("%d %d",&y, &x);
		getchar();
		map[y-1][x-1] = 1; // 음식물 쓰레기 위치
	}

	int max = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (visited[i][j] == 1) continue;
			if (map[i][j] == 0) continue;
			int result = bfs(i,j);
			if (result > max) {
				max = result;
			}
		}
	}
	
	printf("%d\n", max);

}