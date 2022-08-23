#include <vector>
#include <iostream>
#include <algorithm>
#include <utility>
using namespace std;

// [BOJ] 16234. 인구이동 / 골드 5 / 대충 2시간 삽질하고 실패
/*
반례 
밑에처럼 하지 말고 bfs 쓰자...

input

3 10 30
0 0 0
50 30 0
20 0 40

답

2
*/

int getPar(vector<int>tmp, int here) {
	if (tmp[here] == here)
		return here;
	else
		return getPar(tmp, tmp[here]);
}

int diff(int a, int b) {
	if (a > b)
		return a - b;
	else
		return b - a;
}

int main() {
	int n, r, l, ret = 0; cin >> n >> l >> r;
	vector<vector<int>>input;

	//유니온파인드 느낌 누구랑 연합인지 확인용
	vector<int>nara; 
	for (int i = 0; i < n * n; i++) {
		nara.push_back(i);
	}	

	for (int i = 0; i < n; i++) {
		vector<int>tmp;
		for (int j = 0; j < n; j++) {
			int t; cin >> t; tmp.push_back(t);
		}
		input.push_back(tmp);
	}

	int dirx[4] = { 1,0,-1,0 };
	int diry[4] = { 0,-1,0,1 };

	bool moved;
	do{
		moved = false;
		vector<int>tmpNara = nara;

		//인구수합, 연합 몇개인지
		vector<pair<int, int>>info;
		for (int y = 0; y < n; y++) {
			for (int x = 0; x < n; x++) {
				info.push_back({ input[y][x],1 });
			}
		}

		//벽 부실지 세울지
		for (int y = 0; y < n; y++) {
			for (int x = 0; x < n; x++) {
				for (int k = 0; k < 4; k++) {
					int herex = x + dirx[k], herey = y + diry[k];
					if (herex >= 0 && herex < n && herey >= 0 && herey < n) {
						if (diff(input[herey][herex], input[y][x]) >= l && diff(input[herey][herex], input[y][x]) <= r) {
							moved = true;
							if (tmpNara[herex + herey * n] != tmpNara[x + y * n]) {
								tmpNara[herex + herey * n] = tmpNara[x + y * n];
								int hereNara = tmpNara[x + y * n];

								info[hereNara].second++;
								info[hereNara].first += input[herey][herex];
							}
						}
					}
				}
			}
		}

		if (moved) {
			for (int x = 0; x < n; x++) {
				for (int y = 0; y < n; y++) {
					cout << tmpNara[y + x * n] << " ";
				}
				cout << "\n";
			}
			cout << "\n";

			//인구 이동
			for (int y = 0; y < n; y++) {
				for (int x = 0; x < n; x++) {
					int hereNara = tmpNara[x + y * n];
					input[y][x] = info[hereNara].first / info[hereNara].second;
					cout << input[y][x]<<" ";
				}
				cout << "\n";
			}
			cout << "\n";
			ret++;
		}

	} while (moved);

	cout << ret;
}