#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// [BOJ] 14501. 퇴사 / 실버 3 / 40분
vector<int>dp; vector<int>t; vector<int>p; int n;

int main() {
	cin >> n;	
	for (int i = 0; i < n; i++) {
		int tt, pp; cin >> tt >> pp;
		t.push_back(tt); p.push_back(pp);
	}
	dp.assign(n, 0);
	int ret = 0;
	for (int i = n - 1; i >= 0; i--) {
		//상담 가능한놈인지 확인
		if (t[i] + i <= n) {
			//현재 위치 뽑는다고 가정
			//본인 뒤에 있는놈들중에 안겹치는 가장 큰놈 가져오기
			int m = 0;
			for (int j = i+ t[i]; j < n; j++) {
				m = max(m, dp[j]);
			}
			dp[i] = p[i] + m;
			ret = max(ret, dp[i]);
		}
	}
	cout << ret;
}