#include<stdio.h>
#include<algorithm>
#include<vector>

using namespace std;
struct  info{
	int start;
	int end;
};

bool compare(info &first, info &second) {
	if (first.end < second.end) return true;
	else if (first.end == second.end) {
		if (first.start < second.start) return true;
	}
	return false;
}

int main()
{
	int tc;
	scanf("%d", &tc);
	vector<info> v;
	for (int i = 0; i < tc; i++) {
		info tmp;
		scanf("%d %d", &tmp.start, &tmp.end);
		getchar();
		v.push_back(tmp);
	}
	sort(v.begin(), v.end(), compare);

	int cnt = 0;
	info tmp = v.front(); v.erase(v.begin());
	int last_time = tmp.end;
	cnt++;
	while (!v.empty()) {
		info tmp = v.front(); v.erase(v.begin());
		if (tmp.start < last_time) continue;
		last_time = tmp.end;
		cnt++;
	}
	printf("%d\n", cnt);
}