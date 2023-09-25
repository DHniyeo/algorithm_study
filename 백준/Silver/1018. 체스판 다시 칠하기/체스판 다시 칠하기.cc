#include <stdio.h>
#include <queue>
#define min(x,y) x>y?y:x
using namespace std;

int n, m;
const char chess[2][8][9]
= { {
	"WBWBWBWB",
	"BWBWBWBW",
	"WBWBWBWB",
	"BWBWBWBW",
	"WBWBWBWB",
	"BWBWBWBW",
	"WBWBWBWB",
	"BWBWBWBW"
	},
	{
	"BWBWBWBW",
	"WBWBWBWB",
	"BWBWBWBW",
	"WBWBWBWB",
	"BWBWBWBW",
	"WBWBWBWB",
	"BWBWBWBW",
	"WBWBWBWB",
	}
};
char map[50][51];
int FindMin(int y, int x) {
	int a = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (map[i + y][j + x] != chess[0][i][j]) {
				a++;
			}
		}
	}
	int b = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (map[i + y][j + x] != chess[1][i][j]) {
				b++;
			}
		}
	}
	return min(a,b);
}
int main()
{
	int n, m;
	scanf("%d %d", &n, &m);
	getchar();
	for (int i = 0; i < n; i++) {
		scanf(" %s", &map[i]);
	}
	int min = 99999;
	for (int i = 0; i <= n - 8; i++) {
		for (int j = 0; j <= m - 8; j++) {
			int tmp = FindMin(i, j);
			if (min > tmp) {
				min = tmp;
			}
		}
	}
	printf("%d", min);

}