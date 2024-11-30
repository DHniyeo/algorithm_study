#include<iostream>
#include<vector>
#include<unordered_map>
#include<algorithm>
using namespace std;

int N;
unordered_map<int,bool> m;
vector<int> dict;
vector<int> target;
int mem_result[1'000'000] = {0};

void init() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		int num;
		cin >> num;
		if (!m[num]) {
			m[num] = true;
			dict.push_back(num);
		}
		target.push_back(num);
	}
	sort(dict.begin(), dict.end());
}
int find_target_index(int target_num) {

	int st = 0;
	int en = dict.size() - 1;
	while (st <= en) {
		int mid = (st + en) / 2;
		if (dict[mid] < target_num) {
			st = mid + 1;
		}
		else if (dict[mid] > target_num) {
			en = mid - 1;
		}
		else {
			return mid;
		}
	}
	return 0;
}
int main() {
	init();
	for (int a : target) {
		cout << find_target_index(a) << " ";	
	}
}