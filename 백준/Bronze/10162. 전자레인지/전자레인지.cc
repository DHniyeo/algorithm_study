#include<stdio.h>

int main()
{
	int T;
	scanf("%d", &T);
	// A : 300 , B : 60 , C : 10
	if (T % 10 != 0) {
		printf("-1\n");
		return 0;
	}
	else {
		printf("%d ", T / 300);
		T %= 300;
		printf("%d ", T / 60);
		T %= 60;
		printf("%d ", T / 10);
	}
}