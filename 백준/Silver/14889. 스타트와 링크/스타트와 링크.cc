#include <stdio.h>
#include <algorithm>
using namespace std;

int n;
int info[20][20];
int Start_team[10];
int Link_team[10];
int used[20];


int ability_gap() {
	int Team_num = n / 2;
	int Start_ability= 0;
	for (int i = 0; i < Team_num -1; i++) {
		for (int j = i + 1; j < Team_num; j++) {
			Start_ability += info[Start_team[i]][Start_team[j]];
			Start_ability += info[Start_team[j]][Start_team[i]];
		}
	}
	int Link_ability= 0;
	for (int i = 0; i < Team_num - 1; i++) {
		for (int j = i + 1; j < Team_num; j++) {
			Link_ability += info[Link_team[i]][Link_team[j]];
			Link_ability += info[Link_team[j]][Link_team[i]];
		}
	}
	int gap = abs(Start_ability - Link_ability);
	return gap;
}


int min_val = 1e9;
void pick_dfs(int node, int si) {
	if (node == n / 2) {
		// 팀 생성
		int s_index = 0;
		int l_index = 0;
		for (int i = 0; i < n; i++) {
			if (used[i] == 1)
				Start_team[s_index++] = i;
			else
				Link_team[l_index++] = i;
		}

		int gap = ability_gap();
		min_val = min_val > gap ? gap: min_val;
	}

	for (int i = si; i < n; i++) {
		if (used[i] == 0) {
			used[i] = 1;
			pick_dfs(node + 1, i + 1);
			used[i] = 0;
		}
	}

}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf(" %d", &info[i][j]);
		}
	}
	pick_dfs(0, 0);

	printf("%d\n", min_val);
}