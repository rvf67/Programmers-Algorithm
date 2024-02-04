#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#define MAX 100

//리코셰로봇 최단시간문제
//아이디어
//bfs와 큐를 이용

using namespace std;
int height, weight;
int cnt = 0;
int answer = 2147000000;
pair<int, int> start;
pair<int, int> goal;
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };
bool visited[MAX][MAX];
void bfs(vector<string>& board) {
    queue<pair<pair<int, int>, int>> q;

    q.push({ {start.first, start.second}, 0 });
    visited[start.first][start.second] = true;

    while (!q.empty()) {
        int cx = q.front().first.first;
        int cy = q.front().first.second;
        int cnt = q.front().second;
        q.pop();

        if (cx == goal.first && cy == goal.second) {
            answer = min(answer, cnt);
        }

        for (int i = 0; i < 4; i++) {
            int nx = cx + dx[i];
            int ny = cy + dy[i];

            if ((nx < 0 || height <= nx || ny < 0 || weight <= ny) || board[nx][ny] == 'D') continue;

            while (true) {
                nx += dx[i];
                ny += dy[i];

                if ((nx < 0 || height <= nx || ny < 0 || weight <= ny) || board[nx][ny] == 'D') {
                    nx -= dx[i];
                    ny -= dy[i];
                    break;
                }
            }

            if (visited[nx][ny]) continue;

            q.push({ {nx, ny}, cnt + 1 });
            visited[nx][ny] = true;
        }
    }
}
int solution(vector<string> board) {
    height = board.size();
    weight = board[0].size();
    int findCnt = 0;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < weight; j++) {
            if (findCnt == 2) break;

            if (board[i][j] == 'R') {
                start = { i, j };
                findCnt++;
            }
            else if (board[i][j] == 'G') {
                goal = { i, j };
                findCnt++;
            }
        }
    }
    visited[start.first][start.second] = true;
    bfs(board);
    if (answer == 2147000000) return -1;
    return answer;
}
int main()
{
    std::cout << "Hello World!\n";
}
