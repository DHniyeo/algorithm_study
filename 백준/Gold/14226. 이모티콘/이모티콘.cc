#include <stdio.h>
#include <algorithm>
#include <queue>
using namespace std;

struct INFO
{
	int monitor;
	int clipboard;
	int t;
};

queue<INFO> q;
int S; // 목표
int visited[2000][2000] = {0}; // 모니터 이모티콘 갯수 방문일지
int result;

void bfs() {
	while (!q.empty()) {
		int m = q.front().monitor;
		int c = q.front().clipboard;
		int t = q.front().t; q.pop();

		if (m == S) {
			result = t;
			return;
		}
		if (m >= 1) {
			// 1. 클립보드 저장(덮어쓰기)
			int nc = m;
			if(visited[m][nc] == 0){
				visited[m][nc] = 1;
				q.push({ m,nc,t + 1 });
			}
			// 2. 클립보드를 화면에 붙여넣기
			if (m + c <= S) {
				if (visited[m+c][c] == 0) {
					visited[m + c][c] = 1;
					q.push({ m + c, c, t + 1 });
				}
			}
			// 3. 이모티콘 하나 삭제
			if (m>0) {
				if (visited[m - 1][c] == 0) {
					visited[m-1][c] = 1;
					q.push({ m-1, c, t + 1 });

				}
			}

		}
	}

}

int main() {

	
	scanf("%d", &S);
	q.push({ 1,0, 0});
	visited[1][0] = 1;
	bfs();
	printf("%d\n", result);
}