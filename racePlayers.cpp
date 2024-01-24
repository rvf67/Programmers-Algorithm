#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

vector<string> solution(vector<string> players, vector<string> callings) {
    // 선수들의 이름과 등수를 매핑하는 해시 맵
    unordered_map<string, int> playerRank;

    // 선수들의 이름을 등수로 매핑
    for (int i = 0; i < players.size(); i++) {
        playerRank[players[i]] = i + 1;
    }

    // 해설진의 호출에 따라 등수 조정
    for (const string& calling : callings) {
        int callingRank = playerRank[calling];

        // 호출된 선수가 1등이 아니면 등수 조정
        if (callingRank > 1) {
            swap(players[callingRank - 1], players[callingRank - 2]);
            playerRank[calling] = callingRank - 1;
            playerRank[players[callingRank - 1]] = callingRank;
        }
    }

    return players;
}

int main() {
    vector<string> result = solution({ "mumu", "soe", "poe", "kai", "mine" }, { "kai", "kai", "mine", "mine" });

    // 결과 출력
    for (const string& player : result) {
        cout << player << " ";
    }

    return 0;
}