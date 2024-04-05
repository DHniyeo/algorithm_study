// 0.상어는 0, 0에 있던 물고기 방향과 같고 물고기를 먹고들어간다.

// 1.물고기 번호가 작은 물고기부터 순서대로 이동.
// - 이동할 수 있는칸은 빈칸과 다른물고기가 있는칸, 이동할 수 없는 칸은 상어가 있거나 공간의 경계를 넘는칸.
// - 각 물고기는 방향이 이동할 수 있는 칸을 향할때까지 45도 반시계 회전하고, 만약 이동할 수 있는 칸이 없으면 이동을 하지 않고 그 외엔 이동한다.물고기가 다른 물고기 칸으로 이동할때는 서로의 위치를 바꾼다.
//
// 2. 상어의 이동
// - 상어는 여러칸 이동가능
// - 물고기 먹으면 해당 물고기 방향 가져옴
// - 이동중에 지나가는 칸의 물고기는 먹지 않는다.
// - 상어가 이동할수 있는칸이 없으면 집으로 간다.


// 벡터로 물고기 방향 및 사망여부 저장
// 맵 최신화
// 상어가 먹을 수 있는 물고기 번호의 합의 최댓값 구하기.
//상어 뚜루뚜뚜뚜룹.. 

//dfs(상어의 위치) {
//
//	벡터로 상어가 먹을 수 있는 물고기 위치 반환
//		상어가 먹을 물고기가 없다면
//		상어가 먹은 물고기 번호의 합의 최댓값 구하기
//		종료
//
//		for 물고기 먹을수 있는 위치돌기
//			물고기 정보 벡터와 맵 최신화(상어의 위치 옮기기, 물고기의 이동, 점수 올리기)
//			dfs(상어의 이동 후 위치)
//			물고기 정보 벡터와 맵 원위치
//			물고기의 이동전 위치
//}

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#define MapSize 4
#define SharkNumber 30
using namespace std;

const int dy[] = {-1,-1,0,1,1,1,0,-1};
const int dx[] = {0,-1,-1,-1,0,1,1,1};
struct info {
	int num;
	int y, x;
	int dir;
	bool died;
};
bool cmp(const info & first, const info & second) {
	return first.num < second.num;
}

