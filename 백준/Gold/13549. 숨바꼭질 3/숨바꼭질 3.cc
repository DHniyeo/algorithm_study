#include <stdio.h>
#include <algorithm>
#include <queue>
using namespace std;

int min_time = 100000;
int visited[100001] = {0};

struct INFO {
	int start;
	int end;
	int cnt;
};

queue<INFO> q;
void bfs() {
	// x-1, x+1, 2x
	while (!q.empty()) {
		INFO now = q.front(); q.pop();
	
		visited[now.start] = 1;

		if (now.start == now.end) {
			if (min_time > now.cnt) {
				min_time = now.cnt;
			}
			break;
		}
		if (now.start * 2 <= 100000 && !visited[now.start * 2]) q.push({ now.start * 2,now.end,now.cnt});
		if (now.start - 1 >= 0 && !visited[now.start - 1]) q.push({ now.start - 1,now.end,now.cnt + 1 });
		if (now.start + 1 <= 100000 && !visited[now.start + 1]) q.push({ now.start + 1,now.end,now.cnt + 1 });
	}


}

int main() {
	int n, k;
	scanf("%d %d", &n, &k);
	getchar();

	q.push({ n,k,0 });
	bfs();
	

	printf("%d\n",min_time);
}