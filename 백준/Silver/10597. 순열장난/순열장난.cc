#include<stdio.h>
#include<string>
#include<vector>
using namespace std;

string numstring;
int nsize;
int N;
int visited[51];
vector<int> vec;
void dfs(int index) {
	if (index >= nsize)
	{
		if (vec.size() >= N) {
			for (int i = 0; i < N; i++) {
				printf("%d ", vec[i]);
			}
			exit(0);
		}
		return;
	}
	for (int i = 1; i <= 2; i++) {
		string tmp = numstring.substr(index, i);
		int tmp_int = stoi(tmp);
		if (visited[tmp_int])continue;
		if (tmp_int > N) continue;
		vec.push_back(tmp_int);
		visited[tmp_int] = 1;
		dfs(index + i);
		visited[tmp_int] = 0;
		vec.pop_back();
	}
}
int main()
{
	char c[100];
	scanf("%s",c);
	numstring = c;
	
	nsize = numstring.size();
	if (nsize <= 9) N = nsize;
	else {
		N = (nsize - 9) / 2 + 9;
	}
	dfs(0);
	return 0;
}