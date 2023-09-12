#include<stdio.h>

int main()
{
	int L = 1, P = 1, V = 1;
	int t = 1;
	while (1) {
		scanf("%d %d %d", &L, &P, &V);
		if (L == 0 && P == 0 && V == 0) break;
		int tmp = V%P;
		if (tmp > L) {
			tmp = L;
		}
		printf("Case %d: %d\n", t, L*(V / P) + tmp);
		t++;
	}

}