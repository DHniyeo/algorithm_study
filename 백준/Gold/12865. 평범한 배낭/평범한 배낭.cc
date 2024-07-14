#include<iostream>
#include<algorithm>
using namespace std;
int n, k; // 물품의 수와 최대 무게제한
int w[101]; // 무게
int v[101]; // 가치
int dp[101][100001]; // index 와 무게제한 
void init() {
	cin >> n >> k;
	for (int i = 1; i <= n; i++) {
		cin >> w[i] >> v[i];
	}
}
void make_dp_table() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= k; j++) {
			if (j < w[i]) { // 무게 제한을 넘는 물건 이라면
				dp[i][j] = dp[i - 1][j];
			}
			else {
				dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - w[i]] + v[i]);
			}
		}
	}
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();
	make_dp_table();
	cout << dp[n][k] << endl;
}