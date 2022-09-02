#include <string>
#include <vector>
#include <queue>
// [PGS] 118667. 두 큐 합 같게 만들기 / lv2 / 1시간 고민하고 답확인

using namespace std;

// 그리디 문제인데 계속 감을 못잡았음

int solution(vector<int> queue1, vector<int> queue2) {
    long long s1=0,s2=0, m=-1;
    queue<int>q1;
    queue<int>q2;
    for(int i=0;i<queue1.size();i++){
        s1+=queue1[i]; s2+=queue2[i];
        q1.push(queue1[i]);
        q2.push(queue2[i]);
    }
    
    int answer = 0;
    //이 부분 최대 이동이 큐 사이즈의 3배까지는 일어날수 있음
    while(answer<=queue1.size()*3){
        if(s1==s2){
            return answer;
        }
        else if(s1>s2){
            s1-=q1.front(); s2+=q1.front();
            q2.push(q1.front()); q1.pop();
        }else{
            s2-=q2.front(); s1+=q2.front();
            q1.push(q2.front()); q2.pop();
        }
        answer++;
    }
    
    return -1;
}