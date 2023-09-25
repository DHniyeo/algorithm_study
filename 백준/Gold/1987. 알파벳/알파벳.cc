#include<iostream>

int R, C;
char map[20][21];
int visited[255];
int dy[] = { -1,1,0,0 };
int dx[] = { 0,0,-1,1 };
int max = 0;
void dfs(int y, int x, int cnt) {
	int way = 4;
	for (int i = 0; i < 4; i++) {
		int ny = y + dy[i];
		int nx = x + dx[i];
		if (ny >= R || nx >= C || ny < 0 || nx < 0 || visited[map[ny][nx]]) way--;
	}
	if (way == 0) {
		if (max < cnt) {
			max = cnt;
		}
		return;
	}
	for (int i = 0; i < 4; i++) {
		int ny = y + dy[i];
		int nx = x + dx[i];
		if (ny >= R || nx >= C || ny < 0 || nx < 0) continue;
		if (visited[map[ny][nx]]) continue;
		visited[map[ny][nx]] = 1;
		dfs(ny, nx, cnt + 1);
		visited[map[ny][nx]] = 0;
	}
}
int main() {
	scanf("%d %d", &R, &C);
	for (int i = 0; i < R; i++) {
		scanf(" %s", &map[i]);
	}
	visited[map[0][0]] = 1;
	dfs(0,0, 1);

	printf("%d\n", max);
}