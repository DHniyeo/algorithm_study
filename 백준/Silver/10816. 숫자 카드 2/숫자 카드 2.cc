#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

vector<int> dict;
vector<int> target;
int N, M;
void init() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		int num;
		cin >> num;
		dict.push_back(num);
	}
	cin >> M;
	for (int i = 0; i < M; i++) {
		int num;
		cin >> num;
		target.push_back(num);
	}
	sort(dict.begin(), dict.end());
}
int upper_bound(int find_val) {
	int st = 0;
	int en = N;
	while (st < en) {
		int mid = (st + en) / 2;
		if (dict[mid] > find_val) {
			en = mid;
		}
		else {
			st = mid + 1;
		}
	}
	return st;
}
int lower_bound(int find_val){
	int st = 0;
	int en = N;
	while (st < en) {
		int mid = (st + en) / 2;
		if (dict[mid] >= find_val) {
			en = mid;
		}
		else {
			st = mid + 1;
		}
	}
	return st;
}

int main() {
	init();

	for (auto a : target) {
		// cout << upper_bound(dict.begin(), dict.end(), a) - lower_bound(dict.begin(), dict.end(), a) << " ";
		cout << upper_bound(a) - lower_bound(a) << " ";
	}
	
}