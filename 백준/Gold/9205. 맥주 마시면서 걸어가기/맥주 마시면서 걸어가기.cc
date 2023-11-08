#include<stdio.h>
#include<string.h>
#include<queue>
#include<math.h>

using namespace std;

struct point {
	int y, x;

};

int main()
{
	int t; 
	scanf("%d", &t);
	for (int tc = 1; tc <= t; tc++) {
		point start;
		point end;
		point store[100];
		int visited[100]; // 방문한 지점은 방문할 필요가없음.
		memset(visited, 0, sizeof(visited));
		int n;
		scanf(" %d", &n);
		scanf(" %d %d", &start.y, &start.x);
		for (int i = 0; i < n; i++) {
			scanf(" %d %d", &store[i].y, &store[i].x);
		}
		scanf(" %d %d", &end.y, &end.x);
		
		queue<point> q;
		q.push(start);
		int flag = 0;
		while (!q.empty()) {
			point tmp = q.front(); q.pop();
			
			if (abs(end.y - tmp.y) + abs(end.x - tmp.x) <= 1000) {
				flag = 1;
				break;
			}

			for (int i = 0; i < n; i++) {
				if (visited[i] == 1) continue;
				int dist = abs(store[i].y - tmp.y) + abs(store[i].x - tmp.x);
				if (dist <= 1000) {
					visited[i] = 1;
					q.push({ store[i].y, store[i].x });
				}
			}

		}

		if (flag) {
			printf("happy\n");
		}
		else {
			printf("sad\n");
		}
	}
}