//입력  N, K
//물고기수가 가장 왼쪽 어항부터 순서대로 주어짐.
//
//출력 : 물고기가 가장 많이 든 어항과 가장 적게 든 어항의 물고기수 차이가 k이하가 되게 하려면 몇번 정리 해야하는지 출력





#include <iostream>
#include <deque>
using namespace std;

int N, K;
struct loc {
	int y, x;
};
int h, w; // 공중에 뜨는 어항 높이 너비
deque<int> dq[100];

void init() {
	cin >> N >> K;
	for (int i = 0; i < N; i++) {
		int fish_num;
		cin >> fish_num;
		dq[0].push_back(fish_num);
	}
	h = 1; w = 1;
}
void printdq() {
	cout << endl;
	for (int i = N - 1; i >= 0; i--) {
		for (int j = 0; j < dq[i].size(); j++) {
			cout << dq[i][j] << " ";
		}
		cout << endl;
	}
}
void put_rotate() {
	int rotate[100][100] = { 0 };
	for (int i = 0; i < h; i++) { // 뒤집힌 채로 시계방향 90도 돌리기
		for (int j = 0; j < w; j++) {
			rotate[j][h - 1 - i] = dq[i][j];
		}
	}
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			dq[i].pop_front();
		}
	}
	int tmp = h;
	h = w;
	w = tmp;
	for (int i = 0; i < h; i++) { // 뒤집어서 넣어주기
		for (int j = 0; j < w; j++) {
			dq[h - i].push_front(rotate[i][j]);
		}
	}
	h++;
}
void put_rotate2() {
	w = N / 2;
	for (int i = 0; i < w; i++) {
		dq[1].push_front(dq[0][i]);
	}
	for (int i = 0; i < w; i++) {
		dq[0].pop_front();
	}
	h = 2;
	w = N / 4;
	for (int i = 0; i < w; i++) {
		dq[3].push_front(dq[0][i]);
		dq[2].push_front(dq[1][i]);
	}
	for (int i = 0; i < w; i++) {
		dq[0].pop_front();
		dq[1].pop_front();
	}
	h = 4;


}
void fish_mediate() {
	// 인접 어항에 대해 물고기 차를 구하고 차이를 5로 나눈 몪을 d라 할때 숫자가 큰쪽에서 작은 쪽으로 물고기 보냄
	int fish_map[100][100] = { 0 };
	int dy[] = { -1, 0, 1, 0 };
	int dx[] = { 0,-1, 0,1 };
	for (int i = 0; i < h; i++) { // 배열에 옮겨 담기
		for (int j = 0; j < dq[i].size(); j++) {
			fish_map[i][j] = dq[i][j];
		}
	}
	int new_fish_map[100][100] = { 0 };
	for (int i = 0; i < h; i++) { // 배열에 옮겨 담기
		for (int j = 0; j < dq[i].size(); j++) {
			int now = fish_map[i][j];
			for (int k = 0; k < 4; k++) {
				int ny = i + dy[k];
				int nx = j + dx[k];
				if (ny >= N || nx >= N || ny < 0 || nx < 0) continue;
				if (fish_map[ny][nx] == 0) continue;
				int gap = now - fish_map[ny][nx];
				if (gap < 0) {
					// fish_map[ny][nx] 가 큰 경우
					gap *= -1;
					gap /= 5;
					// 두번 작업 할 필요 없음.
					//new_fish_map[ny][nx] -= gap;
					//new_fish_map[i][j] += gap;
				}
				else {
					// 현재 칸 이 더 큰 경우
					gap /= 5;
					new_fish_map[i][j] -= gap;
					new_fish_map[ny][nx] += gap;
				}
			}
			new_fish_map[i][j] += now;
		}
	}
	for (int i = 0; i < h; i++) { // 배열에 옮겨 담기
		for (int j = 0; j < dq[i].size(); j++) {
			dq[i][j] = new_fish_map[i][j];
		}
	}
}
void down_dq() {
	deque<int> tmp;
	for (int i = 0; i < w; i++) { // 역순으로 빼고
		for (int j = 0; j < h; j++) {
			tmp.push_front(dq[j][i]);
		}
	}
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			dq[i].pop_front();
		}
	}
	for (int i = 0; i < w*h; i++) {
		dq[0].push_front(tmp[i]); // 역순으로 넣기
	}

	h = 1; w = 1;
}
int gapfish() {
	int min = 1e9;
	int max = 0;
	for (int i = N - 1; i >= 0; i--) {
		for (int j = 0; j < dq[i].size(); j++) {
			if (min > dq[i][j]) min = dq[i][j];
			if (max < dq[i][j]) max = dq[i][j];
		}
	}
	return max - min;
}
int main() {

	init();
	int times = 0;
	while (K < gapfish()) {
		// 물고기 작은 어항에 한마리 넣기
		int min = 1e9;
		for (int i = 0; i < N; i++) {
			if (min > dq[0][i] && dq[0][i] > 0) {
				min = dq[0][i];
			}
		}
		for (int i = 0; i < N; i++) {
			if (min == dq[0][i]) {
				dq[0][i]++;
			}
		}
		// 맨 왼쪽칸 어항 쌓기
		while (dq[0].size() - w >= h) { // 쌓아 올릴 공간이 해당 높이보다 충분할때 까지 돌리기
			put_rotate();
		}
		// 물고기 조절 작업
		fish_mediate();
		// 물고기 어항 내리기
		down_dq();
		//printdq();
		// n/2개를 공중 부양 후 어항올리기 2번
		put_rotate2();
		//printdq();
		// 물고기 조절작업
		fish_mediate();
		//printdq();
		// 물고기 어항 내리기
		down_dq();
		//printdq();
		times++;
	}
	cout << times << endl;
}