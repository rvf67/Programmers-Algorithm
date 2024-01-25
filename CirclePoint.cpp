#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

//문제 설명
//x축과 y축으로 이루어진 2차원 직교 좌표계에 중심이 원점인 서로 다른 크기의 원이 두 개 주어집니다.
//반지름을 나타내는 두 정수 r1, r2가 매개변수로 주어질 때,
//두 원 사이의 공간에 x좌표와 y좌표가 모두 정수인 점의 개수를 return하도록 solution 함수를 완성해주세요.
//※ 각 원 위의 점도 포함하여 셉니다.

long long solution(int r1, int r2) {
    //일단 x나 Y가 0일때를 기준으로 초기화함
    long long answer = 0;
    for (int i = 1; i <= r2; i++) {
        if (r1 >= i) {//조건을 벗어나면 long long minY = pow(r1, 2) - pow(i, 2);이 0보다 작아짐
            //큰원의 최대정수와 작은원의 최소 정수를 나눠서 계산
            long long minY = pow(r1, 2) - pow(i, 2);
            long long maxY = pow(r2, 2) - pow(i, 2);
            minY = ceil(sqrt(minY));
            maxY = floor(sqrt(maxY));
            answer = answer + maxY - minY + 1;
        }
        else {
            long long maxY = pow(r2, 2) - pow(i, 2);
            maxY = floor(sqrt(maxY));
            answer = answer + maxY + 1;
        }
    }
    //4개의 사분면이므로 *4를 함
    answer = 4 * answer;
    return answer;
}