#include<stdio.h>
#include<stack>
using namespace std;

int map[101][101];
struct info {
	int x, y, d, g;
};
struct loc {
	int x, y;
};
info info_data[20];
int n;

// 반시계 방향 순
const int dx[] = {1,0,-1,0};
const int dy[] = {0,-1,0,1};

int find_result() {
	int cnt = 0;
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			if (map[i][j] == 1 && map[i + 1][j] == 1 && map[i][j + 1] == 1 && map[i + 1][j + 1] == 1)
				cnt++;
		}
	}
	return cnt;
}

// map을 색칠해줌.
void make_dragon_map(info now) {

	// 0 세대 반영.
	stack<int> dir_stores; // 적용된 방향 정보 저장.
	
	// 현재 지점 맵 반영
	map[now.x][now.y] = 1;
	
	// 끝점 저장.
	loc endpoint;
	endpoint.x = now.x + dx[now.d];
	endpoint.y = now.y + dy[now.d];
	

	// 끝점 맵 반영
	map[endpoint.x][endpoint.y] = 1;

	dir_stores.push(now.d); // 방향 정보 저장

	for (int i = 0; i < now.g ; i++) {
		// 저장했던 방향 역순으로 뽑아내면서 반시계 방향으로 회전해서 반영
		stack<int> dir_store = dir_stores;
		while (!dir_store.empty()) {
			int dir = dir_store.top(); dir_store.pop();
			dir = (dir + 1) % 4; // 반시계 90도 회전
			endpoint.x += dx[dir];
			endpoint.y += dy[dir];
			map[endpoint.x][endpoint.y] = 1;

			// 이때 까지 움직인 방향 저장
			dir_stores.push(dir);
		}
	}
}

int main()
{
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		scanf(" %d %d %d %d", &info_data[i].x, &info_data[i].y, &info_data[i].d, &info_data[i].g);
	}

	for (int i = 0; i < n; i++) {
		make_dragon_map(info_data[i]);
	}

	printf("%d\n",find_result());

}