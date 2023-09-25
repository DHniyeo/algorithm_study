#include<stdio.h>
#include<vector>
#include<string.h>

using namespace std;
int map[9][9];
int ResultMap[9][9];
vector<pair<int, int>> v;
int NumOfZero = 0;
void FindBlank() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (map[i][j] == 0)
				v.push_back({ i,j });
		}
	}
}
bool isDup(int y, int x, int num) {
	int py3 = y / 3;
	int px3 = x / 3;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (map[i + 3 * py3][j + 3 * px3] == num) return true;
		}
	}
	for (int i = 0; i < 9; i++) {
		if (map[y][i] == num) return true;
	}
	for (int i = 0; i < 9; i++) {
		if (map[i][x] == num) return true;
	}
	return false;
}

void dfs(int index) {
	if (index == NumOfZero) {
		memcpy(ResultMap, map, sizeof(map));
		return;
	}

	for (int i = 1; i <= 9; i++) {
		int y = v[index].first;
		int x = v[index].second;
		if (isDup(y, x, i))continue;
		map[y][x] = i;
		dfs(index + 1);
		map[y][x] = 0;
	}
}


int main() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			scanf(" %d", &map[i][j]);
		}
	}
	FindBlank(); // vector 생성
	NumOfZero = v.size();
	dfs(0);

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			printf("%d ", ResultMap[i][j]);
		}
		printf("\n");
	}
}