#include<stdio.h>
#include<string.h>
#include<vector>
#include<stack>
using namespace std;

int V, E;
vector<int> G[200001]; // 그래프 저장
int Node_Color[20001]; // Node 색상 저장.

void init() {
	memset(G, 0, sizeof(G));
	memset(Node_Color, 0, sizeof(Node_Color));
	scanf(" %d %d", &V, &E);
	for (int i = 0; i < E; i++) {
		int u, v;
		scanf(" %d %d", &u, &v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
}
bool dfs() {
	stack<int> q;
	for (int i = 1; i <= V; i++) {
		q.push(i);
	}
	while (!q.empty()) {
		int now = q.top(); q.pop();
		int next_color = Node_Color[now] % 2 + 1;
		for (int i = 0; i < G[now].size(); i++) {
			int Next_node = G[now][i];
			if (Node_Color[Next_node] == 0) { // 방문하지 않은 노드라면?
				Node_Color[Next_node] = next_color;
				q.push(Next_node);
			}
			else if (Node_Color[Next_node] != next_color) { // 방문한 노드인데 next Color와 다르다면
				return false;
			}
		}
	}
	return true;
}
int main() {
	int tc;
	scanf("%d", &tc);
	for (int T = 0; T < tc; T++) {
		init();
		bool result = dfs();
		if (result == true) {
			printf("YES\n");
		}
		else {
			printf("NO\n");
		}
	}
}