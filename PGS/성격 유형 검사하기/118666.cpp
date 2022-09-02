#include <string>
#include <vector>

// [PGS] 118666. 성격 유형 검사하기 / lv1 / 25분 
// 더 빨리 풀어야댐 너무 오래걸림
// 그냥 구현문제여서 뭐 따로 안씀

using namespace std;

string solution(vector<string> survey, vector<int> choices) {
    string answer = "";
    vector<string> mbti={"RT","CF","JM","AN"};
    vector<vector<int>>res={{0,0},{0,0},{0,0},{0,0}};
    
    for(int i=0;i<survey.size();i++){
        /*
        1 2 3 4 5 6 7
        3 2 1 0 1 2 3
        */
        char here=' ';
        int hereScore=0;
        
        if(choices[i]>=5){
            hereScore=choices[i]-4;
            here=survey[i][1];
        }else if(choices[i]<4){
            here=survey[i][0];
            if(choices[i]==1){
                hereScore=3;
            }else if(choices[i]==2){
                hereScore=2;
            }else{
                hereScore=1;
            }
        }
        
        for(int y=0;y<4;y++){
            for(int x=0;x<2;x++){
                if(here==mbti[y][x]){
                    res[y][x]+=hereScore;
                }
            }
        }
        
    }
    
    for(int i=0;i<4;i++){
        if(res[i][0]>=res[i][1]){
            answer+=mbti[i][0];
        }else{
            answer+=mbti[i][1];
        }
    }
    
    return answer;
}