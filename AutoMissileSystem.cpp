#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

//문제 설명
//A 나라가 B 나라를 침공하였습니다.
//B 나라의 대부분의 전략 자원은 아이기스 군사 기지에 집중되어 있기 때문에 A 나라는 B 나라의 아이기스 군사 기지에 융단폭격을 가했습니다.
//A 나라의 공격에 대항하여 아이기스 군사 기지에서는 무수히 쏟아지는 폭격 미사일들을 요격하려고 합니다.
//이곳에는 백발백중을 자랑하는 요격 시스템이 있지만 운용 비용이 상당하기 때문에 미사일을 최소로 사용해서 모든 폭격 미사일을 요격하려 합니다.
//A 나라와 B 나라가 싸우고 있는 이 세계는 2 차원 공간으로 이루어져 있습니다.
//A 나라가 발사한 폭격 미사일은 x 축에 평행한 직선 형태의 모양이며 개구간을 나타내는 정수 쌍(s, e) 형태로 표현됩니다.
//B 나라는 특정 x 좌표에서 y 축에 수평이 되도록 미사일을 발사하며, 발사된 미사일은 해당 x 좌표에 걸쳐있는 모든 폭격 미사일을 관통하여 한 번에 요격할 수 있습니다.
//단, 개구간(s, e)로 표현되는 폭격 미사일은 s와 e에서 발사하는 요격 미사일로는 요격할 수 없습니다.요격 미사일은 실수인 x 좌표에서도 발사할 수 있습니다.
//각 폭격 미사일의 x 좌표 범위 목록 targets이 매개변수로 주어질 때,
//모든 폭격 미사일을 요격하기 위해 필요한 요격 미사일 수의 최솟값을 return 하도록 solution 함수를 완성해 주세요.

using namespace std;
int solution(vector<vector<int>>& targets);
bool check(double x_start, double x_end, double y_start, double y_end);
int main() {
    vector<vector<int>> targets = { {4, 5}, {4, 8}, {10, 14}, {11, 13}, {5, 12}, {3, 7}, {1, 4} };
    int result = solution(targets);
    cout << "Total missiles needed: " << result << endl;
    return 0;
}

int solution(vector<vector<int>>& targets) {
    sort(targets.begin(), targets.end());
    vector<bool> destroy(targets.size(), false);
    vector<vector<int>> availableRange;
    int tot_missile = 0;
    for (int i = 0; i < targets.size(); i++) {
        if (!destroy[i]) {
            //이전에 부쉈던 미사일의 허용범위 중에 미사일 허용범위 안에 타겟이 있는지 확인
            int j = 0;
            for (auto& missile : availableRange) {
                if (check(missile[0], missile[1], targets[i][0], targets[i][1])) {
                    //있다면 부수고 허용범위를 업데이트함
                    destroy[i] = true;
                    availableRange[j][0] = max(missile[0], targets[i][0]);
                    availableRange[j][1] = min(missile[1], targets[i][1]);
                    break;
                }
                j++;
            }
            //없다면 부수고 새로운 허용범위를 추가하고 총 미사일 수를 하나 늘림
            if (!destroy[i]) {
                destroy[i] = true;
                availableRange.push_back({ targets[i][0], targets[i][1] });
                tot_missile++;
            }
        }
    }
    return tot_missile;
}

bool check(double x_start, double x_end, double y_start, double y_end)
{
    if (x_start <= y_start && y_start < x_end)
        return true;

    if (x_start < y_end && y_end <= x_end)
        return true;

    return false;
}