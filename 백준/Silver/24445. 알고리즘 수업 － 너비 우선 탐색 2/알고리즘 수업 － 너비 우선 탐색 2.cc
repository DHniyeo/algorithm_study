#include<stdio.h>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
int N, M, R;
vector<int> nodes[100001];
int visited[100001];
int order[100001];

void bfs(queue<int> &IQ) {
	int cnt = 1;
	order[R] = 1;
	while (!IQ.empty()) {
		int now_node = IQ.front(); IQ.pop();
		
		visited[now_node] = 1;

		for (int i = 0; i < nodes[now_node].size(); i++) {
			int next_node = nodes[now_node][i];
			if (visited[next_node] == 1) continue;
			visited[next_node] = 1;
			cnt++;
			order[next_node] = cnt;
			IQ.push(next_node);
		}
	}
}
int main() {
	scanf("%d %d %d", &N, &M, &R);
	for (int i = 0; i < M; i++) {
		int u, v;
		scanf(" %d %d", &u, &v);
		nodes[u].push_back(v);
		nodes[v].push_back(u);
	}
	for (int i = 1; i <= N; i++) {
		sort(nodes[i].begin(), nodes[i].end(), greater<int>());
	}
	queue<int> q;
	q.push(R);
	bfs(q);
	for (int i = 1; i <= N; i++) {
		printf("%d\n", order[i]);
	}
}