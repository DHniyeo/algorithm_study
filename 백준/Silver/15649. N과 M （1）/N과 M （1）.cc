#include<iostream>
#include<vector>
using namespace std;

int N, M; //	최대숫자, 갯수
int visited[9];
void init() {
	cin >> N >> M;
}
int cnt = 0;
vector<int> vc;
void dfs(int depth) {
	if (depth == M) {
		for (auto i : vc) {
			cout << i << " ";
		}
		cout << '\n';
		return;
	}
	for (int i = 1; i <= N; i++) {
		if (visited[i] == 1) continue;
		visited[i] = 1;
		vc.push_back(i);
		dfs(depth + 1);
		vc.pop_back();
		visited[i] = 0;
	}

}

int main()
{
	init();
	dfs(0);

}