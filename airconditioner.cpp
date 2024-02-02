#include <vector>
#include <algorithm>
using namespace std;

int solution(int temperature, int t1, int t2, int a, int b, vector<int> onboard) {
    const int k = 1000 * 100;
    t1 += 10;
    t2 += 10;
    temperature += 10;

    // DP[i][j]: i�п� j �µ��� ���� �� �ִ� ���� ���� ����
    vector<vector<int>> DP(onboard.size(), vector<int>(51, k)); // j = 0: -10, j = 50: 40
    DP[0][temperature] = 0;

    int flag = 1; // �������� �������� �� �µ��� ���ϴ� ����
    if (temperature > t2) {
        flag = -1;
    }

    for (int i = 1; i < onboard.size(); ++i) {
        for (int j = 0; j < 51; ++j) {
            vector<int> arr;
            if ((onboard[i] == 1 && t1 <= j && j <= t2) || onboard[i] == 0) {
                // 1. �������� Ű�� �ʰ� �ǿܿµ��� �޶� �ǳ��µ��� -flag �Ǵ� ���
                if (0 <= j + flag && j + flag <= 50) {
                    arr.push_back(DP[i - 1][j + flag]);
                }
                // 2. �������� Ű�� �ʰ� ����µ� j �� �ǿܿµ��� ���Ƽ� ������ �ʴ� ���
                if (j == temperature) {
                    arr.push_back(DP[i - 1][j]);
                }
                // 3. �������� Ű�� ����µ��� ���ϴ� ���
                if (0 <= j - flag && j - flag <= 50) {
                    arr.push_back(DP[i - 1][j - flag] + a);
                }
                // 4. �������� Ű�� ����µ��� ����µ��� �µ��� ������ �ʴ� ���
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
