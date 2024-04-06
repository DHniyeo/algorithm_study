// 1. 제일 가까운 승객을 찾아서 이동한다.(BFS => 손님 위치 반환, 택시 위치 이동, 연료 소비(연료 바닥 났으면 종료))
// 기름통 확인
// 2. 승객의 목적지 까지 이동(BFS=> 도착했으면 연료 충전.(가는 도중 연료 바닥 났으면 종료)),
// 기름통확인
// 연료 충전

// 입력 : 첫 줄에 N, M, 그리고 초기 연료의 양이 주어진다. (2 ≤ N ≤ 20, 1 ≤ M ≤ N2, 1 ≤ 초기 연료 ≤ 500,000)
// 입력 : 맵 (0은 빈칸, 1은 벽)
// 입력 : 운전 시작하는 칸 (y,x)
// 입력 : 각 승객의 

// 1. vector 돌면서 찾으면 시간초과 될거같은데.. 
// 2. 맵을 만들어 위 왼 오 아래 - 순으로 bfs 찾기 하면 될라나?
#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

int N, M, oil;
int wall_map[20][20];

struct loc {
	int y, x;
};
struct info_queue {
	int y, x, cnt;
};
struct info_vector {
	int y, x, idx;
};
struct info {
	loc start, goal;
	bool finished;
};
bool cmp(info_vector first, info_vector second) {
	if (first.y < second.y) {
		return true;
	}
	else if (first.y == second.y) {
		if (first.x < second.x) {
			return true;
		}
	}
	return false;
}
loc taxi;
vector<info> vc;

void init() {
	cin >> N >> M >> oil;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> wall_map[i][j];
		}
	}
	cin >> taxi.y >> taxi.x;
	taxi.y--; taxi.x--;
	for (int i = 0; i < M; i++) {
		int py, px, gy, gx;
		cin >> py >> px >> gy >> gx;
		py--; px--; gy--; gx--;
		vc.push_back({ py,px,gy,gx, false });
	}
}
int dy[] = { -1,0,1,0 }; // 위 왼 아래 오
int dx[] = { 0,-1,0,1 };

int check_vc(info_queue now) {
	info_queue nnow = now;
	for (int i = 0; i < vc.size(); i++) {
		if (vc[i].finished == true) continue; // 이미 태웠던 승객은 태우지 않음
		if (vc[i].start.y == nnow.y && vc[i].start.x == nnow.x) { // 현재 위치가 vc에 있는 놈이라면
			return i;
		}
	}
	return -1;
}
int findman() {
	int min_dis = 1e9;
	loc nowtaxi = taxi;
	queue<info_queue> q;
	vector<info_vector> idx_vc;
	q.push({nowtaxi.y,nowtaxi.x, 0});
	int visited[20][20] = {0};
	bool Flag = true;
	while (!q.empty()) {
		info_queue now = q.front(); q.pop();
		int idx = check_vc(now);
		if (idx != -1) { // 존재하는 놈이라면 최소 거리찾았다는 것.
			if (Flag) {
				Flag = false;
				min_dis = now.cnt; // 한번에 한해서 최소 거리 갱신
				idx_vc.push_back({ now.y, now.x, idx });
				continue;
			}
			if (min_dis == now.cnt) { // 최소 거리와 같은 거리 값을 가지고 있다면
				idx_vc.push_back({ now.y, now.x, idx });
				continue;
			}
		}
		if (min_dis < now.cnt) break; // 거리 최솟값보다 더 먼 거리면 안봄.
		

		for (int i = 0; i < 4; i++) {
			int ny = now.y + dy[i];
			int nx = now.x + dx[i];
			if (ny >= N || nx >= N || ny < 0 || nx < 0) continue;
			if (wall_map[ny][nx] == 1) continue;
			if (visited[ny][nx] == 1) continue;
			visited[ny][nx] = 1;
			q.push({ ny,nx,now.cnt + 1 });
		}
	}
	if (idx_vc.size() == 0) return -1;
	sort(idx_vc.begin(), idx_vc.end(), cmp); // 행이 가장 작고 열이 가장 작은 idx 구해냄
	int index = idx_vc[0].idx;
	taxi.y = vc[index].start.y; // 택시 위치 갱신
	taxi.x = vc[index].start.x; // 택시 위치 갱신
	oil = oil - min_dis; // 기름 최신화
	vc[index].finished = true;
	return index;
}
int movetogoal(int idx) {
	loc start = vc[idx].start;
	loc goal = vc[idx].goal;
	queue<info_queue> q;
	q.push({ start.y, start.x, oil });

	int visited[20][20] = { 0 };
	int spend_oil = 0;
	while (!q.empty()) {
		info_queue now = q.front(); q.pop();
		if (now.y == goal.y && now.x == goal.x) { // 목적지 도달시
			taxi.y = now.y; // 택시 위치 갱신
			taxi.x = now.x; // 택시 위치 갱신
			spend_oil = oil - now.cnt; // 사용한 기름
			oil = now.cnt; // 기름 최신화
			return spend_oil;
		}
		for (int i = 0; i < 4; i++) {
			int ny = now.y + dy[i];
			int nx = now.x + dx[i];
			if (ny >= N || nx >= N || ny < 0 || nx < 0) continue;
			if (wall_map[ny][nx] == 1) continue;
			if (visited[ny][nx] == 1) continue;
			visited[ny][nx] = 1;
			q.push({ ny,nx,now.cnt - 1 });
		}
	}
	return -1; // 못가는 거라면
}
int main() {
	init();
	// 승객 정보
	
	for (int i = 0; i < M; i++) {
		//cout << i + 1 << endl;
		// 1. 제일 가까운 승객을 찾아서 이동한다.(BFS => 손님 위치 반환, 택시 위치 이동, 연료 소비(연료 바닥 났으면 종료))
		int idx = findman(); // vector의 idx 반환
		//cout << vc[idx].start.y << vc[idx].start.x << endl;
		//cout << "oil : " <<oil << endl;
		if (oil<=0 || idx == -1) { // 태우러 가는 도중에 바닥났다면 종료
			oil = -1;
			break;
		}
		// 2. 승객의 목적지 까지 이동(BFS=> 도착했으면 연료 충전.(가는 도중 연료 바닥 났으면 종료)),
		int spend_oil = movetogoal(idx);
		//cout << "oil : " << oil << endl;
		if (oil<0 || spend_oil == -1) { // oil이 0인경우는 다시 채워지므로 종료 x
			oil = -1;
			break;
		}
		// 기름 충전
		oil = oil + spend_oil * 2;
		//cout << "oil : " << oil << endl;
	}

	cout << oil << endl;
	return 0;
}