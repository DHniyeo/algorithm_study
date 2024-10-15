#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;

int N, M;
vector<int> graph[10001];
vector<int> vc;
void init() {
	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		int end, start;
		cin >> end >> start;
		graph[start].push_back(end);
	}
}
int bfs(int node) { // 한번에 들를수 있는 갯수찾기
	int cnt = 0;
	queue<int> q;
	int visited[10001] = {0};
	q.push(node);
	visited[node] = 1;
	while (!q.empty()) {
		int now = q.front(); q.pop();
		for (int i = 0; i < graph[now].size(); i++) {
			if (visited[graph[now][i]])continue;
			visited[graph[now][i]] = 1;
			q.push(graph[now][i]);
			cnt++;
		}
	}

	return cnt;
}
int main() {
	init();
	int maxV = 0;
	for (int i = 1; i <= N; i++) {
		int result = bfs(i);
		if (maxV < result) { // 초기화
			maxV = result;
			vc.clear();
			vc.push_back(i);
		}
		else if (maxV == result) {
			vc.push_back(i);
		}
	}
	sort(vc.begin(), vc.end(), less<int>());

	for (auto a : vc) {
		cout << a << " ";
	}
}