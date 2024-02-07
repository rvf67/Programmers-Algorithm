#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
//https://school.programmers.co.kr/learn/courses/30/lessons/161990
//프로그래머스 바탕화면 정리문제

//아이디어
//단순 크기비교
vector<int> solution(vector<string> wallpaper) {
    vector<int> answer;
    int minX = 50;
    int minY = 50;
    int maxX = 0;
    int maxY = 0;
    for (int i = 0; i < wallpaper.size(); i++) {
        for (int j = 0; j < wallpaper[0].size(); j++) {
            if (wallpaper[i][j] == '#') {
                minX = min(minX, i);
                minY = min(minY, j);
                maxX = max(maxX, i+1);
                maxY = max(maxY, j+1);
            }
        }
    }
    answer = { minX,minY,maxX,maxY };
    return answer;
}


int main()
{
    std::cout << "Hello World!\n";
}
