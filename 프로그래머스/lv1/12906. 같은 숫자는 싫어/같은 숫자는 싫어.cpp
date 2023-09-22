#include <vector>
#include <iostream>

using namespace std;

vector<int> solution(vector<int> arr) 
{
    vector<int> answer;
    int j = 0;
    answer.push_back(arr[0]);
    for(int i = 1 ; i< arr.size(); i++){
        int tmp = arr[i];
        if(tmp == answer[j]){
            continue;
        }
        else
        {
            answer.push_back(tmp);
            j++;
        }
    }
    
    return answer;
}