#include<stdio.h>

int main()
{
	int n;
	int result = 0;
	scanf("%d", &n);


	for (int i = 0; i <= n; i++)
	{
		int sum = 0;
		int tmp = i;
		sum += tmp;

		// 245
		while (tmp / 10) {
			sum += tmp % 10;
			tmp = tmp / 10;
		}
		sum += tmp;

		if (sum == n) {
			result = i;
			break;
		}
	}
	printf("%d", result);

}