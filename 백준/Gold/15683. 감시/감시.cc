#include<stdio.h>
#include<vector>
#include<string.h>

using namespace std;

int n, m;
int num_cctv;
int result = 1e9;
int map[8][8];
int t_map[8][8];

struct info {
	int y, x, cctv_v, cctv_dir;
};

vector<info> v;

int MIN(int a, int b) {
	if (a > b) return b;
	else {
		return a;
	}
}

void change(int y, int x, int dir) {
	const int dy[] = { -1 , 0, 1, 0};
	const int dx[] = { 0, 1, 0, -1};
	while (1) {
		y = y + dy[dir];
		x = x + dx[dir];
		if (y >= n || x >= m || y < 0 || x < 0) break;
		if (t_map[y][x] == 6) break;
		if(t_map[y][x] == 0 ) t_map[y][x] = 7;
	}
}


void set_t_map() {
	memcpy(t_map, map, sizeof(map));
	for (int i = 0; i < num_cctv; i++) {
		if (v[i].cctv_v == 1) {
			change(v[i].y, v[i].x, v[i].cctv_dir);
		}
		else if (v[i].cctv_v == 2) {
			change(v[i].y, v[i].x, v[i].cctv_dir);
			change(v[i].y, v[i].x, (v[i].cctv_dir + 2) % 4);
		}
		else if (v[i].cctv_v == 3) {
			change(v[i].y, v[i].x, v[i].cctv_dir);
			change(v[i].y, v[i].x, (v[i].cctv_dir + 1) % 4);
		}
		else if (v[i].cctv_v == 4) {
			change(v[i].y, v[i].x, v[i].cctv_dir);
			change(v[i].y, v[i].x, (v[i].cctv_dir + 1) % 4);
			change(v[i].y, v[i].x, (v[i].cctv_dir + 2) % 4);
		}
		else if (v[i].cctv_v == 5) {
			change(v[i].y, v[i].x, v[i].cctv_dir);
			change(v[i].y, v[i].x, (v[i].cctv_dir + 1) % 4);
			change(v[i].y, v[i].x, (v[i].cctv_dir + 2) % 4);
			change(v[i].y, v[i].x, (v[i].cctv_dir + 3) % 4);
		}
	}
}
int cnt_safe_f() {
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (t_map[i][j] == 0) cnt++;
		}
	}
	return cnt;
}
void dfs(int depth) {
	if (depth == num_cctv) {
		// cctv 내용 적용(t_map에 적용)
		set_t_map();

		// min 값 확인
		int cnt_safe = cnt_safe_f();
		result = MIN(result, cnt_safe);
		return;
	}
	for (int i = 0; i < 4; i++) {
		v[depth].cctv_dir = i;
		dfs(depth + 1);
	}
}


int main() {
	num_cctv = 0;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf(" %d", &map[i][j]);
			if (map[i][j] >= 1 && map[i][j] <= 5) {
				v.push_back({ i,j,map[i][j],-1});
				num_cctv++;
			}
		}
	}
	dfs(0);
	printf("%d\n", result);

}