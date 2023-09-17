#include <stdio.h>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

struct info {
	int start;
	int end;
};

bool cmp(const info & a, const info &b) {
	if (a.start < b.start) {
		return true;
	}
	else if (a.start == b.end) {
		if (a.end < b.end) {
			return true;
		}
	}
	return false;
}

int main() {
	int n;
	scanf("%d", &n);
	
	vector<info> v;
	priority_queue<int, vector<int>, greater<int>> endtime;

	for (int i = 0; i < n; i++) {
		info tmp;
		scanf("%d %d", &tmp.start, &tmp.end);
		v.push_back(tmp);
	}
	// 기본적으로 첫번째 원소 기준 정렬임.
	sort(v.begin(), v.end(), cmp);
	
	for (int i = 0; i < v.size(); i++) {
		endtime.push(v[i].end);
		if (endtime.top() <= v[i].start) endtime.pop();
	}

	printf("%d", endtime.size());


}