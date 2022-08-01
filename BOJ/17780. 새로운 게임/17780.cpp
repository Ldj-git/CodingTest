#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>
using namespace std;

// [BOJ] 17780. 새로운 게임 / 골드 2 / 2시간 넘음

//문제를 꼼꼼히 읽읍시다... 말 4개 쌓이면 종료하는건데 한곳에 다모이면 끝나는줄
//뒤집는것도 잘못 구현함 옮기고 다뒤집는게 아니라 뒤집고 옮기기

struct m {
	int y, x, dir, up = -1, down = -1;
};

bool gameOver(vector<m>mal) {
	for (int i = 0; i < mal.size(); i++) {
		int nextmal = mal[i].up, tmp = 1;
		while (nextmal != -1) {
			nextmal = mal[nextmal].up;
			tmp++;
		}
		if (tmp >= 4) {
			return true;
		}
	}
	return false;

	/*int x = mal[0].x, y = mal[0].y;
	for (int i = 1; i < mal.size(); i++) {
		if (x != mal[i].x || y != mal[i].y) {
			return false;
		}
	}
	return true;*/
}

int main() {
	int n, k; cin >> n >> k;
	int ret = 1;

	vector<int>tmp(n, 0);
	vector<vector<int>>chess(n, tmp);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> chess[i][j]; //i가 y j가 x
		}
	}
	//우좌상하
	int dirx[4] = { 1,-1,0,0 };
	int diry[4] = { 0,0,-1,1 };

	vector<m>mal;
	for (int i = 0; i < k; i++) {
		int y, x, dir; cin >> y >> x >> dir;
		mal.push_back({ y - 1,x - 1,dir - 1 });
	}

	while (true) {
		//한턴 진행 1번말부터 하나씩 보기
		for (int i = 0; i < k; i++) {
			//가장 밑에있는 말만 움직임
			if (mal[i].down == -1) {
				int nextx = mal[i].x + dirx[mal[i].dir], nexty = mal[i].y + diry[mal[i].dir];
				//벗어나는 경우
				if (nextx < 0 || nextx >= n || nexty < 0 || nexty >= n) {
					//방향 뒤집기
					if (mal[i].dir % 2 == 0) {
						mal[i].dir += 1;
					}
					else {
						mal[i].dir -= 1;
					}

					//갈수 있으면 가기. 가려는 칸이 파랑이거나 벗어나면 가만히
					int nx = mal[i].x + dirx[mal[i].dir], ny = mal[i].y + diry[mal[i].dir];
					if (nx >= 0 && nx < n && ny >= 0 && ny < n) {
						if (chess[ny][nx] == 0 || chess[ny][nx] == 1) {
							//해당 위치에 이미 말이 있으면 업기
							int gizontop = -1;
							for (int j = 0; j < k; j++) {
								if (mal[j].x == nx && mal[j].y == ny && mal[j].up == -1) {
									gizontop = j; break;
								}
							}
							if (gizontop != -1) {
								mal[gizontop].up = i; mal[i].down = gizontop;
							}

							//움직인 가장 아래말 위치 업데이트
							mal[i].x = nx; mal[i].y = ny;

							//업힌 것들도 위치 업데이트
							int nextmal = mal[i].up;
							while (nextmal != -1) {
								mal[nextmal].x = nx; mal[nextmal].y = ny;
								nextmal = mal[nextmal].up;
							}
						}
					}
				}
				else {
					//파란색
					if (chess[nexty][nextx] == 2) {
						//방향 뒤집고
						if (mal[i].dir % 2 == 0) {
							mal[i].dir += 1;
						}
						else {
							mal[i].dir -= 1;
						}

						//갈수 있으면 가기. 가려는 칸이 파랑이거나 벗어나면 가만히
						int nx = mal[i].x + dirx[mal[i].dir], ny = mal[i].y + diry[mal[i].dir];
						if (nx >= 0 && nx < n && ny >= 0 && ny < n) {
							if (chess[ny][nx] == 0 || chess[ny][nx] == 1) {
								//해당 위치에 이미 말이 있으면 업기
								int gizontop = -1;
								for (int j = 0; j < k; j++) {
									if (mal[j].x == nx && mal[j].y == ny && mal[j].up == -1) {
										gizontop = j; break;
									}
								}
								if (gizontop != -1) {
									mal[gizontop].up = i; mal[i].down = gizontop;
								}

								//움직인 가장 아래말 위치 업데이트
								mal[i].x = nx; mal[i].y = ny;

								//업힌 것들도 위치 업데이트
								int nextmal = mal[i].up;
								while (nextmal != -1) {
									mal[nextmal].x = nx; mal[nextmal].y = ny;
									nextmal = mal[nextmal].up;
								}
							}
						}
					}
					//흰색
					if (chess[nexty][nextx] == 0) {
						//해당 위치에 이미 말이 있으면 업기
						int gizontop = -1;
						for (int j = 0; j < k; j++) {
							if (mal[j].x == nextx && mal[j].y == nexty && mal[j].up == -1) {
								gizontop = j; break;
							}
						}
						if (gizontop != -1) {
							mal[gizontop].up = i; mal[i].down = gizontop;
						}

						//움직인 가장 아래말 위치 업데이트
						mal[i].x = nextx; mal[i].y = nexty;

						//업힌 것들도 위치 업데이트
						int nextmal = mal[i].up;
						while (nextmal != -1) {
							mal[nextmal].x = nextx; mal[nextmal].y = nexty;
							nextmal = mal[nextmal].up;
						}
					}
					//빨간색
					if (chess[nexty][nextx] == 1) {
						//순서 뒤집기
						int nextmal = i, now = -1;
						while (nextmal != -1) {
							now = nextmal;
							nextmal = mal[now].up;
							int tmp = mal[now].down; mal[now].down = mal[now].up; mal[now].up = tmp;
						}

						//이동
						//해당 위치에 이미 말이 있으면 업기
						int gizontop = -1;
						for (int j = 0; j < k; j++) {
							if (mal[j].x == nextx && mal[j].y == nexty && mal[j].up == -1) {
								gizontop = j; break;
							}
						}
						if (gizontop != -1) {
							mal[gizontop].up = now; mal[now].down = gizontop;
						}

						//움직인 가장 아래말 위치 업데이트
						mal[now].x = nextx; mal[now].y = nexty;

						//업힌 것들도 위치 업데이트
						nextmal = mal[now].up;
						while (nextmal != -1) {
							mal[nextmal].x = nextx; mal[nextmal].y = nexty;
							nextmal = mal[nextmal].up;
						}
					}
				}
			}
			if (gameOver(mal)) {
				cout << ret;
				return 0;
			}
		}
		ret++;
		if (ret > 1000) {
			ret = -1;  break;
		}
	}
	cout << ret;
}