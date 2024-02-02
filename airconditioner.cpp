#include <vector>
#include <algorithm>
using namespace std;

int solution(int temperature, int t1, int t2, int a, int b, vector<int> onboard) {
    const int k = 1000 * 100;
    t1 += 10;
    t2 += 10;
    temperature += 10;

    // DP[i][j]: i분에 j 온도를 만들 수 있는 가장 적은 전력
    vector<vector<int>> DP(onboard.size(), vector<int>(51, k)); // j = 0: -10, j = 50: 40
    DP[0][temperature] = 0;

    int flag = 1; // 에어컨을 가동했을 때 온도가 변하는 방향
    if (temperature > t2) {
        flag = -1;
    }

    for (int i = 1; i < onboard.size(); ++i) {
        for (int j = 0; j < 51; ++j) {
            vector<int> arr;
            if ((onboard[i] == 1 && t1 <= j && j <= t2) || onboard[i] == 0) {
                // 1. 에어컨을 키지 않고 실외온도와 달라서 실내온도가 -flag 되는 경우
                if (0 <= j + flag && j + flag <= 50) {
                    arr.push_back(DP[i - 1][j + flag]);
                }
                // 2. 에어컨을 키지 않고 현재온도 j 가 실외온도랑 같아서 변하지 않는 경우
                if (j == temperature) {
                    arr.push_back(DP[i - 1][j]);
                }
                // 3. 에어컨을 키고 현재온도가 변하는 경우
                if (0 <= j - flag && j - flag <= 50) {
                    arr.push_back(DP[i - 1][j - flag] + a);
                }
                // 4. 에어컨을 키고 현재온도가 희망온도라서 온도가 변하지 않는 경우
                if (t1 <= j && j <= t2) {
                    arr.push_back(DP[i - 1][j] + b);
                }

                DP[i][j] = *min_element(arr.begin(), arr.end());
            }
        }
    }

    int answer = *min_element(DP[onboard.size() - 1].begin(), DP[onboard.size() - 1].end());
    return answer;
}
