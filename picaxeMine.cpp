#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

bool compare(vector<int> a, vector<int> b);
bool compare2(vector<int> a, vector<int> b);
int solution(vector<int> picks, vector<string> minerals);

int solution(vector<int> picks, vector<string> minerals) {
    int picksSum = picks[0] + picks[1] + picks[2];

    if (picksSum * 5 < minerals.size()) {
        minerals.resize(minerals.size() - (minerals.size() - picksSum * 5));
    }

    int answer = 0;
    int groupId = 0;
    bool breakTime = true;
    vector<vector<int>> cost((minerals.size() / 5) + 1, vector<int>(3));

    while (breakTime) {
        for (int i = 0 + (groupId * 5); i < 5 + (groupId * 5); i++) {
            if (i == minerals.size()) {
                breakTime = false;
                break;
            }
            if (minerals[i] == "diamond") {
                cost[groupId][0] += 1;
                cost[groupId][1] += 5;
                cost[groupId][2] += 25;
            }
            else if (minerals[i] == "iron") {
                cost[groupId][0] += 1;
                cost[groupId][1] += 1;
                cost[groupId][2] += 5;
            }
            else {
                cost[groupId][0] += 1;
                cost[groupId][1] += 1;
                cost[groupId][2] += 1;
            }
        }
        groupId += 1;
    }

    sort(cost.begin(), cost.end(), compare);

    for (int i = 0; i < cost.size(); i++) {
        if (picks[0] > 0) {
            picks[0] -= 1;
            answer += cost[i][0];
        }
        else if (picks[1] > 0) {
            picks[1] -= 1;
            answer += cost[i][1];
        }
        else if (picks[2] > 0) {
            picks[2] -= 1;
            answer += cost[i][2];
        }
        else {
            return answer;
        }
    }

    return answer;
}

bool compare(vector<int> a, vector<int> b) {
    return a[2] > b[2];
};

int main()
{
    cout<<solution({ 0, 0, 1 }, { "stone", "stone", "stone", "stone", "stone", "diamond"});
}

