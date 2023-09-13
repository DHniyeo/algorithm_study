#include<stdio.h>

int main()
{
	int n;
	int arr[1000];
	scanf("%d", &n);
	getchar();
	int max = -1;
	int sum = 0;
	for (int i = 0; i < n; i++) {
		scanf(" %d", &arr[i]);
		if (max < arr[i]) {
			max = arr[i];
		}
		sum += arr[i];
	}
	printf("%d\n", sum + max * (n - 2));
}