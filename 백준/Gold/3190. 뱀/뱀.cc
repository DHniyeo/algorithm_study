#include<stdio.h>

int n,k,l;
int map[100][100]; // 빈공간은 0 뱀위치는 1 사과는 2
char dir_data[10001];
// D 는 + 1, L 은 + 3
int dy[] = {0,1,0,-1};
int dx[] = {1,0,-1,0};

int main() {
	scanf(" %d", &n);
	scanf(" %d", &k);
	for (int i = 0; i < k; i++) {
		int y, x;
		scanf(" %d %d", &y, &x);
		map[y-1][x-1] = 2;
	}
	scanf(" %d", &l);
	for (int i = 0; i < l; i++) {
		int time;
		char dir;
		scanf(" %d %c", &time, &dir);
		dir_data[time] = dir;
	}

	int time = 0;
	int head_y = 0, head_x = 0, dir = 0; // 초기 방향은 오른쪽
	int tail_y = 0, tail_x = 0, tail_index = 0;
	// 꼬리가 당겨질때 해당 인덱스를 알아야 하기 때문에 시간에 따른 뱀 위치를 저장
	int snake_y[10001] = {0}, snake_x[10001] = { 0 };
	snake_y[0] = 0; snake_x[0] = 0;

	map[0][0] = 1;
	while (1) {
		time++;
		head_y = head_y + dy[dir];
		head_x = head_x + dx[dir];

		// 벽에 부딛힐 경우
		if (head_y >= n || head_x >= n || head_y < 0 || head_x < 0) break;
		// 자기 몸과 부딛힐 경우
		if (map[head_y][head_x] == 1) break;
		// 사과인 경우
		else if (map[head_y][head_x] == 2) {
			snake_y[time] = head_y;
			snake_x[time] = head_x;
			map[head_y][head_x] = 1;
		}
		// 빈공간인 경우
		else if (map[head_y][head_x] == 0) {
			snake_y[time] = head_y;
			snake_x[time] = head_x;
			map[head_y][head_x] = 1;
			// 현 꼬리위치 빈공간으로 초기화
			map[tail_y][tail_x] = 0;
			// 다음 위치로 꼬리위치 변경
			tail_index++;
			tail_y = snake_y[tail_index];
			tail_x = snake_x[tail_index];
		}

		// 해당 초가 끝난 후에 방향전환
		if (dir_data[time] == 'D') {
			dir = (dir + 1) % 4;
		}
		if (dir_data[time] == 'L') {
			dir = (dir + 3) % 4;
		}

	}
	printf("%d\n", time);



}