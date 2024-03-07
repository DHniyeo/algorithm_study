#include<stdio.h>
int point[1001][1001];
int visited[1001];
int cnt = 0;

int n, m;
void dfs(int num) {
	for (int i = 1; i <= n; i++) {
		if (point[num][i] == 1) {
			if (visited[i] == 1) continue;
			visited[i] = 1;
			dfs(i);
		}
	}
}
int main() {
	scanf("%d %d", &n, &m);
	for (int i = 0; i < m; i++) {
		int left, right;
		scanf(" %d %d", &left, &right);
		point[left][right] = 1;
		point[right][left] = 1;
	}

	for (int i = 1; i <= n; i++) {
		if (visited[i] == 1) continue;
		dfs(i);
		cnt++;
	}
	printf("%d",cnt);
}