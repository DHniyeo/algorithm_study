#include<iostream>
#include<cstring>
#include<vector>
#include<deque>
using namespace std;
// M개를 활성 상태로 변경하려고함 => dfs로 활성화 할 바이러스 선택
// 0 빈칸, 1은 벽, 2는 바이러스
// 활성화된 바이러스가 비활성 바이러스 칸으로 이동시 활성으로 변함. => 사실상 상관없음. 바이러스가 이미 퍼져있는걸로 인정.
// 최소시간 구하기. 바이러스를 전부 퍼트릴 수 없다면 -1 반환.

int N, M;
int map[50][50];
char spread_map[50][50];
int choosedVirus[10] = {};
int result = -1;
struct info {
	int y, x;
};
vector <info> vc;

void init() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
			if (map[i][j] == 2) {
				vc.push_back({ i,j });
			}
		}
	}
}

bool findEmpty() { // 빈공간 찾기
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (spread_map[i][j] == '#') { // 빈공간이 있는경우
				return true;
			}
		}
	}
	return false;
}
int findMax(int visited[50][50]) { // 최댓값 찾기
	int Max = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (spread_map[i][j] == '*') continue;
			if (visited[i][j] > Max) {
				Max = visited[i][j];
			}
		}
	}
	return Max-1; // visited[][]가 1부터 시작하므로 -1을 해줌.
}
int spreadVirus() {
	
	int visited[50][50] = {0};
	memset(spread_map,0,sizeof(spread_map));
	deque<info> q;


	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (map[i][j] == 0) {
				spread_map[i][j] = '#'; // 빈칸 처리
			}
			else if (map[i][j] == 1) {
				spread_map[i][j] = '-'; // 벽
			}
			else if (map[i][j] == 2) {
				spread_map[i][j] = '*'; // 비활성화 바이러스
			}
		}
	}

	for (int i = 0; i < vc.size(); i++) {
		if (choosedVirus[i] == 1) { // 활성화된 바이러스 표시
			spread_map[vc[i].y][vc[i].x] = '0'; // 활성화 바이러스
			q.push_back({ vc[i].y, vc[i].x });
			visited[vc[i].y][vc[i].x] = 1;
		}
	}
	const int dy[] = {-1,1,0,0};
	const int dx[] = {0,0,-1,1};

	while (!q.empty()) {
		info now = q.front(); q.pop_front();

		for (int i = 0; i < 4; i++) {
			int ny = now.y + dy[i];
			int nx = now.x + dx[i];
			if (ny >= N || nx >= N || ny < 0 || nx < 0) continue;
			if (visited[ny][nx] != 0) continue;
			if (spread_map[ny][nx] == '-') continue;
			else if (spread_map[ny][nx] == '#') {
				spread_map[ny][nx] = '0';
			}
			visited[ny][nx] = visited[now.y][now.x] + 1;
			q.push_back({ ny,nx });
		}
	}
	if (!findEmpty()) { // 빈공간이 없을때
		return findMax(visited);
	}
	return -1;
}
void chooseVirus(int depth, int now) {
	
	if (depth == M) {
		int tmp = spreadVirus();
		if (tmp == -1) return; // 결과가 -1인 경우는 생각 X
		if (result == -1) result = tmp;
		else if (result > tmp){
			result = tmp;
		}
		return;
	}
	for (int i = now; i < vc.size(); i++) {
		if (choosedVirus[i] == 1) continue;
		choosedVirus[i] = 1;
		chooseVirus(depth + 1, i+1);
		choosedVirus[i] = 0;
	}
}


int main() {
	init();
	chooseVirus(0, 0);

	cout << result << endl;
	return 0;
}