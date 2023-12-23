#include <stdio.h>
#include <string.h>
#include <queue>
// # 벽, . 지나갈수 있는 공간, J 지훈위치, F 불이난 공간.
using namespace std;

int r, c;
char map[1000][1001];
int visited[1000][1000];
int fire_visited[1000][1000];
const int dy[] = { -1, 1, 0, 0 };
const int dx[] = { 0, 0 , -1, 1};

struct info {
	int Jy, Jx;
	int cnt;
};

int main() {
	scanf("%d %d", &r, &c);
	
	for (int i = 0; i < r; i++) {
		scanf(" %s", map[i]);
	}
	queue<info> q;
	queue<info> next_q;
	info start;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (map[i][j] == 'J') {
				start.Jy = i;
				start.Jx = j;
				visited[i][j] = 1;
			}
		}
	}
	start.cnt = 0;
	q.push(start);

	int flag = 0;
	int result;
	
	while (!q.empty()) {
		if (flag == 1) break;
		// 불의 확산
		queue<pair<int, int>> fire;
		for (int i = 0; i < r; i++) {
			for (int j = 0; j < c; j++) {
				if (fire_visited[i][j] == 1) continue; // queue에 추가했던 불 위치는 이미 번졌기 때문에 체크 필요 x
				if (map[i][j] == 'F') {
					fire.push({ i,j });
					fire_visited[i][j] = 1;
				}
			}
		}
		while (!fire.empty()) {
			pair<int, int> fire_loc;
			fire_loc = fire.front(); fire.pop();
			for (int i = 0; i < 4; i++) {
				int ny = fire_loc.first + dy[i];
				int nx = fire_loc.second + dx[i];
				if (ny >= r || nx >= c || ny < 0 || nx < 0) continue;
				if (map[ny][nx] == '#') continue;
				map[ny][nx] = 'F';
			}
		}
		while (!q.empty()) {
			// 지훈의 이동 가능 위치 queue에 저장
			info tmp = q.front(); q.pop();
			// 지훈의 위치가 가장자리?? 탈출
			if (tmp.Jy == r - 1 || tmp.Jx == c - 1 || tmp.Jy == 0 || tmp.Jx == 0) {
				flag = 1;
				result = tmp.cnt + 1;
				break;
			}

			for (int i = 0; i < 4; i++) {
				int ny = tmp.Jy + dy[i];
				int nx = tmp.Jx + dx[i];
				if (ny >= r || nx >= c || ny < 0 || nx < 0) continue;
				if (map[ny][nx] == '#') continue;
				if (map[ny][nx] == 'F')continue;
				if (visited[ny][nx] == 1) continue;
				visited[ny][nx] = 1;
				info next = tmp;
				next.cnt++;
				next.Jy = ny;
				next.Jx = nx;
				next_q.push(next);
			}
		}

		q = next_q;
		next_q = queue<info>();
	}
	
	if (flag == 0) printf("IMPOSSIBLE\n");
	else {
		printf("%d\n", result);
	}
}