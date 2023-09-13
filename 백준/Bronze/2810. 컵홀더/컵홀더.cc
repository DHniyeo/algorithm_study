#include<stdio.h>

int main()
{
	// 커플이 한쌍까지는 사람수 만큼 컵놓을수 있고, n(>2)쌍부터는 n-1 사람이 사용 못함
	int t;
	int sl_cnt = 0;
	scanf("%d", &t);
	char sl[51];
	scanf("%s", sl);
	for (int i = 0; i < t; i++) {
		if (sl[i] == 'L') {
			sl_cnt++;
		}
	}
	sl_cnt = sl_cnt / 2;
	if (sl_cnt <= 1) {
		printf("%d\n", t);
	}
	else {
		printf("%d\n", t - sl_cnt + 1);
	}
}
