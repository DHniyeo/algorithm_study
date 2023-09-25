#include<iostream>
#include<string>
#include<algorithm>
#include<queue>
using namespace std;
int L, C;
char arr[15];
struct cmp {
	bool operator()(string b, string a) {
		if (a < b) return true;
		return false;
	}
};
priority_queue<string, vector<string>, cmp> q;
int cntAIEOU(string c) {
	int cnt = 0;
	int csize = c.size();
	for (int i = 0; i < csize; i++) {
		if (c[i] == 'a' || c[i] == 'i' || c[i] == 'e' || c[i] == 'o' || c[i] == 'u') cnt++;
	}
	return cnt;
}
void dfs(int index, string ch) {
	if (index == C) {
		if (ch.size() == L) {
			int cnt = cntAIEOU(ch);
			if (cnt >= 1 && L - cnt >= 2) {
				sort(ch.begin(), ch.end());
				ch[L] = '\0';
				q.push(ch);
			}
		}
		return;
	}
	dfs(index + 1, ch + arr[index]);
	dfs(index + 1, ch);
}

int main()
{
	scanf("%d %d", &L, &C);
	for (int i = 0; i < C; i++) {
		scanf(" %c", &arr[i]);
	}
	dfs(0,"");

	while (!q.empty()) {
		string a = q.top(); q.pop();
		printf("%s\n",a.c_str());
	}
}