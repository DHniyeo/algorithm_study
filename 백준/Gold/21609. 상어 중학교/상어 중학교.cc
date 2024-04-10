//1. 크기가 가장 큰 블록 그룹을 찾는다.무지개 블록의 수가 가장 많은 블록, 기준 블록의 행이 가장 큰것, 열이 가장큰것
//2. 블록 모두 제거 B제곱 점수를 얻음.
//3. 격자에 중력 작용(-1 블록 빼고 다내림)
//4. 격자 90도 반시계 방향으로 회전.
//4. 격자에 중력작용(-1 블록 빼고 다내림)
#include <iostream>
#include <cstring>
#include <queue>
#include <math.h>
#include<algorithm>
#include <vector>

using namespace std;

int N, M;
int color_MAP[20][20]; // -1 : 검은 블록 0: 무지개 블록 // -2 : 빈공간
int score = 0;
int dy[] = { -1,1,0,0 };
int dx[] = { 0,0,-1,1 };

void init() {
	cin >> N >> M;
	score = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> color_MAP[i][j];
		}
	}
}
struct loc {
	int y, x;
};
struct info {
	int cnt, rainbowcnt;
};
struct vector_info {
	int y, x, rainbowcnt;
};
bool cmp(vector_info first, vector_info second) {
	if (first.rainbowcnt > second.rainbowcnt) {
		return true;
	}
	else if (first.rainbowcnt == second.rainbowcnt) {
		if (first.y > second.y) {
			return true;
		}
		else if (first.y == second.y) {
			return first.x > second.x;
		}
	}
	return false;
}

int color_visited[20][20] = { 0 };
info bfs(int y, int x, int color) {
	int visited[20][20] = { 0 };
	info result = { 1,0};
	queue<loc> q;
	q.push({ y,x });
	visited[y][x] = 1;
	while (!q.empty()) {
		loc now = q.front(); q.pop();

		for (int i = 0; i < 4; i++) {
			int ny = now.y + dy[i];
			int nx = now.x + dx[i];
			if (ny >= N || nx >= N || ny < 0 || nx < 0) continue;
			if (color_MAP[ny][nx] == -1 || color_MAP[ny][nx] == -2) continue;
			if (color_MAP[ny][nx] == color || color_MAP[ny][nx] == 0) { // 무지개 블럭이나 기준 블럭과 같은색상일경우에만
				if (visited[ny][nx] == 1) continue;
				color_visited[ny][nx] = 1;
				visited[ny][nx] = 1;
				result.cnt++;
				if (color_MAP[ny][nx] == 0) result.rainbowcnt++;
				q.push({ ny,nx });
			}
		}
	}
	return result;
}
void deleteBlock(int y, int x, int color) { // 기준 블럭의 위치에서 다시한번 돌면서 맵최신화
	// 방문한 곳은 이미 -2일테니깐 visited 배열이 필요가 없음.
	queue<loc> q;
	q.push({ y,x });
	color_MAP[y][x] = -2; // 빈공간으로 만들어버림.

	while (!q.empty()) {
		loc now = q.front(); q.pop();

		for (int i = 0; i < 4; i++) {
			int ny = now.y + dy[i];
			int nx = now.x + dx[i];
			if (ny >= N || nx >= N || ny < 0 || nx < 0) continue;
			if (color_MAP[ny][nx] == -1 || color_MAP[ny][nx] == -2) continue;
			if (color_MAP[ny][nx] == color || color_MAP[ny][nx] == 0) { // 무지개 블럭이나 기준 블럭과 같은색상일경우에만
				color_MAP[ny][nx] = -2; // 빈공간으로 만들어버림.
				q.push({ ny,nx });
			}
		}

	}
}
bool findBig() {
	memset(color_visited, 0, sizeof(color_visited));
	//1. 크기가 가장 큰 블록 그룹을 찾는다.무지개 블록의 수가 가장 많은 블록, 기준 블록의 행이 가장 큰것, 열이 가장큰것
	int flag = false;
	int maxcnt = 0; // 블록 그룹은 cnt가 두개 이상이어야함.
	int rainbowcnt = 0;
	vector<vector_info> vc;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (color_MAP[i][j] > 0) { // 일반 블록에서 들어가야함.
				if (color_visited[i][j] == 1) continue; // 이미 방문한 색깔블록은 제외
				info now = bfs(i, j, color_MAP[i][j]);
				if (maxcnt < now.cnt && now.cnt > 1) {
					vc.clear();
					maxcnt = now.cnt;
					flag = true;
					vc.push_back({ i,j,now.rainbowcnt });
				}
				else if(maxcnt == now.cnt && now.cnt > 1){ 
					vc.push_back({ i,j,now.rainbowcnt });
				}
			}
		}
	}
	if (!flag) return flag;
	sort(vc.begin(), vc.end(), cmp);
	
	//2. 블록 모두 제거 B제곱 점수를 얻음.
	loc centerBlock = { vc[0].y, vc[0].x };
	deleteBlock(centerBlock.y, centerBlock.x, color_MAP[centerBlock.y][centerBlock.x]);
	score = score + maxcnt * maxcnt;
	return flag;
}
void Gravity() {
	for (int i = N - 1; i >= 0; i--) { // 맨 밑에서부터 내림
		for (int j = 0; j < N; j++) {
			if (color_MAP[i][j] == -1 || color_MAP[i][j] == -2) continue; // 검은 블록과 빈공간은 움직이지 않음.
			int nowy = i;
			while (1) {
				int ny = nowy + 1;
				if (ny >= N)break; // 범위 안에서만 이동
				if (color_MAP[ny][j] != -2) break; // 빈공간으로만 이동
				color_MAP[ny][j] = color_MAP[nowy][j]; // 이동
				color_MAP[nowy][j] = -2; // 현재칸 비우기
				nowy = ny; // 좌표 이동
			}
		}
	}
}

void RotateMAP() {
	int tmp[20][20] = { 0 };
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			tmp[i][j] = color_MAP[j][N - 1 - i];
		}
	}
	memcpy(color_MAP, tmp, sizeof(color_MAP));
}
void printMAP() {

	cout << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << color_MAP[i][j] << " ";
		}
		cout << endl;
	}

}
int main() {
	init();
	while (1) {
		//1. 크기가 가장 큰 블록 그룹을 찾는다.무지개 블록의 수가 가장 많은 블록, 기준 블록의 행이 가장 큰것, 열이 가장큰것
		//2. 블록 모두 제거 B제곱 점수를 얻음.
		if (!findBig()) break;
		//printMAP();
		//cout << "nowscore : "<< score << endl;
		//3. 격자에 중력 작용(-1 블록 빼고 다내림)
		Gravity();
		//printMAP();
		//4. 격자 90도 반시계 방향으로 회전.
		RotateMAP();
		//printMAP();
		//5. 격자에 중력작용(-1 블록 빼고 다내림)
		Gravity();
		//printMAP();
	}

	cout << score << endl;
}