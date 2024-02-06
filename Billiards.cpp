#include <string>
#include <vector>
#include <iostream>
#include <cmath>
//당구문제
//https://school.programmers.co.kr/learn/courses/30/lessons/169198
using namespace std;

int min(int a, int b) {
    return a > b ? b : a;
}

vector<int> solution(int m, int n, int startX, int startY, vector<vector<int>> balls) {
    vector<int> answer;
    int a = startX;
    int b = startY;
    float d[2] = { (float)n / m, -(float)n / m };

    for (int i = 0; i < balls.size(); i++) {
        int res = 999999999;
        int ca = balls[i][0];
        int cb = balls[i][1];

        // cout << d[1] << '\n';

         //(0,0)
        if (cb == ca && b == a) {
            if (a < ca) {
                int dist = pow(cb + b, 2) + pow(ca + a, 2);
                res = min(dist, res);
            }
        }

        //(m,0)
        if (a > ca && (float)b / a - m == (float)cb / ca - m) {
            int dist = pow(cb + b, 2) + pow(2 * m - a - ca, 2);
            res = min(dist, res);
        }

        //(0,n)
        if (b > cb && (float)(b - n) / a == (float)(cb - n) / ca) {
            int dist = pow(2 * n - b - cb, 2) + pow(ca + a, 2);
            res = min(dist, res);
        }

        //(m,n)
        if (b > cb && (float)(b - n) / (a - m) == (float)(cb - n) / (ca - m)) {
            int dist = pow(2 * n - b - cb, 2) + pow(2 * m - a - ca, 2);
            res = min(dist, res);
        }
        //y = 0
        if ((a == ca && b < cb) || a != ca) {
            int dist = pow(cb + b, 2) + pow(ca - a, 2);
            res = min(dist, res);
        }
        //y = n
        if ((a == ca && b > cb) || a != ca) {
            int dist = pow(2 * n - b - cb, 2) + pow(ca - a, 2);
            res = min(dist, res);
        }
        //x = 0
        if ((b == cb && a < ca) || b != cb) {
            int dist = pow(cb - b, 2) + pow(ca + a, 2);
            res = min(dist, res);
        }
        //x = m
        if ((b == cb && a > ca) || b != cb) {
            int dist = pow(cb - b, 2) + pow(2 * m - a - ca, 2);
            res = min(dist, res);
        }

        answer.push_back(res);

    }
    return answer;
}