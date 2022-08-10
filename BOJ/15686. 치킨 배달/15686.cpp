#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <climits>
#include <cstdlib>
using namespace std;

// [BOJ] 15686. 치킨 배달 / 골드 5 / 1시간 하고 시간초과남

int n, m;

//시간초과 나는게
//모든 경우를 bfs 해서 그런거 같음 도대체 왜 이렇게 짠거지 ㅋㅋㅋㅋㅋ
//그냥 좌표로 abs 계산만 하자


int cal(vector<pair<int,int>>chicken, vector<pair<int, int>>home, vector<int>c) {
	int ret = 0;

	for (int i = 0; i < home.size(); i++) {
		int now = INT_MAX;
		for (int j = 0; j < c.size(); j++) {
			if (c[j] == 1) {
				now = min(now, abs(home[i].first - chicken[j].first) + abs(home[i].second - chicken[j].second));
			}
		}
		ret += now;
	}

	//int dirx[4] = { 1,0,-1,0 }, diry[4] = { 0,1,0,-1 };
	//for (int i = 0; i < home.size(); i++) {
	//	queue<pair<int, int>>q;
	//	vector<bool>tmp(n, false);
	//	vector<vector<bool>>visited(n, tmp);
	//	q.push({ home[i].first,home[i].second });
	//	visited[home[i].first][home[i].second] = true;
	//	while (!q.empty()) {
	//		int herex = q.front().first, herey = q.front().second;
	//		q.pop();
	//		for (int j = 0; j < 4; j++) {
	//			int x = herex + dirx[j], y = herey + diry[j];
	//			if (x >= 0 && x < n && y >= 0 && y < n) {
	//				if (!visited[x][y]) {
	//					if (data[x][y] == 2) {
	//						ret += abs(home[i].first - x) + abs(home[i].second - y);
	//						q = queue<pair<int, int>>(); //큐 초기화
	//						break;
	//					}
	//					else {
	//						q.push({ x,y });
	//						visited[x][y] = true;
	//					}
	//				}
	//			}
	//		}
	//	}
	//}

	return ret;
}

int main() {
	cin >> n >> m;
	vector<vector<int>>data;
	vector<pair<int, int>>home;
	vector<pair<int, int>>chicken;
	for (int i = 0; i < n; i++) {
		vector<int>tmp;
		for (int j = 0; j < n; j++) {
			int t; cin >> t; tmp.push_back(t);
			if (t == 1) {
				home.push_back({ i,j });
			}
			if (t == 2) {
				chicken.push_back({ i,j });
			}
		}
		data.push_back(tmp);
	}

	vector<int>c(chicken.size(),0);
	for (int i = 0; i < m; i++) {
		c[c.size() - i - 1] = 1;
	}

	int ret = INT_MAX;
	do {
		//for (int i = 0; i < c.size(); i++) {
		//	if (c[i] == 0) { //잠시 없앨 치킨집
		//		data[chicken[i].first][chicken[i].second] = 0;
		//	}
		//}

		ret = min(ret, cal(chicken, home, c));

		//for (int i = 0; i < c.size(); i++) {
		//	if (c[i] == 0) { //치킨집 다시 추가
		//		data[chicken[i].first][chicken[i].second] = 2;
		//	}
		//}
	} while (next_permutation(c.begin(), c.end()));
	cout << ret;
}