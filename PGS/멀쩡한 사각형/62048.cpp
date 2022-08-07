#include <cmath>
#include <iostream>
// [PGS] 62048. 멀쩡한 사각형 / lv2 / 30분정도 해보고 계속 실패 떠서 답확인해봄

using namespace std;

long long gcd(long long a,long long b){
    if(a<b){
        long long tmp=b; b=a; a=tmp;
    }
    
    if(a%b==0)
        return b;
    else
        return gcd(b,a%b);
}

long long solution(int w,int h) {
    long long ww=(long long)w;
    long long hh=(long long)h;
    return ww*hh-(ww+hh-gcd(ww,hh));
    
    // long long answer = 0;
//     //직사각형은 왼쪽 아래를 기준으로 셈
//     float before=0, gradient=(float)h/w;
//     for(int i=1;i<=w;i++){
//         //i 일때 y축에 닿는 수
//         float now=before+gradient;
//         answer+=(long long) (ceil(now)-floor(before));
//         before=now;
//     }
    
//     return (long long)w*h-answer;
}