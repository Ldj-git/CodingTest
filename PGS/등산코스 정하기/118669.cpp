#include <string>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

//[PGS] 118669. 등산코스 정하기 / lv3 / 고민하다 답보고 3시간정도 삽질하다 실패

//삽질 기록...
//그 예제 3번이 안되는데 생각을 처음부터 다시 해야할듯
//산봉오리가 1번만 포함되어야해서...

// 다익스트라 비슷하게 하는데 가중치 합으로 하는게 아니라 최대가중치를 파악할것

vector<int> solution(int n, vector<vector<int>> paths, vector<int> gates, vector<int> summits) {
    int minIntensity = 10000000, san = -1;
    //0번은 안씀
    vector<int>tmp(n + 1, 10000000);
    //정보 저장용 인접행렬방식으로
    vector<vector<int>>di(n + 1, tmp);

    for (int i = 0; i < paths.size(); i++) {
        int s = paths[i][0], d = paths[i][1], w = paths[i][2];
        di[s][d] = w; di[d][s] = w;
    }
    
    //이런식으로 모든 입구마다 다익하듯이 돌렸는데 시간초과 뜸...
    for (int i = 0; i < gates.size(); i++) {
        int start = gates[i];
        //start 에서 해당 위치까지 최소 intensity가 얼만지 저장용 
        vector<int> ret(n + 1, 10000000);

        //다익
        //pq는 최소비용이 큐 앞으로 오게
        //해당 위치까지 가는 최대 비용이 저장됨
        //기존 경로보다 작은 최대 비용이 있으면 업데이트 해줘야함
        priority_queue<pair<int, int>,vector<pair<int,int>>,greater<pair<int,int>>>pq; //오름차순이고 pair는 비용,위치 
        pq.push({ 0,start }); 
        while (!pq.empty()) {
            pair<int,int> here = pq.top(); pq.pop();
            //해당 비용이 기록된 비용보다 작으면 업데이트
            if (ret[here.second] > here.first) {
                ret[here.second] = here.first;
                //해당 위치에서 pq 추가
                for (int j = 1; j <= n; j++) {
                    int cost = max(di[here.second][j], ret[here.second]);
                    if (cost <= ret[j]) {
                        pq.push({ cost,j });
                    }
                }
            }
        }

        for (int j = 0; j < summits.size(); j++) {
            int here = summits[j];
            if (minIntensity > ret[here]) {
                san = here; minIntensity = ret[here];
            }
        }
    }

    return { san,minIntensity };
}

int main() {
    solution(7, {{1, 2, 5}, {1, 4, 1}, {2, 3, 1}, {2, 6, 7}, {4, 5, 1}, {5, 6, 1}, {6, 7, 1}} , {3, 7}, {1, 5});
}