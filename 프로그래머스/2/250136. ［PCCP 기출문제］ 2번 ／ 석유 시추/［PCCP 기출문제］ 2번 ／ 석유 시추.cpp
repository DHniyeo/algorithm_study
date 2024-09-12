#include <string>
#include <vector>
#include <queue>

using namespace std;

int solution(vector<vector<int>> land) {
    int answer = 0;
    int R = land.size();
    int C = land[0].size();
    int dy[] = {-1,0,1,0};
    int dx[] = {0,1,0,-1};
    vector<vector<int>> visited(R, vector<int>(C,0));
    vector<vector<int>> ans(C);
    for(int i =0 ; i< R ;i++){
        for(int j = 0 ; j< C; j++){
            if(visited[i][j]) continue;
            if(land[i][j]==0) continue;
            vector<int> arr;
            visited[i][j] = 1;
            queue<pair<int,int>> q;
            q.push({i,j});
            arr.push_back(j);
            int oil_size = 1;
            while(!q.empty()){
                pair<int,int> now = q.front(); q.pop();
                for(int i = 0 ; i< 4; i++){
                    int ny = now.first + dy[i];
                    int nx = now.second + dx[i];
                    if(ny >= R || nx >= C || ny <0 || nx < 0) continue;
                    if(visited[ny][nx]) continue;
                    if(land[ny][nx] == 0) continue;
                    visited[ny][nx] =1;
                    oil_size++;
                    arr.push_back(nx);
                    q.push({ny,nx});
                }
            }
            vector<bool> visit(C,false);    
            for(auto x : arr){
                if(visit[x] == false){
                    visit[x] = true;
                    ans[x].push_back(oil_size); // x인덱스에 크기 추가
                }
            }
        }
    }
    // 맵 다만들어짐
    for(int i = 0; i< C; i++){
        int sum =0;
        for(auto n : ans[i]){
            sum += n;
        }
        answer = answer < sum ? sum : answer;
    }
    
    return answer;
}