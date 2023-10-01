/* 
DP문제
BFS 문제


스타트링크에서 판매하는 어린이용 장난감 중에서 가장 인기가 많은 제품은 구슬 탈출이다. 구슬 탈출은 직사각형 보드에 빨간 구슬과 파란 구슬을 하나씩 넣은 다음, 빨간 구슬을 구멍을 통해 빼내는 게임이다.
보드의 세로 크기는 N, 가로 크기는 M이고, 편의상 1×1크기의 칸으로 나누어져 있다. 가장 바깥 행과 열은 모두 막혀져 있고, 보드에는 구멍이 하나 있다. 빨간 구슬과 파란 구슬의 크기는 보드에서 1×1크기의 칸을 가득 채우는 사이즈이고, 각각 하나씩 들어가 있다. 게임의 목표는 빨간 구슬을 구멍을 통해서 빼내는 것이다. 이때, 파란 구슬이 구멍에 들어가면 안 된다.
이때, 구슬을 손으로 건드릴 수는 없고, 중력을 이용해서 이리 저리 굴려야 한다. 왼쪽으로 기울이기, 오른쪽으로 기울이기, 위쪽으로 기울이기, 아래쪽으로 기울이기와 같은 네 가지 동작이 가능하다.
각각의 동작에서 공은 동시에 움직인다. 빨간 구슬이 구멍에 빠지면 성공이지만, 파란 구슬이 구멍에 빠지면 실패이다. 빨간 구슬과 파란 구슬이 동시에 구멍에 빠져도 실패이다. 빨간 구슬과 파란 구슬은 동시에 같은 칸에 있을 수 없다. 또, 빨간 구슬과 파란 구슬의 크기는 한 칸을 모두 차지한다. 기울이는 동작을 그만하는 것은 더 이상 구슬이 움직이지 않을 때 까지이다.
보드의 상태가 주어졌을 때, 최소 몇 번 만에 빨간 구슬을 구멍을 통해 빼낼 수 있는지 구하는 프로그램을 작성하시오.

*/


#include <stdio.h>
#include <queue>
#include <algorithm>
using namespace std;

struct INFO {
	int ry, rx, by, bx, count;
};

INFO start;
char map[10][11];

int bfs() {
	const int dy[] = { -1, 1, 0, 0 };
	const int dx[] = { 0, 0, -1, 1 };

	int visited[10][10][10][10] = { 0, };
	queue<INFO> q;
	q.push(start);
	visited[start.ry][start.rx][start.by][start.bx] = 1;

	int ret = -1;
	while (!q.empty()) {
		INFO cur = q.front();   q.pop();
		if (cur.count > 10)  break;
		if (map[cur.ry][cur.rx] == 'O' && map[cur.by][cur.bx] != 'O') {
			ret = cur.count;
			break;
		}

		for (int dir = 0; dir < 4; ++dir) {
			int next_ry = cur.ry;
			int next_rx = cur.rx;
			int next_by = cur.by;
			int next_bx = cur.bx;

			while (1) {
				if (map[next_ry][next_rx] != '#' && map[next_ry][next_rx] != 'O') {
					next_ry += dy[dir], next_rx += dx[dir];
				}
				else {
					if (map[next_ry][next_rx] == '#') {
						next_ry -= dy[dir], next_rx -= dx[dir];
					}
					break;
				}
			}

			while (1) {
				if (map[next_by][next_bx] != '#' && map[next_by][next_bx] != 'O') {
					next_by += dy[dir], next_bx += dx[dir];
				}
				else {
					if (map[next_by][next_bx] == '#') {
						next_by -= dy[dir], next_bx -= dx[dir];
					}
					break;
				}
			}

			if (next_ry == next_by && next_rx == next_bx) {
				if (map[next_ry][next_rx] != 'O') {
					int red_dist = abs(next_ry - cur.ry) + abs(next_rx - cur.rx);
					int blue_dist = abs(next_by - cur.by) + abs(next_bx - cur.bx);
					if (red_dist > blue_dist) {
						next_ry -= dy[dir], next_rx -= dx[dir];
					}
					else {
						next_by -= dy[dir], next_bx -= dx[dir];
					}
				}
			}

			if (visited[next_ry][next_rx][next_by][next_bx] == 0) {
				visited[next_ry][next_rx][next_by][next_bx] = 1;
				INFO next;
				next.ry = next_ry;
				next.rx = next_rx;
				next.by = next_by;
				next.bx = next_bx;
				next.count = cur.count + 1;
				q.push(next);
			}
		}
	}
	return ret;
}

int main()
{
	int n, m;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; ++i) {
		scanf("%s", map[i]);
	}

	for (int y = 0; y < n; ++y) {
		for (int x = 0; x < m; ++x) {
			if (map[y][x] == 'R') {
				start.ry = y, start.rx = x;
			}
			if (map[y][x] == 'B') {
				start.by = y, start.bx = x;
			}
		}
	}
	start.count = 0;

	int ret = bfs();
	printf("%d\n", ret);

	return 0;
}