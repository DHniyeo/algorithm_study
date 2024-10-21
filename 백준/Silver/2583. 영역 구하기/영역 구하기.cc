#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
int M, N, K;
int field[101][101];
int visited[101][101];
vector<int> vc;
void init() {
	cin >> M >> N >> K;
	for (int i = 0; i < K; i++) {
		int sy, sx;
		cin >> sx >> sy;
		int ey, ex;
		cin >> ex >> ey;

		for (int y = sy; y < ey; y++) {
			for (int x = sx; x < ex; x++) {
				field[y][x] = 1;
			}
		}
	}
}
int bfs(int y, int x) {
	const int dy[] = { -1,0,1,0 };
	const int dx[] = { 0,-1,0,1 };
	int cnt = 1;
	queue<pair<int, int>> q;
	q.push({ y,x });
	while (!q.empty()) {
		pair<int, int> now = q.front(); q.pop();
		for (int i = 0; i < 4; i++) {
			int ny = now.first + dy[i];
			int nx = now.second + dx[i];
			if (ny < 0 || nx < 0 || ny >= M || nx >= N) continue;
			if (field[ny][nx] == 1) continue;
			if (visited[ny][nx])continue;
			visited[ny][nx] = 1;
			cnt++;
			q.push({ ny,nx });
		}
	}
	return cnt;
}
int main() {
	init();
	int total_cnt = 0;
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			if (field[i][j] == 1) continue;
			if (visited[i][j])continue;
			visited[i][j] = 1;
			int sum = bfs(i, j);
			vc.push_back(sum);
			total_cnt++;
		}
	}
	sort(vc.begin(), vc.end());
	cout << total_cnt << "\n";
	for (auto a : vc) {
		cout << a << " ";
	}
}