//비어있는 칸 중에서 좋아하는 학생이 인접한 칸에 가장 많은 칸으로 자리를 정한다.
//1을 만족하는 칸이 여러 개이면, 인접한 칸 중에서 비어있는 칸이 가장 많은 칸으로 자리를 정한다.
//2를 만족하는 칸도 여러 개인 경우에는 행의 번호가 가장 작은 칸으로, 그러한 칸도 여러 개이면 열의 번호가 가장 작은 칸으로 자리를 정한다.
// 탐색하면서 주변에 좋아하는 학생 카운트 -> 최댓값 구하고 vector(최댓값을 가진 인덱스,비어있는칸 갯수,y,x) 만들고 정렬해서 맨앞에 나온 값을 맵에 추가(숫자)
// 최종적으로 탐색하면서 좋아하는 학생 카운트하기.
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

int N;
int survey[400][5]; // 0번 인덱스는 현재 학생의 번호임
int dy[] = { -1,1,0,0 };
int dx[] = { 0,0, -1,1 };
struct info_map {
	int num, likeNum;
};
struct info_vector {
	int max, emptyblock, y, x;
};

bool cmp(const info_vector & first,const info_vector & second) {
	if (first.emptyblock > second.emptyblock) {
		return true;
	}
	else if (first.emptyblock == second.emptyblock) {
		if (first.y < second.y) {
			return true;
		}
		else if (first.y == second.y) {
			if (first.x < second.x) {
				return true;
			}
		}
	}
	return false;
}
info_map MAP[20][20] = {0};

void init() {
	memset(MAP, 0, sizeof(MAP));
	memset(survey, 0, sizeof(survey));
	cin >> N;	

	for (int i = 0; i < N*N; i++) {
		for (int j = 0; j < 5; j++) {
			cin >> survey[i][j];
		}
	}

}
void putStudent(int index) {

	//비어있는 칸 중에서 좋아하는 학생이 인접한 칸에 가장 많은 칸으로 자리를 정한다.
	//1을 만족하는 칸이 여러 개이면, 인접한 칸 중에서 비어있는 칸이 가장 많은 칸으로 자리를 정한다.
	//2를 만족하는 칸도 여러 개인 경우에는 행의 번호가 가장 작은 칸으로, 그러한 칸도 여러 개이면 열의 번호가 가장 작은 칸으로 자리를 정한다.

	// 탐색하면서 주변에 좋아하는 학생 카운트 -> 최댓값 구하고 vector(최댓값,비어있는칸 갯수,y,x) 만들고 정렬해서 맨앞에 나온 값을 맵에 추가(숫자와 최댓값)
	int StudentNum = survey[index][0];
	vector<info_vector> vc;
	

	int cntMax = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (MAP[i][j].num == 0) { // 해당 칸이 빈칸이라면
				int likecnt = 0;
				int emptycnt = 0;
				for (int k = 0; k < 4; k++) {
					int ny = i + dy[k];
					int nx = j + dx[k];
					if (ny >= N || nx >= N || ny < 0 || nx < 0)continue;
					if (MAP[ny][nx].num == 0) emptycnt++;
					else {
						for (int t = 1; t <= 4; t++) {
							if (MAP[ny][nx].num == survey[index][t]) likecnt++;
						}
					}
				}
				if (cntMax < likecnt) { // 해당 칸에서부터 다시 쌓음
					vc.clear();
					cntMax = likecnt;
					vc.push_back({ cntMax, emptycnt, i,j });
				}
				else if (cntMax == likecnt) { // 벡터에 추가.
					vc.push_back({ cntMax, emptycnt, i,j });
				}
			}
		}
	}
	if (vc.size() == 0) return;
	sort(vc.begin(), vc.end(), cmp);
	info_vector FindLoc = vc[0]; // 찾은 위치
	MAP[FindLoc.y][FindLoc.x].num = StudentNum;
}
int findresult() {
	for (int i = 0; i < N; i++) { // 현재 주위에 좋아하는 사람 수 파악하기
		for (int j = 0; j < N; j++) {
			int likecnt = 0;
			int StudentNum = MAP[i][j].num;
			int index = 0;
			for (int k = 0; k < N*N; k++) { // survey에서 인덱스 찾아야함
				if (survey[k][0] == StudentNum) {
					index = k;
					break;
				}
			}
			for (int k = 0; k < 4; k++) {
				int ny = i + dy[k];
				int nx = j + dx[k];
				if (ny >= N || nx >= N || ny < 0 || nx < 0)continue;
				for (int t = 1; t <= 4; t++) {
					if (MAP[ny][nx].num == survey[index][t]) likecnt++;
				}
			}
			MAP[i][j].likeNum = likecnt;
		}
	}

	int sum = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (MAP[i][j].likeNum == 1) {
				sum += 1;
			}
			else if (MAP[i][j].likeNum == 2) {
				sum += 10;
			}
			else if (MAP[i][j].likeNum == 3) {
				sum += 100;
			}
			else if (MAP[i][j].likeNum == 4) {
				sum += 1000;
			}
		}
	}
	return sum;
}
void printMap() {
	cout << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << MAP[i][j].num << " ";
		}
		cout << endl;
	}

	cout << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << MAP[i][j].likeNum << " ";
		}
		cout << endl;
	}
}

int main() {
	init();

	for (int i = 0; i < N*N; i++) {
		putStudent(i);
	}
	//printMap();
	int result = findresult();
	cout << result << endl;
}