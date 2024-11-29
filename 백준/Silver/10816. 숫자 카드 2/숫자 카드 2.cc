#include<iostream>
#include<unordered_map>
#include<vector>
using namespace std;
int N, M;
unordered_map<int,int> dict;
vector<int> vc;
int st = -1e9;
int en = 1e9;
void init() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		int num;
		cin >> num;
		if(dict[num]) dict[num] += 1;
		else dict[num] = 1;
	}
	cin >> M;
	for (int i = 0; i < M; i++) {
		int num;
		cin >> num;
		vc.push_back(num);
	}
}


int main() {
	init();
	for (auto num : vc) {
		cout << dict[num] << " ";
	}
}