#include<stdio.h>

using namespace std;

int n, num[11];
int max = -1e9;
int min = 1e9;
int plus, minus, mux, div;
void dfs(int val, int index) {

	if (index == n) {
		min = min > val ? val : min;
		max = max < val ? val : max;
		return;
	}
	if (plus>0){
		plus--;
		dfs(val + num[index], index + 1);
		plus++;
	}
	if (minus > 0) {
		minus--;
		dfs(val - num[index], index + 1);
		minus++;
	}
	if (mux > 0) {
		mux--;
		dfs(val * num[index], index + 1);
		mux++;
	}
	if (div > 0) {
		div--;
		int pm = 1;
		if (val < 0) {
			val = -val;
			pm = -1;
		}
		dfs(pm *(val / num[index]), index + 1);
		div++;

	}
}
int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf(" %d", &num[i]);
	}
	scanf(" %d", &plus);
	scanf(" %d", &minus);
	scanf(" %d", &mux);
	scanf(" %d", &div);
	dfs(num[0], 1);
	printf("%d\n", max);
	printf("%d\n", min);
}