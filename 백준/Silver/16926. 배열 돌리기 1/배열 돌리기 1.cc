#include <iostream>
#include <cstring>
#define min(x,y) x < y ? x : y
using namespace std;
int dy[] = { 0,1,0,-1 }; // 우 하 좌 상
int dx[] = { 1,0 ,-1, 0 };
int n, m, k;
int map[300][300];
void printmap() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << map[i][j] << " ";
		}
		cout << endl;
	}

}
void init() {
	cin >> n >> m >> k;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
		}
	}
}
struct loc {
	int y, x;
};
void rotate(int idx) {
	int chogiy = idx;
	int chogix = idx;
	int dir = 2;
	loc now = { idx,idx };
	int tmp = map[idx][idx];
	while (1) {
		int ny = now.y + dy[dir];
		int nx = now.x + dx[dir];
		if (ny == chogiy && nx == chogix) {
			map[now.y][now.x] = tmp;
			break;
		}
		if (ny >= n - idx || nx >= m - idx || ny < idx || nx < idx) {
			dir = (dir + 1) % 4;
			continue;
		}
		else {
			map[now.y][now.x] = map[ny][nx];
		}
		now = { ny,nx };
	}
}
int main() {
	// 여기에 코드를 작성해주세요.
	init();
	int minV = min(n, m);
	for (int i = 0; i < minV / 2; i++) {
		int size = 2 * (n - i * 2) + 2 * (m - i * 2) - 4;
		int nowsize = k % size;
		for (int j = 0; j < nowsize; j++) {
			rotate(i);
		}
	}
	printmap();

	return 0;
}