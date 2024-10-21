#include<iostream>
using namespace std;
int N, M;
int d[11][11];
void init(){
    cin >> N >> M;
}
int make_d(int i,int j){
   if(i< 0 || j < 0) return 0;
   if(i < j) return 0;
   if(d[i][j] == 0){
       d[i][j] = make_d(i-1,j) + make_d(i-1,j-1);
   }
   return d[i][j];
}
int main(){
    init();
    d[0][0] = 1;
    cout << make_d(N, M);
    
    
    
}