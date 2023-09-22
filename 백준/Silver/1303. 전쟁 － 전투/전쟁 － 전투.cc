#include <stdio.h>
#include <queue>
#include <algorithm>

using namespace std;



int n, m;
char map[101][101];
int visited[100][100] = { 0 };
int dy[] = { 0,0,-1,1 };
int dx[] = { -1,1,0,0 };
int dfs(int y, int x, char c, int cnt) {
	visited[y][x] = 1;
	
	for (int i = 0; i < 4; i++) {
		int ny = y + dy[i];
		int nx = x + dx[i];
		if (ny >= m || nx >= n || ny < 0 || nx < 0) continue;
		if (visited[ny][nx] == 1) continue;
		if (map[ny][nx] != c) continue;
		cnt = dfs(ny, nx, c, cnt + 1);
	}
	return cnt;
}

int bfs(int y, int x, char c, int cnt) {
	visited[y][x] = 1;
	queue<pair<int, int>> q;
	q.push({ y,x });

	while (!q.empty()) {
		pair<int, int> tmp = q.front(); q.pop();
		
		for (int i = 0; i < 4; i++) {
			int ny = tmp.first + dy[i];
			int nx = tmp.second + dx[i];
			if (ny >= m || nx >= n || ny < 0 || nx < 0) continue;
			if (visited[ny][nx] == 1) continue;
			if (map[ny][nx] != c) continue;
			visited[ny][nx] = 1;
			q.push({ ny,nx });
			cnt++;
		}
	}
	return cnt;
}


int main()
{
	
	int w_result = 0;
	int b_result = 0;
	
	scanf("%d %d", &n, &m);
	getchar();
	for (int i = 0; i < m; i++) {
		scanf("%s", map[i]);
		getchar();
	}

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (visited[i][j]) continue;
			int sum = dfs(i, j, map[i][j], 1);
			//int sum = bfs(i, j, map[i][j], 1);
			if (map[i][j] == 'W')
			{
				w_result = w_result + sum * sum;
			}
			else if (map[i][j] == 'B')
			{
				b_result = b_result + sum * sum;
			}
		}
	}
	printf("%d %d\n", w_result, b_result);


}