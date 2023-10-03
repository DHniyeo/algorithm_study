#include<stdio.h>
#include<string.h>
#include<queue>
using namespace std;
int n, m;
int map[8][8];

int max_safety = 0;

struct INFO {
	int y, x;
};
struct MAPINFO {
	int map[8][8];
	int get_safety() {
		int ret = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (map[i][j] == 0)
					ret++;
			}
		}
		return ret;
	}
	void printmap() {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				printf("%d ", map[i][j]);
			}
			printf("\n");
		}
		printf("\n");
	}
};
int dy[] = { -1, 1, 0 ,0 };
int dx[] = { 0, 0, -1 ,1 };
void bfs() {
	MAPINFO TMP;
	memcpy(TMP.map, map, sizeof(map));
	queue<INFO> q;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (TMP.map[i][j] == 2)
				q.push({ i,j });
		}
	}
	int visited[8][8] = {0};
	while (!q.empty()) {
		INFO now = q.front(); q.pop();

		for (int i = 0; i < 4; i++) {
			int ny = now.y + dy[i];
			int nx = now.x + dx[i];
			if (ny >= n || nx >= m || ny < 0 || nx < 0) continue;
			if (TMP.map[ny][nx] == 1)continue;
			if (visited[ny][nx] == 1) continue;
			visited[ny][nx] = 1;
			TMP.map[ny][nx] = 2;
			q.push({ ny,nx });
		}
	}
	int safety_num = TMP.get_safety();
	max_safety = max_safety < safety_num ? safety_num : max_safety;

	return;
}
void pick_wall_dfs(int sy, int sx, int cnt) {
	if (cnt == 3) {
		bfs();
		return;
	}
	// 현재위치 그 이후의 지점 부터 탐색해서 0이면 벽 세우기
	for (int y = sy; y < n; y++) {
		for (int x = sx; x < m; x++) {
			if (map[y][x] == 0) {
				map[y][x] = 1;
				pick_wall_dfs(y, x, cnt + 1);
				map[y][x] = 0;
			}
		}
		// 중요!! 처음부터 다시 돌려야 하기 때문
		sx = 0;
	}
}
// 맵 색칠용


int main() {
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf(" %d", &map[i][j]);
		}
	}
	// 벽을 고르는 데 필요
	pick_wall_dfs(0, 0, 0);
	printf("%d", max_safety);

}