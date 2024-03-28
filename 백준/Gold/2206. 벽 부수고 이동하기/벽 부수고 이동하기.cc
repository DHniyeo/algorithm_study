#include<stdio.h>
#include<queue>
#include<string.h>
using namespace std;

int n, m;
char map[1000][1001];
int visited[1000][1001][2] = { 0 };

struct info {
	int y, x, dist;
	bool isbroken;
};
int bfs() {
	queue<info> q;

	int dy[] = { -1,0,1,0 };
	int dx[] = { 0,-1,0,1 };
	memset(visited, 0, sizeof(visited));
	// visited [][][0] : 벽 아직 부순적없음
	// visited [][][1] : 벽 부순 상태에서 이동하는 경우
	// visited를 통합하게 되면 벽을 부수지 않은 상태에서 갈 수있는 위치를 벽을 부숴서 정작 필요한 경우에 못 부시는 케이스가 큐에 담김. 부순 후 이동한 케이스를 분리함.
	q.push({ 0, 0, 1, 0});
	visited[0][0][0] = 1;

	while (!q.empty()) {
		info now = q.front(); q.pop();
		if (now.y == n - 1 && now.x == m - 1) {
			return now.dist;
		}
		for (int i = 0; i < 4; i++) {
			int ny = now.y + dy[i];
			int nx = now.x + dx[i];
			if (ny >= n || nx >= m || ny < 0 || nx < 0) continue;

			if (map[ny][nx] == '1') { // 벽을 만난 경우
				if (now.isbroken == true) continue;
				if (visited[ny][nx][0] == 1) continue;
				visited[ny][nx][0] = 1;
				q.push({ ny,nx, now.dist + 1, true });
			}
			else if (map[ny][nx] == '0') { // 벽이 아닌경우
				if (now.isbroken == false && visited[ny][nx][0] != 1) { // 벽을 부순적 없고 방문한 적도 없다면
					visited[ny][nx][0] = 1;
					q.push({ ny,nx, now.dist + 1, false });
				}
				else if(now.isbroken == true && visited[ny][nx][1] != 1) { // 벽을 부순상태에서 방문한 적이 없다면
					visited[ny][nx][1] = 1;
					q.push({ ny,nx, now.dist + 1, true});
				}
			}
		}
	}
	return -1;
}
void init() {
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		scanf("%s", map[i]);
	}
}
int main() {
	init();
	int result = bfs();
	printf("%d", result);
}