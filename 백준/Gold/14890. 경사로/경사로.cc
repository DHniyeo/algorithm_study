#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
int n, l;
int map[100][100];


int result = 0;
void map_rotate() {
	int tmp[100][100] = { 0 };
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			tmp[i][j] = map[j][n - 1 - i];
		}
	}
	memcpy(map, tmp, sizeof(map));
}

void cango(int x) {
	
	int now = map[0][x];
	int block[100] = {0}; // 이미 경사로가 설치된 구역
	for (int i = 1; i < n; i++) {
		if (now == map[i][x]) continue;
		if (abs(now - map[i][x]) > 1) return;
		// gap이 1 날때
		// 내리막길 발견
		if (now - map[i][x] == 1) {
			now = map[i][x];
			for (int j = 0; j < l; j++) {
				if (i + j >= n) return;
				if (map[i + j][x] != now) return;
				block[i + j] = 1;
			}
			i = i + l - 1;
		}
		// 오르막길 발견
		else if (map[i][x] - now == 1) {
			for (int j = 1; j <= l; j++) {
				if (map[i - j][x] != now) return;
				if (block[i - j] == 1) return;
			}
			now = map[i][x];
		}
	}
	result++;
	return;
}




int main() {
	scanf("%d %d", &n, &l);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf(" %d", &map[i][j]);
		}
	}
	for (int i = 0; i < n; i++) {
		cango(i);
	}
	map_rotate();
	for (int i = 0; i < n; i++) {
		cango(i);
	}
	printf("%d", result);
}