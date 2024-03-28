#include <algorithm>
#include <deque>
#include <stdio.h>
#include <string.h>
#include <vector>

using namespace std;
int N, M, K;

vector<int> tree_map[10][10]; // 나무 맵
vector<int> died_map[10][10]; // 죽은 나무 맵
int food[10][10];             // 양분 맵
int A[10][10];

void init() {
  memset(tree_map, 0, sizeof(tree_map));
  memset(died_map, 0, sizeof(died_map));
  memset(food, 0, sizeof(food));
  memset(A, 0, sizeof(A));

  if(scanf("%d %d %d", &N, &M, &K)){};
  for (int i = 0; i < N; i++) {   // S2D2의 양분 추가
    for (int j = 0; j < N; j++) { // S2D2의 양분 추가
      if(scanf(" %d", &A[i][j])){};
    }
  }
  for (int i = 0; i < M;
       i++) { // 나무 심기(입력으로 주어지는 나무의 위치는 모두 서로 다름)
    int x, y, z;
    if(scanf(" %d %d %d", &x, &y, &z)){};
    tree_map[x - 1][y - 1].push_back(z);
  }
  for (int i = 0; i < N; i++) { // 처음의 양분은 5
    for (int j = 0; j < N; j++) {
      food[i][j] = 5;
    }
  }
}
void spring() {
  // 나무가 자신의 나이 만큼 양분을 먹고 나이 1 증가. 어린나무부터 양분먹고
  // 양분이 부족하면 바로 사망.
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      int index = -1;
      int number_of_tree = tree_map[i][j].size();
      for (int k = 0; k < number_of_tree; k++) {
        if (food[i][j] >= tree_map[i][j][k]) { // 양분 먹고 나이 1 증가
          food[i][j] -= tree_map[i][j][k];     // 양분먹고
          tree_map[i][j][k]++;                 // 나이 1 증가
        } else {
          index = k; // 해당 인덱스 이상의 값들을 죽은 나무의 벡터로 이동해야함.
          break;
        }
      }
      if (index != -1) {
        int time_of_pop = number_of_tree - index; // pop을 해줘야 하는 횟수
        for (int k = index; k < number_of_tree; k++) { // 죽은 나무 목록에 추가
          died_map[i][j].push_back(tree_map[i][j][k]);
        }
        while (time_of_pop--) { // 현재 생존 나무목록에서 제외
          tree_map[i][j].pop_back();
        }
      }
    }
  }
}
void summer() {
  // 죽은 나무 나이 / 2 양분으로 추가
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      int number_of_died = died_map[i][j].size();
      for (int k = 0; k < number_of_died; k++) {
        food[i][j] += died_map[i][j][k] / 2;
      }
      died_map[i][j] = vector<int>();
    }
  }
}
void tree_make(int y, int x, int cnt) {
  const int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};
  const int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
  for (int i = 0; i < 8; i++) {
    int ny = y + dy[i];
    int nx = x + dx[i];
    if (ny >= N || nx >= N || ny < 0 || nx < 0)
      continue;
    for (int j = 0; j < cnt; j++) {
      if (tree_map[ny][nx].empty()) {
        tree_map[ny][nx].push_back(1);
      } else {
        tree_map[ny][nx].insert(tree_map[ny][nx].begin(), 1);
      }
    }
  }
}
void fall() {
  // 나무 나이가 5의 배수일경우 인접한 8개의 칸에 나이 1인 나무 생성
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      int number_of_tree = tree_map[i][j].size();
      int cnt = 0;
      for (int k = 0; k < number_of_tree; k++) {
        if (tree_map[i][j][k] % 5 == 0 && tree_map[i][j][k] > 0) {
          cnt++;
          // tree_make(i, j); // 맨앞에 나이 1인 나무 생성
        }
      }
      if (cnt > 0)
        tree_make(i, j, cnt); // 맨앞에 나이 1인 나무 생성
    }
  }
}
void winter() {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      food[i][j] += A[i][j];
    }
  }
}
int find_tree() {
  int cnt = 0;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cnt += tree_map[i][j].size();
    }
  }
  return cnt;
}
int main() {
  init();
  while (K--) {
    spring();
    summer();
    fall();
    winter();
  }
  int result = find_tree();
  printf("%d\n", result);
}