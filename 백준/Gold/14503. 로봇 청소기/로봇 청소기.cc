#include<stdio.h>
#include<queue>
using namespace std;

// 북, 동, 남, 서
int dy[] = { -1, 0, 1, 0 };
int dx[] = { 0, 1, 0 ,-1 };
int n, m;
struct Robot {
	int y, x, dir;
};
// 0 청소되지 않은 빈칸, 1인 경우 벽 // 청소된칸 2로 지정.
int map[50][50];

// 디버깅용
void printmap() {
	printf("\n");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			printf("%d ", map[i][j]);
		printf("\n");
	}
}

queue<Robot> q;
int main()
{
	Robot first;
	scanf("%d %d", &n, &m);
	scanf(" %d %d %d",&first.y, &first.x, &first.dir);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf(" %d", &map[i][j]);
		}
	}

	q.push(first);
	int cnt = 0;
	while (!q.empty())
	{
		Robot now = q.front(); q.pop();
		if (map[now.y][now.x] == 0) {
			cnt++;
			map[now.y][now.x] = 2;
		}
		int flag = 0;
		// 청소되지 않은 칸 있는지 없는지 여부 찾기
		for (int i = 0; i < 4; i++) {
			int ny = now.y + dy[i];
			int nx = now.x + dx[i];
			// 후진했을때 벽이면 작동 멈춤(벽인지만 체크하면됨. 범위 초과는 문제에서 방지됨)
			//if (ny >= n || nx >= m || ny < 0 || nx < 0) continue;
			if (map[ny][nx] == 0) {
				flag = 1;
				break;
			}
		}
		// 청소되지 않은 칸 없음 
		if (flag == 0) {
			// 바라보는 칸 유지한채로 후진
			int ny = now.y - dy[now.dir];
			int nx = now.x - dx[now.dir];
			// 후진했을때 벽이면 작동 멈춤(벽인지만 체크하면됨. 범위 초과는 문제에서 방지됨)
			//if (ny >= n || nx >= m || ny < 0 || nx < 0) break;
			if(map[ny][nx] == 1) break;
			q.push({ ny,nx, now.dir });
		}
		// 청소되지 않은 칸 있음
		else {
			// 시계 반대방향으로 회전
			int ndir = (now.dir + 3) % 4;
			// 만약 앞쪽 칸이 청소 되지 않았다면 한칸 전진
			int ny = now.y + dy[ndir];
			int nx = now.x + dx[ndir];

			// 앞쪽 칸이 청소 되지 않았으면 위치 옮기기
			if (map[ny][nx] == 0) {
				q.push({ ny,nx,ndir });
			}
			else {
				q.push({ now.y,now.x,ndir });
			}
		}
	}
	printf("%d", cnt);

}