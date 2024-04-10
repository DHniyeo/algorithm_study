//	입력: N, M
//	N*N 맵
//	M개의 줄에 d와 s 주어짐
//	출력 : 1x폭발한 1번구슬 + 2x폭발한 2번구슬 개수 + 3x 폭발한 3번구슬 개수

#include<iostream>
#include<cstring>
using namespace std;

int N, M;
int ball_map[49][49];
int straight[2500]; // 일자 배열
struct info {
	int d, s;
};
struct loc {
	int y, x;
};
info todo[100];
int ballcnt[4]; // 1,2,3만씀
int dy[] = { -1,1,0,0 };
int dx[] = { 0,0,-1,1 };

int spin_dy[] = { 0,1,0,-1 }; // 왼 아래 오른 위
int spin_dx[] = { -1,0,1,0 };

void init() {
	memset(ballcnt, 0, sizeof(ballcnt));
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> ball_map[i][j];
		}
	}
	for (int i = 0; i < M; i++) {
		int d, s;
		cin >> d >> s;
		d--;
		todo[i] = { d,s };
	}
}
void cnt_ball_in_straight(int idx) {
	if (straight[idx] == 1) {
		ballcnt[1]++;
	}
	else if (straight[idx] == 2) {
		ballcnt[2]++;
	}
	else if (straight[idx] == 3) {
		ballcnt[3]++;
	}
}
void blizard(int d, int s) {
	loc shark = { N / 2, N / 2 };
	for (int i = 1; i <= s; i++) {
		int ny = shark.y + dy[d] * i;
		int nx = shark.x + dx[d] * i;
		ball_map[ny][nx] = 0;
	}
}
void pushstraight() { // 배열 댕김
	for (int i = 1; i < N*N; i++) {
		if (straight[i] != 0) {
			int nowi = i;
			while (1) {
				int ni = nowi - 1;
				if (ni < 1) break;
				if (straight[ni] != 0) break;
				straight[ni] = straight[nowi];
				straight[nowi] = 0;
				nowi = ni;
			}
		}
	}
}
void makestaright() {
	loc now = { N / 2, N / 2 };
	int adder = 1;
	int dir = 0;

	int times = 0;
	int limit_times = 1;
	int cnt = 0;

	int num = 0;
	while (1) {
		int ny = now.y + spin_dy[dir];
		int nx = now.x + spin_dx[dir];
		if (ny == 0 && nx == -1) break;

		num++;
		times++;

		straight[num] = ball_map[ny][nx];

		if (times == limit_times) { // 정해진 길이 만큼 움직이고
			cnt++;
			times = 0;
			dir = (dir + 1) % 4;
		}
		if (cnt == 2) { // 2번 움직였다면 limit + 1
			cnt = 0;
			limit_times += 1;
		}
		now.y = ny;
		now.x = nx;
	}
	pushstraight();
}

bool breakstragiht() {
	int num = 0;
	int cnt = 1;
	int flag = false;
	int lastpoint = 0;
	for (int i = 1; i < N*N; i++) {
		lastpoint = i;
		if (straight[i] == 0)break;
		if (num != straight[i]) {
			if (cnt >= 4) {
				flag = true;
				for (int j = i - cnt; j < i; j++) {
					cnt_ball_in_straight(j);
					straight[j] = 0;
				}

			}
			num = straight[i];
			cnt = 1; // cnt 초기화
		}
		else {
			cnt++;
		}
	}
	if (cnt >= 4) { // 마지막에 한번 더해줘야함
		flag = true;
		for (int j = lastpoint - cnt; j < lastpoint; j++) {
			cnt_ball_in_straight(j);
			straight[j] = 0;
		}
	}
	pushstraight();

	return flag;
}
void makenewstraight() {
	int newstraight[2500] = { 0 };
	int newi = 1;

	int num = straight[1];
	int cnt = 0;
	int lastpoint = 0;
	for (int i = 1; i < N*N; i++) {
		if (straight[i] == 0)break;
		if (newi >= N * N) break;
		if (num != straight[i]) {
			newstraight[newi++] = cnt;
			newstraight[newi++] = num;
			num = straight[i];
			cnt = 1; // cnt 초기화
		}
		else {
			cnt++;
		}
	}
	newstraight[newi++] = cnt;
	newstraight[newi++] = num;

	memset(straight, 0, sizeof(straight));
	for (int i = 1; i < N*N; i++) {
		straight[i] = newstraight[i];
	}
}
void makeball_map() {
	loc now = { N / 2, N / 2 };
	int adder = 1;
	int dir = 0;

	int times = 0;
	int limit_times = 1;
	int cnt = 0;

	int num = 0;
	while (1) {
		int ny = now.y + spin_dy[dir];
		int nx = now.x + spin_dx[dir];
		if (ny == 0 && nx == -1) break;

		num++;
		times++;

		ball_map[ny][nx] = straight[num];

		if (times == limit_times) { // 정해진 길이 만큼 움직이고
			cnt++;
			times = 0;
			dir = (dir + 1) % 4;
		}
		if (cnt == 2) { // 2번 움직였다면 limit + 1
			cnt = 0;
			limit_times += 1;
		}
		now.y = ny;
		now.x = nx;
	}
}




int getscore() {
	//출력: 1x폭발한 1번구슬 + 2x폭발한 2번구슬 개수 + 3x 폭발한 3번구슬 개수
	int sum = 0;
	sum = ballcnt[1] + ballcnt[2] * 2 + ballcnt[3] * 3;
	return sum;
}
void printstraight() {
	cout << endl;
	for (int i = 0; i < N*N; i++) {
		cout << straight[i] << " ";
	}
}
void printballmap() {
	cout << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << ball_map[i][j] << " ";
		}
		cout << endl;
	}
}
int main() {
	init();
	for (int i = 0; i < M; i++) {
		info now = todo[i];
		//1. d방향으로 거리 s 이하인 모든칸에 얼음파편 던지기
		blizard(now.d, now.s);
		//printballmap();
		// 맵 일자 배열로 재구성.
		makestaright();
		//printstraight();

		//2. 연속된 숫자 폭파
		while (1) {
			if (!breakstragiht()) break;
			//printstraight();
		}

		//3. 연속된 숫자파악해서 구슬의 개수
		makenewstraight();
		//printstraight();
		//구슬 번호로 맵 재구성하기.
		makeball_map();
		//printballmap();
	}
	cout << getscore() << endl;
}