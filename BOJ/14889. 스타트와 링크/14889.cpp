#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// [BOJ] 14889. 스타트와 링크 / 실버 2 / 50분

int ret = 1000, n;

int main() {
	cin >> n;
	vector<vector<int>>stat;
	for (int i = 0; i < n; i++) {
		vector<int>tmp;
		for (int j = 0; j < n; j++) {
			int t; cin >> t; tmp.push_back(t);
		}
		stat.push_back(tmp);
	}
	//한가지 팀 고르는 경우 n C n/2의 배열
	vector<int>c(n, 0);
	for (int i = 0; i < n / 2; i++) {
		c[i] = 1;
	}

	do {
		vector<int>t1; vector<int>t2;
		for (int i = 0; i < n; i++) {
			if (c[i] == 1) {
				t1.push_back(i);
			}
			else {
				t2.push_back(i);
			}
		}

		//한 팀안에서 2선수 뽑는 경우 n/2 C 2 의 배열
		vector<int>cc(n/2, 0);
		cc[0] = 1; cc[1] = 1;
		int team1 = 0, team2 = 0;
		do {
			int i1 = -1, i2 = -1;
			for (int i = 0; i < n/2; i++) {
				if (cc[i] == 1) {
					if (i1 == -1)
						i1 = i;
					else
						i2 = i;
				}

			}
			team1 += stat[t1[i1]][t1[i2]] + stat[t1[i2]][t1[i1]];
			team2 += stat[t2[i1]][t2[i2]] + stat[t2[i2]][t2[i1]];

		} while (prev_permutation(cc.begin(), cc.end()));
		//prev_permuatation은 내림차순을 오름차순으로 출력
		//next_permuatation은 오름차순을 내림차순으로 출력
		//이거 햇갈림


		int diff = team1 - team2;
		if (diff < 0)
			diff *= -1;

		ret = min(ret, diff);

	} while (prev_permutation(c.begin(), c.end()));
	cout << ret;
}