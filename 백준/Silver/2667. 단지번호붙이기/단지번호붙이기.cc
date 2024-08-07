#include<stdio.h>
#include<algorithm>
#include<queue>
using namespace std;

int n;
char map[25][26];
int visited[25][25];
priority_queue<int, vector<int>, greater<int>> pq;

int dy[] = { -1,1,0,0 };
int dx[] = { 0,0,-1,1 };

int dfs(int y, int x, int cnt) {

	visited[y][x] = 1;
	for (int i = 0; i < 4; i++) {
		int ny = y + dy[i];
		int nx = x + dx[i];
		if (ny >= n || nx >= n || ny < 0 || nx < 0) continue;
		if (visited[ny][nx] == 1) continue;
		if (map[ny][nx] == '0') continue;
		cnt = dfs(ny, nx, cnt + 1);
	}
	return cnt;
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf(" %s", map[i]);
	}

	int cnt = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (map[i][j] == '0') continue;
			if (visited[i][j] == 1) continue;
			pq.push(dfs(i, j, 1));
			cnt++;
		}
	}
	printf("%d\n", cnt);
	for (int i = 0; i < cnt; i++) {
		int tmp = pq.top(); pq.pop();
		printf("%d\n", tmp);
	}
}