int map[MapSize][MapSize]; // 현재 맵상태 반영 // 상어는 30
vector<info> fish; // 물고기 정보
info shark; // 상어 정보
int result = 0;
void init() {
	for (int i = 0; i < MapSize; i++) {
		for (int j = 0; j < MapSize; j++) {
			int a, b;
			cin >> a >> b;
			fish.push_back({ a, i,j ,b-1, false}); // 0 ~ 7  ↑, ↖, ←, ↙, ↓, ↘, →, ↗
			map[i][j] = a;
		}
	}
	shark.y = -1;
	shark.x = -1;
	shark.num = SharkNumber;
	sort(fish.begin(), fish.end(), cmp); // 물고기 번호 순대로 정렬
}
void printmap() {
	cout << endl;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << map[i][j] << " ";
		}
		cout << endl;
	}
}
vector<info> findCanEat() {
	vector<info> tmp;
	info nowshark = shark;
	for (int i = 1; ; i++) {
		int ny = nowshark.y + dy[nowshark.dir];
		int nx = nowshark.x + dx[nowshark.dir];
		if (ny >= MapSize || nx >= MapSize || ny < 0 || nx < 0) break;
		if (map[ny][nx] != 0) {
			tmp.push_back({ map[ny][nx], ny, nx, fish[map[ny][nx] - 1].dir, false }); // 먹을 수 있는 물고기 정보 추가
		}
		nowshark.y = ny;
		nowshark.x = nx;
	}
	return tmp;
}
void eatfish(int goal_y, int goal_x) { // 상어가 해당 물고기를 먹는것에만 집중. 벡터와 맵이 변경됨.
	if (shark.y != -1) {
		map[shark.y][shark.x] = 0; // 현재 상어 위치 비우기
	}
	fish[map[goal_y][goal_x] - 1].died = true; // 해당 물고기 사망 처리
	shark.dir = fish[map[goal_y][goal_x] - 1].dir;
	shark.y = fish[map[goal_y][goal_x] - 1].y;
	shark.x = fish[map[goal_y][goal_x] - 1].x;

	map[goal_y][goal_x] = SharkNumber; // 상어 이동
}
void movefish() {
// 1.물고기 번호가 작은 물고기부터 순서대로 이동.
// - 이동할 수 있는칸은 빈칸과 다른물고기가 있는칸, 이동할 수 없는 칸은 상어가 있거나 공간의 경계를 넘는칸.
// - 각 물고기는 방향이 이동할 수 있는 칸을 향할때까지 45도 반시계 회전하고, 만약 이동할 수 있는 칸이 없으면 이동을 하지 않고 그 외엔 이동한다.물고기가 다른 물고기 칸으로 이동할때는 서로의 위치를 바꾼다.
	for (int i = 0; i < fish.size(); i++) {
		info nowfish = fish[i];
		int cnt = 8;
		if (nowfish.died == true) continue; // 이미 죽은 물고기는 이동 x
		while (cnt--) {
			int ny = nowfish.y + dy[nowfish.dir];
			int nx = nowfish.x + dx[nowfish.dir];
			if (ny >= MapSize || nx >= MapSize || ny < 0 || nx < 0 || map[ny][nx] == SharkNumber) // 벽이나 상어 만나는 경우
			{
				nowfish.dir= (nowfish.dir+1) %8; // 방향전환
				continue;
			}
			if (map[ny][nx] == 0) { // 빈 공간인 경우 해당 공간으로 이동
				map[nowfish.y][nowfish.x] = 0;
				nowfish.y = ny;
				nowfish.x = nx;
				fish[i] = nowfish; // 벡터 최신화
				map[nowfish.y][nowfish.x] = nowfish.num; // 맵 최신화
				break;
			}
			else { // 다른 물고기가 있는 경우 자리 바꾸기
				map[nowfish.y][nowfish.x] = map[ny][nx]; // 맵에서 기존 자리에 상대 물고기 채워넣기
				nowfish.y = ny;							 // 새로운 좌표 등록
				nowfish.x = nx;
				fish[map[ny][nx] - 1].y = fish[i].y;     // 벡터에서 상대 물고기 위치 갱신하기
				fish[map[ny][nx] - 1].x = fish[i].x;
				fish[i] = nowfish; // 벡터에서 현재 물고기 위치 갱신하기
				map[nowfish.y][nowfish.x] = nowfish.num; // 새로운 자리에 현재 물고기 채워넣기
				break;
			}
		}
	}
}
void dfs(int score) {
	vector<info> canEat = findCanEat();
	//	벡터로 상어가 먹을 수 있는 물고기 위치 반환
	//		상어가 먹을 물고기가 없다면
	if (canEat.size() == 0) {
		//		상어가 먹은 물고기 번호의 합의 최댓값 구하기
		if (result < score) result = score;
		return;
	}
	
	//		for 물고기 먹을수 있는 위치돌기
	for (int i = 0; i < canEat.size(); i++) {
	//	물고기 정보 벡터와 맵 최신화(상어의 위치 옮기기, 물고기의 이동, 점수 올리기)
		info nowfish = canEat[i];
		int backup_map[MapSize][MapSize];
		memcpy(backup_map, map, sizeof(map));
		info backup_shark = shark;
		vector<info> backup_fish = fish;
		eatfish(nowfish.y, nowfish.x); // 물고기 먹기
		movefish();					   // 물고기 이동
		dfs(score + nowfish.num);
		//	물고기 정보 벡터와 맵 원위치
		memcpy(map, backup_map, sizeof(map));
		shark = backup_shark;
		fish = backup_fish;
	}
}

int main() {
	init();
	// 물고기 먹고 물고기 이동하고 들어가기
	int score = map[0][0]; // 0,0 위치의 물고기 번호
	eatfish(0, 0);
	//printmap();
	movefish();
	//printmap();
	dfs(score);

	cout << result << endl;
}