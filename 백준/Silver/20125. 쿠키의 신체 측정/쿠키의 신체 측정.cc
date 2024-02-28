#include<stdio.h>

char map[1001][1001];
int head_x = -1;
int head_y = -1;
int n;
void find_head() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (map[i][j] == '*') {
				head_x = i; // 머리위치 저장
				head_y = j; // 머리위치 저장
				return;
			}
		}
	}
}


int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf(" %s", &map[i]);
	}

	find_head();
	// 왼팔, 오른팔
	int left_arm = 0, right_arm = 0;
	for (int j = 0; j < n; j++) {
		if (j < head_y && map[head_x + 1][j] == '*') left_arm++;
		if (j > head_y && map[head_x + 1][j] == '*') right_arm++;
	}

	// 허리
	int waist = 0;
	for (int i = head_x+2; i < n; i++) {
		if (map[i][head_y] == '*') waist++;
		else break;
	}

	// 왼쪽, 오른쪽 다리
	int left_leg = 0;
	int right_leg = 0;
	for (int i = head_x + 2; i < n; i++) {
		if (map[i][head_y - 1] == '*') left_leg++;
		if (map[i][head_y + 1] == '*') right_leg++;
	}

	printf("%d %d\n", head_x + 2, head_y + 1);
	printf("%d %d %d %d %d\n",left_arm, right_arm, waist, left_leg, right_leg);

}