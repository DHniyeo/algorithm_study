#include <stdio.h>
#include <queue>
#include <stack>
#include <algorithm>
#include <string.h>

using namespace std;
struct info {
	int start;
	int end;
};

vector <int> map[1001];

int visited[1001] = { 0 };
void dfs(int node) {
	

	visited[node] = 1;
	printf("%d ", node);
	int size = map[node].size();
	for (int i = 0; i < size; i++) {
		if (visited[map[node][i]] == 1)continue;
		dfs(map[node][i]);
	}
	return;
}
void bfs(int node) {
	visited[node] = 1;
	queue<int> q;
	q.push(node);

	while (!q.empty()) {
		int next = q.front(); q.pop();
		printf("%d ", next);
		int size = map[next].size();
		for (int i = 0; i < size; i++) {
			if (visited[map[next][i]] == 1) continue;
			visited[map[next][i]] = 1;
			q.push(map[next][i]);
		}
	}


}
int main()
{
	int n, m, v;

	scanf("%d %d %d", &n, &m, &v);
	getchar();
	for (int i = 0; i < m; i++) {
		info tmp;
		scanf("%d %d", &tmp.start, &tmp.end);
		getchar();
		map[tmp.start].push_back(tmp.end);
		map[tmp.end].push_back(tmp.start);
	}
	for (int i = 1; i <= n; i++) {
		// 오름차순 정렬
		sort(map[i].begin(), map[i].end(), less<int>());
	}
	dfs(v);
	printf("\n");
	memset(visited, 0, sizeof(visited));
	bfs(v);
	printf("\n");
}