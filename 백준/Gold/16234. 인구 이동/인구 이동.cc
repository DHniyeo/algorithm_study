/*
하나 씩 들어가서, 좌우 위아래 비교해보고 조건 만족하면 임시 visited 에 추가,
합계 누적. 더이상 비교 할것 없으면 새로운맵에 평균값 저장. 전부 처리한 후에
새로운 맵 적용. 변한게 없으면 종료. 20라운드 이상 - 종료
*/
#include <stdio.h>
#include <string.h>
#include <math.h>

int map[50][50];
int tmp_map[50][50];
int visited[50][50];     // 방문했는지 아닌지.
int tmp_visited[50][50]; // 한 구역에 대해서만 체크
int n, l, r;

const int dy[4] = { -1, 1, 0, 0 };
const int dx[4] = { 0, 0, -1, 1 };
int sum = 0;
int cnt = 0;
void dfs(int y, int x) {

	for (int i = 0; i < 4; i++) {
		int ny = y + dy[i];
		int nx = x + dx[i];
		if (ny >= n || nx >= n || ny < 0 || nx < 0) continue;
		if (visited[ny][nx] == 1) continue;
		if (tmp_visited[ny][nx] == 1) continue;
		int gap = abs(map[ny][nx] - map[y][x]);
		if (gap >= l && gap <= r) {
			visited[ny][nx] = 1; // 방문 여부 체크
			tmp_visited[ny][nx] = 1; // 한 덩어리에 대한 방문 여부 체크
			sum += map[ny][nx];
			cnt++;
			dfs(ny, nx);
		}
	}
}
void tmp_map_make(int num) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (tmp_visited[i][j] == 1) {
				tmp_map[i][j] = num;
			}
		}
	}
}

int mapchange() {
	int flag = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (visited[i][j] == 0) {
				memset(tmp_visited, 0, sizeof(tmp_visited));
				visited[i][j] = 1;
				tmp_visited[i][j] = 1;
				sum = map[i][j];
				cnt = 1;
				dfs(i,j); // tmp_visited 생성
				if (cnt >= 2) {
					sum = sum / cnt;
					flag = 1;
					// tmp_map 생성
					tmp_map_make(sum);
				}
				else {
					tmp_map[i][j] = sum;
				}
			}
		}
	}
	

	if (flag == 0) return 0;
	memcpy(map, tmp_map, sizeof(map));
	memset(visited, 0, sizeof(visited));
	memset(tmp_map, 0, sizeof(tmp_map));
	return 1;
}

int main() {

	scanf("%d %d %d", &n, &l, &r);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf(" %d", &map[i][j]);
		}
	}
	int day = 0;
	while (1) {
		if (day >= 2000)
			break;
		int flag = mapchange();
		if (flag == 0) break;

		day++;
	}
	printf("%d\n", day);
}