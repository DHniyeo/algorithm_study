#include <stdio.h>
#include <queue>
#include <algorithm>

using namespace std;

int comp_num;
int input_num;
int visited[101]= {0};
int map[101][101] = {0};

struct info {
	int y;
	int x;
	int cnt;
};


int bfs(int node) {
	visited[node] = 1;
	

	return 0;
}
int dfs(int node, int cnt) {
	visited[node] = 1;
	
	for (int i = 1; i <= comp_num; i++) {
		if (visited[i] == 1) continue;
		if (map[node][i] == 0)continue;
		visited[i] = 1;
		cnt = dfs(i, cnt+1);
	}
	return cnt;
}

void input() {
	scanf("%d", &comp_num);
	getchar();
	scanf("%d", &input_num);
	getchar();
	for (int i = 0; i < input_num; i++) {
		int s, e;
		scanf("%d %d", &s, &e);
		getchar();
		map[s][e] = 1;
		map[e][s] = 1;
	}
}
int main()
{
	input();

	printf("%d\n", dfs(1,0));
	// printf("%d\n", bfs(1));
}