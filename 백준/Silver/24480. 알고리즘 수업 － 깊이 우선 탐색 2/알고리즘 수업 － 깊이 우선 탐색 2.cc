#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

int N, M, R;
vector<int> vc[100001];
int visited[100001];
int order[100001];
int cnt = 1;

void dfs(int node) {
	visited[node] = 1;
	order[node] = cnt;

	for (int i = 0; i < vc[node].size(); i++) {
		int next_node = vc[node][i];
		if (visited[next_node] == 1) continue;
		cnt++;
		dfs(next_node);
	}
}

int main() {
	scanf("%d %d %d", &N, &M, &R);
	for (int i = 0; i < M; i++) {
		int u, c;
		scanf(" %d %d", &u, &c);
		vc[u].push_back(c);
		vc[c].push_back(u);
	}
	// 정렬거치기
	for (int i = 1; i <= N; i++) {
		sort(vc[i].begin(), vc[i].end(), greater<int>());
	}
	dfs(R);
	
	for (int i = 1; i <= N; i++) {
		printf("%d\n", order[i]);
	}
}