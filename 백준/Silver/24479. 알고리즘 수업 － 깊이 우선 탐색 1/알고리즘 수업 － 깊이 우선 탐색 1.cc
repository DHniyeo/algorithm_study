#include <stdio.h>
#include <queue>
using namespace std;

int N, M, R;
priority_queue<int, vector<int>,greater<int>> map[100001];
int visited[100001];
int order[100001];
int cnt = 1;
void dfs(int node) {
	visited[node] = 1;
	order[node] = cnt;

	while (!map[node].empty()) {
		int next_node = map[node].top(); map[node].pop();
		if (visited[next_node] == 1) continue;
		cnt++;
		dfs(next_node);
	}

}
int main() {
	scanf("%d %d %d", &N, &M, &R);
	for (int i = 0; i < M; i++) {
		int u, v;
		scanf(" %d %d", &u, &v);
		map[u].push(v);
		map[v].push(u);
	}
	dfs(R);
	for (int i = 1; i <= N; i++) {
		printf("%d\n", order[i]);
	}
}