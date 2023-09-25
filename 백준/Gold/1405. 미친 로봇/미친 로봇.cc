#include<stdio.h>
double percent[4];
int time = 0;

double result = 0;

int visited[30][30] = {0};
int dy[] = {0,0,-1,1};
int dx[] = {1,-1,0,0};


void dfs(int node, int y, int x, double p) {

	if (node == time) {
		result += p;
		return;
	}
	for (int i = 0; i < 4; i++) {
		if (percent[i] == 0)continue;
		int ny = y + dy[i];
		int nx = x + dx[i];
		if (visited[ny][nx]) continue;
		visited[ny][nx] = 1;
		dfs(node + 1, ny, nx, p*percent[i]);
		visited[ny][nx] = 0;
	}
}

int main()
{
	// 동, 서, 남, 북
	double Input[4];
	scanf("%d %lf %lf %lf %lf", &time, &Input[0], &Input[1], &Input[2], &Input[3]);
	for (int i = 0; i < 4; i++) {
		percent[i] = Input[i] / 100;
	}
	visited[15][15] = 1;
	dfs(0, 15,15, 1);

	printf("%0.18f", result);
}