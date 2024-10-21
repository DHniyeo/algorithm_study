#include<iostream>
using namespace std;
long long d[1'000'001];
int N;
void init() {
	cin >> N;
	d[1] = 0;
	d[2] = 1;
}
long long solve(int N) {
	if (N <= 1) return 0;
	if (d[N] == 0) d[N] = (N - 1) * (solve(N - 1) + solve(N - 2)) % 1'000'000'000;
	return d[N];
}
int main() {
	init();
	
	cout << solve(N);
}