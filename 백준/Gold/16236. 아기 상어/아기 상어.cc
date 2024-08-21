#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>

using namespace std;

int n;
int map[21][21];
struct Shark {
	int y, x, size;
	int eat; //  지금까지 먹은 물고기 개수
};
struct Fish {
	int y, x, lev;
};
Shark shark;
int dy[4] = { -1,0,0,1 };
int dx[4] = { 0,-1,1,0 };

struct Compare {
	bool operator() ( Fish f, Fish tar ) {
		if (tar.lev < f.lev) return true;
		else if (tar.lev > f.lev) return false;

		if (tar.y < f.y) return true;
		else if (tar.y > f.y) return false;

		return tar.x < f.x;
	}
};

Fish bfs() {
	Fish f = { -1,-1,-1 };
	priority_queue<Fish, vector<Fish>, Compare> q;
	int visited[21][21] = { 0, };

	q.push({ shark.y, shark.x });
	visited[shark.y][shark.x] = 1;
	while (!q.empty()) {
		Fish now = q.top();
		q.pop();

		if (1 <= map[now.y][now.x] && map[now.y][now.x] < shark.size) return now;

		for (int i = 0; i < 4; i++) {
			int ny = now.y + dy[i];
			int nx = now.x + dx[i];
			if (ny < 0 || ny >= n || nx < 0 || nx >= n) continue;
			if (visited[ny][nx] || map[ny][nx] > shark.size) continue;

			q.push({ ny,nx,now.lev + 1 });
			visited[ny][nx] = 1;
		}
	}
	return f;
}

int solve() {
	int t = 0;
	while (1) {
		// 1. bfs 
		Fish ret = bfs();
		if (ret.y == -1) return t;

		// 2. 물고기 먹기
		map[ret.y][ret.x] = 0;
		shark.y = ret.y, shark.x = ret.x;
		if (++shark.eat == shark.size) {
			shark.size++;
			shark.eat = 0;
		}
		t += ret.lev;
	}
	return t;
}

int main() {
	//freopen("input.txt", "r", stdin);

	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
			if (map[i][j] == 9) { 
				map[i][j] = 0;
				shark = { i,j,2,0 }; 
			}
		}
	}

	int ans = solve();
	printf("%d\n", ans);

	return 0;
}