//-턴이 진행되던 도중 말이 4개이상 쌓이는 순간 게임이 종료됨.
//- 1번말부터 K번 말까지 순서대로 이동시킴.한 말이 이동할때 위에 올려져 있는 말도 함께이동.
//- 이동하려는 칸이 흰색인 경우 해당 칸으로 이동.이동하려는 칸에 말이 이미 있는 경우 가장 위에 말을 올려놓음.
//- 이동하려는 칸이 빨간색인경우 이동후에 A번말과 그위에 있는 모든말의 쌓여있는 순서를 반대로 바꾼다.옮기기전의 말들만 순서를 바꿔서 쌓는다.
//- 이동하려는 칸이 파란색인경우 A번 말의 이동 방향을 반대로 하고 한칸 이동한다.방향을 반대로 바꾼후에 이동하려는 칸이 파란색인경우 가만히 있는다.
//- 체스판을 벗어난 경우는 파란색과 같은경우이다.
// 게임이 종료 되는 턴 수를 구하고 1000보다 크면 -1을 출력

#include <iostream>
#include <vector>
#include <deque>
using namespace std;
int color_map[12][12];
int N, K;
int flag = 0;

// 오 왼 위 아래
const int dy[] = { 0 , 0 , -1, 1 };
const int dx[] = { 1 , -1 , 0, 0 };

struct info {
	int y, x, dir;
};
vector<info> vc;
deque<int> dq[12][12];

void init() {
	flag = 0;
	vc.clear();
	cin >> N >> K;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> color_map[i][j];
		}
	}
	for (int i = 0; i < K; i++) {
		int y, x, dir;
		cin >> y >> x >> dir;
		vc.push_back({ y - 1,x - 1,dir - 1 });
		dq[y - 1][x - 1].push_back(i);
	}
}
int check() {
	int max = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int num = dq[i][j].size();
			if (max < num) max = num;
		}
	}
	return max;
}
void whitetile_move(int num) {
	info now = vc[num];
	int ny = now.y + dy[now.dir];
	int nx = now.x + dx[now.dir];
	int size = dq[now.y][now.x].size();

	int now_index = 0;
	for (int i = 0; i < size; i++) {
		if (dq[now.y][now.x][i] == num) { // 현재 체스말 위치 찾기
			now_index = i;
			break;
		}
	}
	for (int i = now_index; i < size; i++) {
		int chessnum = dq[now.y][now.x][i];
		dq[ny][nx].push_back(chessnum); // 순서대로 쌓기
		// 벡터 최신화
		vc[chessnum].y = ny;
		vc[chessnum].x = nx;
	}
	int move_cnt = size - now_index; // 옮겨야 되는 횟수
	while (move_cnt--) { // 기존에 있던 위치에서 삭제
		dq[now.y][now.x].pop_back();
	}
	if (4 <= dq[ny][nx].size()) flag = 1;
}
void redtile_move(int num) {
	info now = vc[num];
	int ny = now.y + dy[now.dir];
	int nx = now.x + dx[now.dir];
	int size = dq[now.y][now.x].size();

	int now_index = 0;
	for (int i = 0; i < size; i++) {
		if (dq[now.y][now.x][i] == num) { // 현재 체스말 위치 찾기
			now_index = i;
			break;
		}
	}
	for (int i = size - 1; i >= now_index; i--) {
		int chessnum = dq[now.y][now.x][i];
		dq[ny][nx].push_back(chessnum); // 순서대로 쌓기
		// 벡터 최신화
		vc[chessnum].y = ny;
		vc[chessnum].x = nx;
	}
	int move_cnt = size - now_index; // 옮겨야 되는 횟수
	while (move_cnt--) { // 기존에 있던 위치에서 삭제
		dq[now.y][now.x].pop_back();
	}
	// 쌓은 후 체크
	if (4 <= dq[ny][nx].size()) flag = 1;
}
void bluetile_move(int num) {
	// 방향 전환하기.
	if (vc[num].dir == 0) vc[num].dir = 1;
	else if (vc[num].dir == 1) vc[num].dir = 0;
	else if (vc[num].dir == 2) vc[num].dir = 3;
	else if (vc[num].dir == 3) vc[num].dir = 2;

	info now = vc[num];
	int ny = now.y + dy[now.dir];
	int nx = now.x + dx[now.dir];

	if (ny >= N || nx >= N || ny < 0 || nx < 0) return;
	else if (color_map[ny][nx] == 2) return;
	else if (color_map[ny][nx] == 1) { // 빨간색 타일
		redtile_move(num);
	}
	else if (color_map[ny][nx] == 0) { // 흰색 타일
		whitetile_move(num);
	}
}

void move_chess(int num) {
	info now = vc[num];
	int ny = now.y + dy[now.dir];
	int nx = now.x + dx[now.dir];

	if (ny >= N || nx >= N || ny < 0 || nx < 0) { // 파란색 타일
		bluetile_move(num);
	}
	else if (color_map[ny][nx] == 2) { // 파란색 타일
		bluetile_move(num);
	}
	else if (color_map[ny][nx] == 1) { // 빨간색 타일
		redtile_move(num);
	}
	else if (color_map[ny][nx] == 0) { // 흰색 타일
		whitetile_move(num);
	}
}

int gamespace() {
	int times = 0;
	while (1) {

		times++;
		for (int i = 0; i < K; i++) {
			if (flag == 1) return times;
			move_chess(i);
		}
		if (flag == 1) return times;

		if (times > 1000) {
			times = -1;
			break;
		}
	}
	return times;
}
int main() {
	init();

	cout << gamespace() << endl;
}