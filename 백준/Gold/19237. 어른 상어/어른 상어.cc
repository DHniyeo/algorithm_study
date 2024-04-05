// 상어는 고유 번호가 있따.
// 1번 상어가 대빵, 다쫓아냄
// 1. 자신의 위치에서 냄새 뿌리기
// 2. 상어의 동시 이동 자신의 냄새를 해당칸에 뿌림
// 3. 냄새는 상어가 k번 이동하면 사라짐
// 이동 방향 결정할 때는, 인접한 칸 중에 아무냄새가 없는 칸의 방향으로 잡고, 그런칸이 없으면 자신의 냄새가 있는 칸의 방향으로 잡음.
// 우선순위는 상어마다 다를 수 있고, 같은 상어라도 현재 상어가 보고있는 방향에 따라 다를 수 도 있다.
// 우선순위는 주어짐.

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;
int N, M, K;
struct info_map {
	int num, dir;
};
struct info_smell {
	int num;
	int cnt; // 머무른 횟수
};
info_map shark_map[20][20] = {0};
vector<info_smell> smell_map[20][20];
int priority_map[401][5][5];
const int dy[] = {0, -1, 1, 0,0};
const int dx[] = {0, 0, 0, -1, 1}; // 위(1), 아래(2), 왼쪽(3), 오른쪽(4)

void init() {
	
	cin >> N >> M >> K; // 맵크기, 상어수, 냄새 사라지는 시간
	for (int i = 0; i < N; i++) { // 상어 번호 배치 맵에 반영
		for (int j = 0; j < N; j++) {
			cin >> shark_map[i][j].num;
		}
	}
	for (int k = 1; k <= M; k++) { // 상어 방향 맵에 반영
		int tmp_dir;
		cin >> tmp_dir;
		for (int i = 0; i < N; i++) { // 
			for (int j = 0; j < N; j++) {
				if (shark_map[i][j].num == k) {
					shark_map[i][j].dir = tmp_dir; // 1~4
				}
			}
		}
	}
	
	for (int i = 1; i <= M; i++) { // 우선순위
		for (int j = 1; j <= 4; j++) {
			for (int k = 1; k <= 4; k++) {
				cin >> priority_map[i][j][k];
			}
		}
	}
}

void spreadSmell() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (shark_map[i][j].num != 0) {
				smell_map[i][j].push_back({ shark_map[i][j].num , 0 });
			}
		}
	}
}

void moveshark() {
	info_map new_map[20][20]; // 동시 진행 하므로 현재맵을 보고 새로운 맵을 생성함.
	memset(new_map, 0, sizeof(new_map));
	// 상어의 현재 바라보고 있는 방향에 따라 다음 방향의 순서가 결정됨.
	// 이동 방향 결정할 때는, 인접한 칸 중에 아무냄새가 없는 칸의 방향으로 잡고, 그런칸이 없으면 자신의 냄새가 있는 칸의 방향으로 잡음.
	// 해당 방향에 상어가 있을 때 상어 번호가 더 작다면 덮어씌우기
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (shark_map[i][j].num != 0) {
				info_map shark = shark_map[i][j];
				// 아무 냄새 없는 칸의 방향 찾기
				bool flag = false;
				for (int k = 1; k <= 4; k++) {
					int ny = i + dy[priority_map[shark.num][shark.dir][k]];
					int nx = j + dx[priority_map[shark.num][shark.dir][k]];
					if (ny >= N || nx >= N || ny < 0 || nx < 0) continue;
					if (smell_map[ny][nx].size() != 0) continue;
					flag = true;
					// 옮겨진 위치를 새로운 맵에서 갱신
					shark.dir = priority_map[shark.num][shark.dir][k]; // 방향 갱신
					if (new_map[ny][nx].num == 0 || new_map[ny][nx].num > shark.num) { // 빈칸이거나 기존에 있던 놈 보다 수가 작아야함
						new_map[ny][nx] = shark; // 맵에서 갱신
					}
					break;
				}
				if (!flag) {
					for (int k = 1; k <= 4; k++) {
						int ny = i + dy[priority_map[shark.num][shark.dir][k]];
						int nx = j + dx[priority_map[shark.num][shark.dir][k]];
						if (ny >= N || nx >= N || ny < 0 || nx < 0) continue;
						bool findsmell = false;
						for (int t = 0; t < smell_map[ny][nx].size(); t++) {
							if (smell_map[ny][nx][t].num == shark.num) {
								findsmell = true;
								break;
							}
						}
						if (!findsmell) continue;

						// 옮겨진 위치를 새로운 맵에서 갱신
						shark.dir = priority_map[shark.num][shark.dir][k]; // 방향 갱신
						if (new_map[ny][nx].num == 0 || new_map[ny][nx].num > shark.num) { // 빈칸이거나 기존에 있던 놈 보다 수가 작아야함
							new_map[ny][nx] = shark; // 맵에서 갱신
						}
						break;
					}
				}

			}
		}
	}
	memcpy(shark_map, new_map, sizeof(shark_map));
}
void removeSmell() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			vector<info_smell> nextSmell;
			int size = smell_map[i][j].size();
			for (int k = 0; k < size; k++) {
				if (smell_map[i][j][k].cnt < K) { // K보다 작을 때만 다시 추가해줌.
					nextSmell.push_back(smell_map[i][j][k]);
				}
			}
			smell_map[i][j] = nextSmell;
		}
	}
}
void plusSmellTime() {
	// 냄새 시간 증가
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int size = smell_map[i][j].size();
			for (int k = 0; k < size; k++) {
				smell_map[i][j][k].cnt += 1;
			}
		}
	}
}


bool checkmap() {
	int sum = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (shark_map[i][j].num != 0) {
				sum += shark_map[i][j].num;
			}
		}
	}
	if (sum == 1) return true;
	else return false;
}
void printmap() {
	cout << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << shark_map[i][j].num << " ";
		}
		cout << endl;
	}
}
int main() {
	init();
	int time = 0;
	
	// 자신의 위치에서 냄새 뿌리기
	spreadSmell();
	while (1) {
		// 1번 상어만 격자에 남아 있다면 break;
		if (checkmap()) {
			break;
		}
		// time이  1000을 넘는다면 break;
		if (time >= 1000) {
			time = -1;
			break;
		}		
		// 상어의 동시 이동
		moveshark();
		// 냄새 시간 증가 
		plusSmellTime();
		// 냄새 k번 이동하면 사라짐
		removeSmell();
		// 자신의 위치에서 냄새 뿌리기
		spreadSmell();

		time++;
		//printmap();
	}
	cout << time;

}