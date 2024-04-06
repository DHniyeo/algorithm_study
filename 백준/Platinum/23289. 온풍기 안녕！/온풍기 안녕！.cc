//1. 집에 있는 모든 온풍기에서 바람이 한 번 나옴
//2. 온도가 조절됨
//3. 온도가 1 이상인 가장 바깥쪽 칸의 온도가 1씩 감소
//4. 초콜릿을 하나 먹는다
//5. 조사하는 모든 칸의 온도가 K 이상이 되었는지 검사.모든 칸의 온도가 K이상이면 테스트를 중단하고, 아니면 1부터 다시 시작한다.
#include<iostream>
#include<cstring>
#include<queue>
using namespace std;

int R, C, K ,W;

int room[20][20] = {0};
int temperature[20][20] = { 0 };
int wall[20][20][20][20] = {0}; // 시작 y,x 끝 y, x

int hotdy[5][3] = { {},{-1,0,1},{-1,0,1},{-1,-1,-1},{1,1,1} };
int hotdx[5][3] = { {},{1,1,1},{-1,-1,-1},{-1,0,1},{-1,0,1} };

int dy[] = {0,0,0,-1,1};
int dx[] = {0,1,-1,0,0};
// 1 : 오른쪽
// 2 : 왼쪽
// 3 : 위쪽
// 4 : 아래쪽

struct info_queue {
	int y, x, cnt;
};

void init() {

	memset(room, 0, sizeof(room));
	memset(temperature, 0, sizeof(temperature));
	memset(wall, 0, sizeof(wall));

	cin >> R >> C >> K;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cin >> room[i][j];
		}
	}
	cin >> W;
	for (int i = 0; i < W; i++){
		int x, y, t;
		cin >> x >> y >> t;
		x--; y--;
		if (t == 0) {
			wall[x][y][x - 1][y] = 1;
			wall[x-1][y][x][y] = 1;
		}
		else {
			wall[x][y][x][y+1] = 1;
			wall[x][y+1][x][y] = 1;
		}
	}
}
void bfs(int y, int x) {
	int tmp_temperature[20][20] = { 0 };
	int starty = y + dy[room[y][x]];
	int startx = x + dx[room[y][x]];
	queue<info_queue> q;
	q.push({ starty,startx,5 });
	int visited[20][20] = { 0 };
	while (!q.empty()) {
		info_queue now = q.front(); q.pop();
		if (now.cnt == 0) break;
		tmp_temperature[now.y][now.x] = now.cnt;

		for (int i = 0; i < 3; i++) {
			int ny = now.y + hotdy[room[y][x]][i];
			int nx = now.x + hotdx[room[y][x]][i];
			if (ny >= R || nx >= C || ny < 0 || nx < 0)continue;
			if (visited[ny][nx] == 1) continue;
			if (i == 1) { // 직선방향일때
				if (wall[now.y][now.x][ny][nx] == 1)continue; // 갈려는 지점이 벽으로 막혀있다면
			}
			else { // 대각선방향 일때
				// 현재위치로 오기전 지점 찾기 (직진지점)
				int tmpy = now.y - dy[room[y][x]];
				int tmpx = now.x - dx[room[y][x]];
				// 거쳐가지는 지점 찾기
				int throwy = tmpy + hotdy[room[y][x]][i];
				int throwx = tmpx + hotdx[room[y][x]][i];
				if (wall[now.y][now.x][throwy][throwx] == 1) continue; // 두 지점 중 하나라도 막혀있다면
				if (wall[throwy][throwx][ny][nx] == 1) continue;
			}
			visited[ny][nx] = 1;
			q.push({ ny,nx,now.cnt - 1 });
		}
	}
	
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			temperature[i][j] += tmp_temperature[i][j];
		}
	}
}
void hotMachine() {
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (room[i][j] > 0 && room[i][j] < 5) { // 1 ~ 4
				bfs(i, j);
			}
		}
	}
}

void TempMediate() {
	int tmp_temperature[20][20] = { 0 };
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			int now = temperature[i][j];
			if (now == 0) continue;

			int lowtemp = 0;
			for (int k = 1; k <= 4; k++) {
				int ny = i + dy[k];
				int nx = j + dx[k];
				if (ny >= R || nx >= C || ny < 0 || nx < 0)continue;
				if (temperature[ny][nx] >= now) continue;
				if (wall[i][j][ny][nx] == 1) continue;
				int mediV = (now - temperature[ny][nx])/4; // 조정해야하는 값
				tmp_temperature[ny][nx] += mediV; // 온도 옮겨주기
				lowtemp += mediV;
			}
			tmp_temperature[i][j] += (temperature[i][j] - lowtemp);
		}
	}
	memcpy(temperature, tmp_temperature, sizeof(temperature));
}

void outSideTempminus() {
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (i == 0 || j == 0 || i == R - 1 || j == C - 1) {
				if (temperature[i][j] > 0) {
					temperature[i][j]--;
				}
			}
		}
	}
}

bool checkmap() {
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (room[i][j] == 5 && temperature[i][j] < K) return false;
		}
	}
	return true;
}
int main() {


	init();
	int choco = 0;
	while (1) {

		//1. 집에 있는 모든 온풍기에서 바람이 한 번 나옴
		hotMachine();
		//2. 온도가 조절됨
		TempMediate();
		//3. 온도가 1 이상인 가장 바깥쪽 칸의 온도가 1씩 감소
		outSideTempminus();
		//4. 초콜릿을 하나 먹는다
		choco++;
		if (choco > 100) {
			choco = 101;
			break;
		}
		//5. 조사하는 모든 칸의 온도가 K 이상이 되었는지 검사.모든 칸의 온도가 K이상이면 테스트를 중단하고, 아니면 1부터 다시 시작한다.
		if (checkmap()) {
			break;
		}
	}
	cout << choco << endl;

}