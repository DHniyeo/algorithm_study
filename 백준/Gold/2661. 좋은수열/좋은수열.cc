#include<iostream>
#include<string>
using namespace std;
int N;

int cnt = 0;
bool isBad(string c) {
	int size = c.size();
	// i 는 갯수
	for (int i = 1; i <= size / 2; i++) {
		string first = c.substr(size - (i * 2), i);
		string second = c.substr(size - i, i);
		if (first == second) return true;
	}
	return false;
}
void dfs(string tmp, int step) {
	if (isBad(tmp)) return;
	if (step == N) {
		cout << tmp << endl;
		exit(0);
		return;
	}
	
	dfs(tmp + "1",step+1);
	dfs(tmp + "2", step + 1);
	dfs(tmp + "3", step + 1);
}
int main() {
	scanf("%d", &N);
	dfs("", 0);
}