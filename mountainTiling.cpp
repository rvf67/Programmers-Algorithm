#include <string>
#include <vector>
#include <iostream>

//문제: 프로그래머스 카카오 겨울 인턴십 산모양 타일링 문제
//https://school.programmers.co.kr/learn/courses/30/lessons/258705

//계획
//각 n개의 삼각형을 기준으로 가능한 경우의 수가 4가지가 나옴 
// 그리고 삼각형마다 겹쳐지는 삼각형이 하나씩은 나옴
//이를 분리하기 위해 각 삼각형의 왼쪽과중앙(+위)만 쓸때와 오른쪽의 경우의 수를 따로 분리하여
//경우의 수를 누적하여 모두 더하는 식으로 함
//추가:tops의 위쪽 삼각형이 있는 경우와 없는 경우도 판단할것
//결과는 10007로 나눈 나머지

using namespace std;
int solution(int n, vector<int> tops);
int main()
{
    cout<<solution(4, { 1,1,0,1 });
    return 0;
}

int solution(int n, vector<int> tops) {
    int answer = 1;
    vector<int> leftAndMid(n, 0);
    vector<int> right(n, 0);
    //가장 처음 삼각형의 경우의수
    right[0] = 1;
    leftAndMid[0] = tops[0] == 1 ? 3 : 2;
    for (int i = 1; i < tops.size(); i++) {
        if (tops[i]) {
            leftAndMid[i] = (3 * leftAndMid[i - 1] + 2 * right[i - 1]) % 10007;
        }
        else {
            leftAndMid[i] = (2 * leftAndMid[i - 1] + right[i - 1]) % 10007;
        }
        right[i] = (leftAndMid[i - 1] + right[i - 1]) % 10007;
    }
    answer = (leftAndMid[tops.size() - 1] + right[tops.size() - 1]) % 10007;
    return answer;
}