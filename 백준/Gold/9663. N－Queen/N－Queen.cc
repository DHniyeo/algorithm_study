#include<stdio.h>

int N;
int dy[] = { -1,-1,-1,0,0,1,1,1 };
int dx[] = { -1,1,0,-1,1,-1,1,0 };
int cnt = 0;
int visited[15][15] = { 0 };
int x_visited[15] = { 0 };
bool CanGo(int node, int column) {
	int y = node;
	int x = column;
	for (int i = 0; i < N; i++) {
		if (visited[y][i]) return false;
		if (visited[i][x]) return false;
		if (y - i >= 0 && x - i >= 0 && visited[y - i][x - i]) return false;
		if (y + i < N && x + i < N && visited[y + i][x + i]) return false;
		if (y - i >= 0 && x + i < N && visited[y - i][x + i]) return false;
		if (y + i < N && x - i >= 0 && visited[y + i][x - i]) return false;
	}
	return true;
}
void dfs(int node) {
	if (node == N) {
		cnt++;
		return;
	}
	for (int i = 0; i < N; i++) {
		if (x_visited[i] == 1) continue;
		if (CanGo(node, i)) {
			x_visited[i] = 1;
			visited[node][i] = 1;
			dfs(node + 1);
			visited[node][i] = 0;
			x_visited[i] = 0;
		}
	}
}
int main() {
	scanf("%d", &N);

	dfs(0);
	printf("%d\n", cnt);
}