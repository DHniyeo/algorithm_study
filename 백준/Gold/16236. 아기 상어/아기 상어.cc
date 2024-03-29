#include<iostream>
#include<math.h>
#include<cstring>
#include<queue>
using namespace std;
int N;
int Map[20][20];
struct info {
	int y, x;
};
info baby_shark, target;
int min_dist = 1e9;
int shark_size = 2;
int get_fish = 0;

void init() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> Map[i][j];
			if (Map[i][j] == 9) {
				baby_shark.y = i;
				baby_shark.x = j;
			}
		}
	}
}
int find_dist(int y, int x) { // 상어와 물고기의 최단 거리 구하기.
	// 상어가 큰 물고기를 피해서 이동하는 최단 거리를 구해야 한다.
	const int dy[] = { 1, 0, -1, 0 };
	const int dx[] = { 0,-1, 0, 1 };
	queue<info> q;
	int visited[20][20];
	memset(visited, 0, sizeof(visited));

	q.push({ baby_shark.y, baby_shark.x });
	visited[baby_shark.y][baby_shark.x] = 1;
	while (!q.empty()) {
		info now = q.front(); q.pop();
		if (now.y == y && now.x == x) { // 해당 물고기 위치에 도달
			return visited[now.y][now.x] - 1;
		}
		for (int i = 0; i < 4; i++) {
			int ny = now.y + dy[i];
			int nx = now.x + dx[i];
			if (ny >= N || nx >= N || ny < 0 || nx < 0) continue;
			if (visited[ny][nx] != 0) continue;
			if (Map[ny][nx] > shark_size) continue; // 큰 물고기 피해가기
			visited[ny][nx] = visited[now.y][now.x] + 1;
			q.push({ ny,nx });
		}
	}
	return 1e9; // 도달 하지 못했으므로 매우 큰값 반환
}

bool findFish() {
	bool flag = false;
	min_dist = 1e9;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (Map[i][j] < shark_size && Map[i][j] > 0 && Map[i][j] != 9) { // 물고기 크기가 작고 거리가 최소일때
				// 최단 거리 구하기.
				int dist = find_dist(i, j);
				if (min_dist > dist) {
					flag = true;
					min_dist = dist;
					target.y = i;
					target.x = j;
				}
			}
		}
	}
	return flag;
}
void eat_fish() {
	Map[baby_shark.y][baby_shark.x] = 0; // 현재 위치 비움
	Map[target.y][target.x] = 9; // 물고기 위치가 상어 위치가됨.
	baby_shark.y = target.y;
	baby_shark.x = target.x;
	get_fish++; // 먹은 물고기 수 증가
	if (get_fish == shark_size) { // 상어가 먹은 물고기가 조건에 부합할 시 크기 성장.
		shark_size++;
		get_fish = 0;
	}
}
void printmap() { // 디버깅용
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << Map[i][j] << " ";
		}
		cout << endl;
	}
}

int main() {
	init();
	int cnt = 0;
	while (1) {
		if (!findFish()) { // 물고기 찾기
			break;
		}
		eat_fish();
		cnt += min_dist;
	}
	cout << cnt;
}