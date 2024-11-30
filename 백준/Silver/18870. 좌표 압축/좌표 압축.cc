#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N;
	cin >> N;

	vector<int> arr(N);  // 원본 배열
	vector<int> sorted(N);  // 정렬될 배열

	// 입력
	for (int i = 0; i < N; i++) {
		cin >> arr[i];
		sorted[i] = arr[i];
	}

	// 정렬 및 중복 제거
	sort(sorted.begin(), sorted.end());
	sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());

	// 각 원소마다 lower_bound로 위치 찾기
	for (int i = 0; i < N; i++) {
		cout << lower_bound(sorted.begin(), sorted.end(), arr[i]) - sorted.begin() << ' ';
	}

	return 0;
}