#include<iostream>
using namespace std;
int N;
int map[21][21];
int holesum = 0;
// 직사각형을 찾고 나머지 부분 더해주기
void init() {
	cin >> N;
	holesum = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> map[i][j];
			holesum += map[i][j];
		}
	}
}
int sector1(int x, int y, int d1) {
	int cnt = 0;
	for (int r = 1; r < x + d1; r++) {
		if (r < x) { // r < x 일때
			for (int c = 1; c <= y; c++) {
				cnt += map[r][c];
			}
		}
		else { // r >= x 일때
			for (int c = 1; c <= y - 1 - (r - x); c++) {
				cnt += map[r][c];
			}
		}
	}
	return cnt;
}
int sector2(int x, int y, int d2) {
	int cnt = 0;
	for (int c = y + 1; c <= N; c++) {
		if (c > y + d2) {
			for (int r = 1; r <= x + d2; r++) {
				cnt += map[r][c];
			}
		}
		else {
			for (int r = 1; r <= x + d2 - 1 - (y + d2 - c); r++) {
				cnt += map[r][c];
			}
		}
	}
	return cnt;
}
int sector3(int x, int y, int d1, int d2) {
	int cnt = 0;
	for (int r = x + d1; r <= N; r++) {
		if (r >= x + d1 + d2) {
			for (int c = 1; c < y - d1 + d2; c++) {
				cnt += map[r][c];
			}
		}
		else {
			for (int c = 1; c < y - d1 + d2 - ((x + d1 + d2) - r); c++) {
				cnt += map[r][c];
			}
		}
	}
	return cnt;
}
int sector4(int x, int y, int d1, int d2) {
	int cnt = 0;
	for (int r = x + d2 + 1; r <= N; r++) {
		if (r > x + d1 + d2) {
			for (int c = y - d1 + d2; c <= N; c++) {
				cnt += map[r][c];
			}
		}
		else {
			for (int c = y - d1 + d2 + 1 + ((x + d1 + d2) - r); c <= N; c++) {
				cnt += map[r][c];
			}
		}
	}
	return cnt;
}
int getMax(int num[5]) {
	int MaxV = 0;
	for (int i = 0; i < 5; i++) {
		if (num[i] > MaxV) MaxV = num[i];
	}
	return MaxV;
}
int getMin(int num[5]) {
	int MinV = 1e9;
	for (int i = 0; i < 5; i++) {
		if (num[i] < MinV) MinV = num[i];
	}
	return MinV;
}
int solve() {// x, y, d1, d2 선택하기
	int result = 1e9;
	for (int x = 1; x <= N; x++) {
		for (int y = 1; y <= N; y++) {
			for (int d1 = 1; d1 <= N - 2; d1++) {
				for (int d2 = 1; d2 <= N - 2; d2++) {
					if (x + d1 + d2 > N || 1 > y - d1 || y + d2 > N) continue;
					int sec[5] = { 0 };
					sec[0] = sector1(x, y, d1);
					sec[1] = sector2(x, y, d2);
					sec[2] = sector3(x, y, d1, d2);
					sec[3] = sector4(x, y, d1, d2);
					sec[4] = holesum - sec[0] - sec[1] - sec[2] - sec[3];

					int maxV = getMax(sec);
					int minV = getMin(sec);
					int tmp = maxV - minV;
					if (result > tmp) result = tmp;
				}
			}
		}
	}
	return result;
}

int main() {
	init();
	cout << solve() << endl;
}