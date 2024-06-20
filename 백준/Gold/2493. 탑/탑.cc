#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int num;
int height[500000];
vector<int> result;

void init() {
    scanf("%d", &num);
    for (int i = 0; i < num; i++) {
        scanf("%d", &height[i]);
    }
}

int main() {
    init();
    stack<int> s; // 인덱스를 저장하는 스택

    for (int nowi = 0; nowi < num; nowi++) {
        while (!s.empty() && height[s.top()] <= height[nowi]) {
            s.pop();
        }
        if (s.empty()) {
            result.push_back(0);
        } else {
            result.push_back(s.top() + 1);
        }
        s.push(nowi);
    }

    for (int i = 0; i < num; i++) {
        printf("%d ", result[i]);
    }

    return 0;
}