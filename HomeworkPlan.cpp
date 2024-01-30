#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
#include <map>
#include <sstream>

//문제 설명
//과제를 받은 루는 다음과 같은 순서대로 과제를 하려고 계획을 세웠습니다.
//
//과제는 시작하기로 한 시각이 되면 시작합니다.
//새로운 과제를 시작할 시각이 되었을 때, 기존에 진행 중이던 과제가 있다면 진행 중이던 과제를 멈추고 새로운 과제를 시작합니다.
//진행중이던 과제를 끝냈을 때, 잠시 멈춘 과제가 있다면, 멈춰둔 과제를 이어서 진행합니다.
//만약, 과제를 끝낸 시각에 새로 시작해야 되는 과제와 잠시 멈춰둔 과제가 모두 있다면, 새로 시작해야 하는 과제부터 진행합니다.
//멈춰둔 과제가 여러 개일 경우, 가장 최근에 멈춘 과제부터 시작합니다.
//과제 계획을 담은 이차원 문자열 배열 plans가 매개변수로 주어질 때, 과제를 끝낸 순서대로 이름을 배열에 담아 return 하는 solution 함수를 완성해주세요.

//아이디어
//정렬과 스택을 이용
using namespace std;
int convertTimeStringToMinutes(const string timeString);
stack<vector<string>> hwStack;
map<string, int> hwMap;
//정렬할때 시간기준으로 정렬하는 함수
bool cmp(const vector<string>& v1, const vector<string>& v2) {
    return convertTimeStringToMinutes(v1[1]) < convertTimeStringToMinutes(v2[1]);
}
//텍스트로 된 시간을 int형으로 만들어줌
int convertTimeStringToMinutes(const string timeString) {
    int hours, minutes;
    char delimiter;

    istringstream ss(timeString);
    ss >> hours >> std::noskipws >> delimiter >> minutes;

    return hours * 60 + minutes;
}

vector<string> solution(vector<vector<string>> plans) {
    vector<string> answer;
    int nextElement = 1;
    sort(plans.begin(), plans.end(), cmp);
    hwStack.push(plans[0]);
    hwMap[plans[0][0]] = stoi(plans[0][2]);
    int currentTime = convertTimeStringToMinutes(plans[0][1]);
    //메인 로직 
    while (!hwStack.empty()) {
        vector<string> current = hwStack.top();
        for (int i = 0; i <= hwMap[current[0]]; i++) {
            //현재 계획을 다 돌렸을 때
            if (hwMap[current[0]] == 0) {
                answer.push_back(hwStack.top()[0]);
                hwMap.erase(hwStack.top()[0]);
                hwStack.pop();
                if (nextElement < plans.size() && hwStack.empty()) {
                    hwStack.push(plans[nextElement]);
                    hwMap[plans[nextElement][0]] = stoi(plans[nextElement][2]);
                    currentTime = convertTimeStringToMinutes(plans[nextElement][1]);
                    nextElement++;
                    break;
                }
                break;
            }
            //계획을 다 돌리지 않았는데 다음 계획이 찾아올때
            else if (nextElement < plans.size() && currentTime == convertTimeStringToMinutes(plans[nextElement][1])) {
                hwStack.push(plans[nextElement]);
                hwMap[plans[nextElement][0]] = stoi(plans[nextElement][2]);
                nextElement++;
                break;
            }
            hwMap[current[0]]--;
            currentTime++;
        }
    }
    return answer;
}

int main() {
    vector<string> result = solution({ {"science", "12:40", "50"}, {"music", "12:20", "40"}, {"history", "14:00", "30"}, {"computer", "12:30", "100"} });
    // 출력
    cout << "Result: [";
    for (size_t i = 0; i < result.size(); ++i) {
        cout << "\"" << result[i] << "\"";
        if (i < result.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;
    return 0;
}
