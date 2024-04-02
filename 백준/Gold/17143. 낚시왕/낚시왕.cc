#include <iostream>
#include <queue>
using namespace std;
int R, C, M;
long long int score;
struct info {
	int r, c, s, d, z;
};

struct cmp {
	bool operator()(info second, info first) {
		if (first.c < second.c) {
			return true;
		}
		else if (first.c == second.c) {
			if (first.r < second.r) {
				return true;
			}
			else if (first.r == second.r) {
				if (first.z > second.z) {
					return true;
				}
			}
		}
		return false;
	};
};
priority_queue<info, vector<info>, cmp> sharks; // c가 작고 r이작고 크기가 큰 순서대로

void init() {
	cin >> R >> C >> M;
	for (int i = 0; i < M; i++) {
		int r, c, s, d, z;
		cin >> r >> c >> s >> d >> z;
		sharks.push({ r - 1, c - 1, s, d - 1, z });
	}
	score = 0;
}

void cpyqueue(priority_queue<info, vector<info>, cmp> &q1, queue<info> &q2) {
	while (!q2.empty()) {
		info tmp = q2.front();
		q2.pop();
		q1.push(tmp);
	}
}
void getshark(int x) { // 상어 끌어 올리기
	queue<info> eq;
	int flag = 0;
	while (!sharks.empty()) {
		info shark = sharks.top();
		sharks.pop();
		if (flag == 0 && shark.c == x) { // 한번에 한해서
			score += shark.z;
			flag = 1;
		}
		else {
			eq.push(shark);
		}
	}
	cpyqueue(sharks, eq);
}
void move_shark() {
	priority_queue<info, vector<info>, cmp> eq; // c가 작고 r이작고 크기가 큰 순서대로
	const int dy[] = { -1,1,0,0 }; // 위 아래 오른 왼
	const int dx[] = { 0,0,1,-1 };

	int visited[100][100] = {}; // 방문 했으면 패스
	while (!sharks.empty()) {
		info shark = sharks.top();
		sharks.pop();

		int Rotate;
		if (shark.d == 0 || shark.d == 1) { // 위 아래 움직일 시.
			Rotate = shark.s % ((R - 1) * 2);
		}
		else { // 오른 왼 움직일 시.
			Rotate = shark.s % ((C - 1) * 2);
		}
		while (Rotate--) {
			int ny = shark.r + dy[shark.d];
			int nx = shark.c + dx[shark.d];
			if (ny >= R || nx >= C || ny < 0 || nx < 0) { // 범위 초과시 방향전환
				if (shark.d == 0) shark.d = 1;
				else if (shark.d == 1) shark.d = 0;
				else if (shark.d == 2) shark.d = 3;
				else if (shark.d == 3) shark.d = 2;

				ny = shark.r + dy[shark.d];
				nx = shark.c + dx[shark.d];
			}
			shark.r = ny;
			shark.c = nx;
		}
		eq.push(shark); // 옮겨 담음
	}

	while (!eq.empty()) {
		info shark = eq.top();
		eq.pop();
		if (visited[shark.r][shark.c] == 1) continue; // 큰 상어가 이미 방문했으므로
		visited[shark.r][shark.c] = 1;
		sharks.push(shark);
	}
}

int main() {

	init();
	for (int i = 0; i < C; i++) {
		getshark(i);
		move_shark();
	}
	cout << score;
}