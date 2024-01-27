#include <string>
#include <vector>
#include <queue>
#define MAX 100000

//https://school.programmers.co.kr/learn/courses/30/lessons/250134 
//문제설명


//아이디어
//기본적으로 탐색개수가 적으므로 dfs완전탐색과 재귀를 이용함
//일단 동시에 움직여야하므로 턴을 이용한 번갈아 이동하는 방법은 삼가함

using namespace std;

int dx[] = { -1,1,0,0 };
int dy[] = { 0,0,-1,1 };
//코어가 덤프되어 메모리를 아끼기 위해 따로 나누지 않고 합침
bool visited[4][4][2] = {false};
bool redEnd, blueEnd;
int map[4][4] = { 0 };
int width, height;

struct Point {
    int x, y;
};

// 해당 방향으로 움직임 반환
Point getNext(int x, int y, int dir) {
    int nx = x + dx[dir];
    int ny = y + dy[dir];
    return { nx,ny };
}

bool isPossible(Point cntRed, Point red,
    Point cntBlue, Point blue) {
    // 기본 탐색 규칙
    if (red.x < 0 || red.y < 0 || red.x >= height || red.y >= width
        || blue.x < 0 || blue.y < 0 || blue.x >= height || blue.y >= width
        || map[red.x][red.y] == 5 || map[blue.x][blue.y] == 5) return false;

    // 두 수레 스위치 체크
    if ((cntRed.x == blue.x && cntRed.y == blue.y)
        && (cntBlue.x == red.x && cntBlue.y == red.y)) return false;

    // 도착지점에 도착하지도 않고 중복방문이라면 false
    if ((!redEnd && visited[red.x][red.y][0])
        || (!blueEnd && visited[blue.x][blue.y][1])) return false;

    // 두 수레가 동일한 지점에 위치시 
    if (red.x == blue.x && red.y == blue.y) return false;
    return true;
}

// 백트래킹
int backtracking(Point red, Point blue, int result) {
    // 두 수레가 모두 도착 시 result 반환
    if (redEnd && blueEnd) return result;
    int answer = MAX;

    // 2중 for문으로 16가지 경우의 수
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            // 도착지점에 도착한 경우엔 움직이지 않음
            Point nRed = (!redEnd) ? getNext(red.x, red.y, i) : red;
            Point nBlue = (!blueEnd) ? getNext(blue.x, blue.y, j) : blue;

            // 불가능한 경우 conitnue
            if (!isPossible(red, nRed, blue, nBlue)) continue;
            visited[nRed.x][nRed.y][0] = true;
            visited[nBlue.x][nBlue.y][1] = true;
            if (map[nRed.x][nRed.y] == 3) redEnd = true;
            if (map[nBlue.x][nBlue.y] == 4) blueEnd = true;

            // 가장 적게 걸리는 턴 수
            answer = min(answer, backtracking(nRed, nBlue, result + 1));

            // 방문 기록 및 도착 기록 초기화
            redEnd = false;
            blueEnd = false;
            visited[nRed.x][nRed.y][0] = false;
            visited[nBlue.x][nBlue.y][1] = false;
        }
    }
    return answer;
}

int solution(vector<vector<int>> maze) {
    Point cntRed, cntBlue;
    height = maze.size();
    width = maze[0].size();
    for (int i = 0; i < maze.size(); i++) {
        for (int j = 0; j < maze[i].size(); j++) {
            map[i][j] = maze[i][j];

            // 각 수레의 시작위치 초기화
            if (maze[i][j] == 1) cntRed = { i,j };
            else if (maze[i][j] == 2) cntBlue = { i,j };
        }
    }
    // 시작 위치 방문 처리
    visited[cntRed.x][cntRed.y][0] = true;
    visited[cntBlue.x][cntBlue.y][1] = true;

    int answer = backtracking(cntRed, cntBlue, 0);
    return (answer == MAX) ? 0 : answer;
}