//1. 벨트가 로봇과 함께 한칸 회전
//2. 가장 먼저 벨트에 올라간 로봇부터 벨트가 회전하는 방향으로 한 칸 이동할 수 있다면 이동.이동 못하면 가만히.내리는 위치면 내림.
//1) 로봇이동하려면 이동하려는 칸에 로봇이 없고 내구도가 1 이상 남아있어야한다.
//3. 올리는 위치에 있는 칸의 내구도가 0이 아니면 올리는 위치에 로봇을 올린다.
//4. 내구도가 0인 칸의 개수가 K개 이상이라면 과정을 종료.

#include<iostream>
#include<vector>
using namespace std;
int N, K;

int A[200] = { 0 };
int Robot[200] = { 0 };
void init() {
	cin >> N >> K;
	for (int i = 0; i < 2 * N; i++) {
		cin >> A[i];
	}
}
void Rotate() {
	// 맵 이동
	int tmp = A[2 * N - 1];
	for (int i = 2 * N - 1; i > 0; i--) {
		A[i] = A[i - 1];
	}
	A[0] = tmp;

	// 로봇 이동
	tmp = Robot[2 * N - 1];
	for (int i = 2 * N - 1; i > 0; i--) {
		Robot[i] = Robot[i - 1];
	}
	Robot[0] = tmp;
	// 언제든지 로봇이 내리는 위치에 도달하면 그 즉시 내린다
	if (Robot[N - 1] == 1) {
		Robot[N - 1] = 0;
	}
}
void Robotmove() {
	// 맨뒤의 로봇부터 움직임 
	for (int i = 2 * N - 2; i >= 0; i--) { // 맨 마지막에 있던 칸에 로봇은 없음
		if (Robot[i] == 1 && Robot[i+1] == 0 && A[i + 1] >= 1) { // 해당칸에 로봇이 있고, 다음칸에 로봇이 없고, 다음칸의 내구도가 1이상일때 
			Robot[i + 1] = Robot[i]; // 이동
			Robot[i] = 0;
			// 올리거나 로봇이 이동하는 칸의 내구도는 1 감소.
			A[i + 1] --;
		}
	}

	// 언제든지 로봇이 내리는 위치에 도달하면 그 즉시 내린다
	if (Robot[N - 1] == 1) {
		Robot[N - 1] = 0;
	}
}
bool checkBlock() {
	int cnt = 0;
	for (int i = 0; i < 2 * N; i++) {
		if (A[i] == 0) cnt++;
	}
	if (cnt >= K) return true;
	else return false;
}

void printmap() {
	cout << endl;
	for (int i = 0; i < 2 * N; i++) {
		cout << A[i] << " ";
	}
	cout << endl;

	for (int i = 0; i < 2 * N; i++) {
		cout << Robot[i] << " ";
	}
	cout << endl;
}
int main() {
	init();
	int time = 0;
	while (1) {
		time++;
		// 올리거나 로봇이 이동하는 칸의 내구도는 1 감소.
		//1. 벨트가 로봇과 함께 한칸 회전
		Rotate();
		//printmap();
		//2. 가장 먼저 벨트에 올라간 로봇부터 벨트가 회전하는 방향으로 한 칸 이동할 수 있다면 이동.이동 못하면 가만히.내리는 위치면 내림.
		//1) 로봇이동하려면 이동하려는 칸에 로봇이 없고 내구도가 1 이상 남아있어야한다.
		Robotmove();
		//printmap();
		//3. 올리는 위치에 있는 칸의 내구도가 0이 아니면 올리는 위치에 로봇을 올린다.
		if (A[0] > 0) {
			Robot[0] = 1; // 로봇 올리고
			A[0]--;
		}
		//printmap();
		//4. 내구도가 0인 칸의 개수가 K개 이상이라면 과정을 종료.
		if (checkBlock()) {
			break;
		}
	}
	cout << time << endl;

}