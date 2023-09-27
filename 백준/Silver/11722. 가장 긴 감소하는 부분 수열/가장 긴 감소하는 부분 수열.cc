#include<stdio.h>
#define max(x,y) x>y?x:y
int arr[1001];
int memo[1001];
int dp(int n) {
	for (int i = 0; i < n; i++) {
		memo[i] = 1;
		for (int j = 0; j < i; j++) {
			if (arr[j] > arr[i]) memo[i] = max((memo[j] + 1), memo[i]);
		}
	}
	int result = 0;
	for (int i = 0; i < n; i++) {
		result = max(result, memo[i]);
	}
	return result;
}

int main() {
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf(" %d", &arr[i]);
	}
	printf("%d", dp(n));
}