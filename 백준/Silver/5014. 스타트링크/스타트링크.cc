#include<stdio.h>
#include<queue>
using namespace std;
struct info {
	int now;
	int cnt;
};
int F, S, G, U, D;
int visited[1000001];
queue<info> q;

int main() {
	

	scanf("%d %d %d %d %d", &F, &S, &G, &U, &D);
	
	q.push({S,0});
	visited[S] = 1;

	int result = -1;
	while (!q.empty()) {
		info tmp = q.front(); q.pop();
		
		if (tmp.now == G) {
			result = tmp.cnt;
			break;
		}

		int Up_next = tmp.now + U;
		if (Up_next <= F && !visited[Up_next]) {
			visited[Up_next] = 1;
			q.push({ Up_next, tmp.cnt + 1 });
		}
		int Down_next = tmp.now - D;
		if (Down_next > 0 && !visited[Down_next]) {
			visited[Down_next] = 1;
			q.push({ Down_next, tmp.cnt + 1 });
		}
	}

	if (result == -1) printf("use the stairs\n");
	else {
		printf("%d\n", result);
	}

}