#include<iostream>
#include<string>
using namespace std;
long long d[201][201] = { 0 };
long long make_d(int i, int j) {
	if (i < j) return 0;
	if (i < 0 || j < 0) return 0;
	if (d[i][j] == 0) {
		d[i][j] = make_d(i - 1, j) + make_d(i - 1, j - 1);
		if (d[i][j] > 1000000000) d[i][j] = 1000000001;
	}
	return d[i][j];
}
int N, M, K;
void init() {
	cin >> N >> M >> K;
}
string solve() {
	string result;
	while (1) {
		if (N == 0 || M == 0) break;
		long long criteria = make_d(N + M - 1, M);
		if (K > criteria) {
			result += 'z';
			K -= criteria;
			M--;
		}
		else {
			result += 'a';
			N--;
		}
	}
	if (N == 0) {
		for (int i = 0; i < M; i++) {
			result += 'z';
		}
	}
	else if (M == 0) {
		for (int i = 0; i < N; i++) {
			result += 'a';
		}
	}
	return result;
}

int main() {
	init();
	d[0][0] = 1;
	d[1][0] = 1;
	d[0][1] = 1;
	long long max = make_d(N + M, N);
	if (max < K) {
		cout << "-1" << '\n';
		return 0;
	}
	cout << solve() << '\n';
}