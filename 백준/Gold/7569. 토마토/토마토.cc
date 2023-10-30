#include<stdio.h>
#include<queue>
using namespace std;
struct INFO {
	int z, y, x;
	int cnt;
};

int n, m, h;
int map[101][101][101];
int isThereRaw() {
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < m; k++) {
				if (map[i][j][k] == 0)
					return 1;
			}
		}
	}
	return 0;
}

int main() {

	scanf("%d %d %d", &m, &n, &h);

	for (int i = 0; i < h; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < m; k++) {
				scanf(" %d", &map[i][j][k]);
			}
		}
	}
	
	queue<INFO> q;
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < m; k++) {
				if (map[i][j][k] == 1) q.push({ i,j,k,0 });
			}
		}
	}
	int result = -1;
	int cnt_check = -1;
	int dz[] = {0 , 0 , -1, 1 , 0, 0};
	int dy[] = {-1, 1, 0 , 0 , 0 ,0 };
	int dx[] = {0, 0 , 0 , 0 , -1, 1};
	while (!q.empty()) {
		INFO tmp = q.front(); q.pop();
		if (cnt_check != tmp.cnt) {
			cnt_check = tmp.cnt;
			if (!isThereRaw()) {
				result = tmp.cnt;
				break;
			}
		}
		for (int i = 0; i < 6; i++) {
			int nz = tmp.z + dz[i];
			int ny = tmp.y + dy[i];
			int nx = tmp.x + dx[i];
			if (nz >= h || ny >= n || nx >= m || nz < 0 || ny < 0 || nx < 0) continue;
			if (map[nz][ny][nx] == 1 || map[nz][ny][nx] == -1) continue;
			map[nz][ny][nx] = 1;
			q.push({ nz,ny,nx,tmp.cnt + 1 });
		}
	}
	printf("%d\n", result);
}