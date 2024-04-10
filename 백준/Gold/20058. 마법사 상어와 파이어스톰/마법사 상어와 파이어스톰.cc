//1. 모든 부분 격자를 시계 방향으로 90도 회전
//2. 이후 얼음이 있는 칸 3개 또는 그 이상과 인접해있지 않은 칸은 얼음의 양이 1 줄어든다

#include<iostream>
#include<cstring>
#include<queue>
using namespace std;


int N, Q;
int iceMap[64][64];
int mapsize;
int schedule[1000];

int TwoN(int num) { // 메모이제이션 하면 더 좋을거같긴함.

	int result = 1;
	for (int i = 0; i < num; i++) {
		result *= 2;
	}
	return result;
}

void init() {
	cin >> N >> Q;
	mapsize = TwoN(N);
	for (int i = 0; i < mapsize; i++) {
		for (int j = 0; j < mapsize; j++) {
			cin >> iceMap[i][j];
		}
	}
	for (int i = 0; i < Q; i++) {
		cin >> schedule[i];
	}
}

void Rotate(int y, int x, int size) {
	
	int tmp[64][64] = { 0 }; // 옮겨담음
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			tmp[i][j] = iceMap[y + i][x + j];
		}
	}

	for (int i = 0; i < size; i++) { // 회전한 배열 집어넣기
		for (int j = 0; j < size; j++) {
			iceMap[y + i][x + j] = tmp[size-1-j][i];
		}
	}

}
void doL(int num) {
	int L = num;
	int TwoL = TwoN(L);

	for (int i = 0; i < mapsize; i += TwoL) {
		for (int j = 0; j < mapsize; j += TwoL) {
			Rotate(i, j, TwoL);
		}
	}
}
void iceMelting() {
	int tmp[64][64] = { 0 };
	
	int dy[] = { 0,1,0,-1 };
	int dx[] = { 1,0,-1,0 };

	memset(tmp, 0, sizeof(tmp));
	for (int i = 0; i < mapsize; i++) {
		for (int j = 0; j < mapsize; j++) {
			if (iceMap[i][j] == 0) continue; // 더이상 녹을게 없다.
			int cnt = 0;
			for (int k = 0; k < 4; k++) {
				int ny = i + dy[k];
				int nx = j + dx[k];
				if (ny >= mapsize || nx >= mapsize || ny < 0 || nx < 0) continue;
				if (iceMap[ny][nx] == 0) continue;
				cnt++;
			}
			if (cnt < 3) {
				tmp[i][j] = iceMap[i][j] - 1;
			}
			else {
				tmp[i][j] = iceMap[i][j];
			}
		}
	}
	memcpy(iceMap, tmp, sizeof(iceMap));
}

void printMap() {
	cout << endl;
	for (int i = 0; i < mapsize; i++) {
		for (int j = 0; j < mapsize; j++) {
			cout << iceMap[i][j] << " ";
		}
		cout << endl;
	}
}
int sumIce() {
	int result = 0;
	for (int i = 0; i < mapsize; i++) {
		for (int j = 0; j < mapsize; j++) {
			result += iceMap[i][j];
		}
	}
	return result;
}
int visited[64][64];
int dy[] = { -1,1,0,0 };
int dx[] = { 0,0,-1,1 };
struct loc{
	int y, x;
};
struct info {
	int cnt, size;
};
info cntNum(int y ,int x) {
	queue<loc> q;
	q.push({ y,x });
	info result = {1,iceMap[y][x]};


	while (!q.empty()) {
		loc now = q.front(); q.pop();
		for (int i = 0; i < 4; i++) {
			int ny = now.y + dy[i];
			int nx = now.x + dx[i];
			if (ny >= mapsize || nx >= mapsize || ny < 0 || nx < 0) continue;
			if (iceMap[ny][nx] == 0) continue; // 얼음 이없다면 안감
			if (visited[ny][nx] == 1) continue; // 방문 한곳이라면 안감
			visited[ny][nx] = 1;
			result.cnt++; // 횟수 증가
			result.size += iceMap[ny][nx]; // 크기 증가
			q.push({ ny,nx });
		}
	}

	return result;
}

int getBiGBolck() {
	int result = 0;
	memset(visited, 0, sizeof(visited));

	for (int i = 0; i < mapsize; i++) {
		for (int j = 0; j < mapsize; j++) {
			if (visited[i][j] == 1) continue;
			if (iceMap[i][j] > 0) {
				visited[i][j] = 1;
				info now = cntNum(i, j);
				if (now.cnt > result) { // 가장 큰 덩어리 찾기
					result = now.cnt;
				}
			}
		}
	}
	return result;
}
int main() {
	init();
	for (int i = 0; i < Q; i++) {
		int now = schedule[i];
		//1. 모든 부분 격자를 시계 방향으로 90도 회전
		if (now != 0) doL(now);
		//cout << endl << "after rotate : "<< now << endl;
		//printMap();
		//2. 이후 얼음이 있는 칸 3개 또는 그 이상과 인접해있지 않은 칸은 얼음의 양이 1 줄어든다
		iceMelting();
		//cout << endl<< "after melting" << endl;
		//printMap();
	}
	cout << sumIce() << endl;
	cout << getBiGBolck() << endl;



}