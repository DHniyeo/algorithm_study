#include<stdio.h>

int N, S;
int sum = 0;
int result = 0;
int arr[20];
void dfs(int index)
{
	if (index == N) {
		if (sum == S) {
			result++;
		}
		return;
	}

	sum = sum + arr[index];
	dfs(index + 1);
	sum = sum - arr[index];
	dfs(index + 1);
	return;
}
int main()
{

	scanf("%d %d", &N, &S);
	for (int i = 0; i < N; i++) {
		scanf(" %d", &arr[i]);
	}
	dfs(0);
	if (S == 0) result--;
	printf("%d", result);
}