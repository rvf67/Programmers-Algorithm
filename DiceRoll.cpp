#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
#include <map>


//문제설명
//A와 B가 n개의 주사위를 가지고 승부를 합니다.주사위의 6개 면에 각각 하나의 수가 쓰여 있으며,
//주사위를 던졌을 때 각 면이 나올 확률은 동일합니다.각 주사위는 1 ~n의 번호를 가지고 있으며, 주사위에 쓰인 수의 구성은 모두 다릅니다.
//A가 먼저 n / 2개의 주사위를 가져가면 B가 남은 n / 2개의 주사위를 가져갑니다.
// 각각 가져간 주사위를 모두 굴린 뒤, 나온 수들을 모두 합해 점수를 계산합니다.점수가 더 큰 쪽이 승리하며, 점수가 같다면 무승부입니다.
//A는 자신이 승리할 확률이 가장 높아지도록 주사위를 가져가려 합니다.

//아이디어
//순열과 이분탐색을 이용

using namespace std;

const int MAX = 100 * 600 + 1;

int N;
vector<int> A, B;
vector<int> Asums, Bsums;
map<pair<set<int>, set<int>>, bool> visited;

void init()
{
    A.clear();
    B.clear();
    Asums.clear();
    Bsums.clear();
}

void func(int idx, int total, bool isA, vector<int>& v, vector<vector<int>>& dice)
{
    if (idx == N / 2)
    {
        isA ? Asums.push_back(total) : Bsums.push_back(total);

        return;
    }

    for (int i = 0; i < 6; i++)
    {
        func(idx + 1, total + dice[v[idx]][i], isA, v, dice);
    }
}

vector<int> solution(vector<vector<int>> dice) {
    N = dice.size();
    vector<int> v(N);

    for (int i = 0; i < N; i++)
    {
        v[i] = i;
    }

    vector<int> answer(N / 2);
    int maxWin = 0;

    do
    {
        init();
        int win = 0;

        set<int> ASet, BSet;

        for (int i = 0; i < N / 2; i++)
        {
            A.push_back(v[i]);
            ASet.insert(v[i]);

            B.push_back(v[i + N / 2]);
            BSet.insert(v[i + N / 2]);
        }

        if (!visited.count({ ASet, BSet }))
        {
            func(0, 0, true, A, dice);
            func(0, 0, false, B, dice);

            sort(Bsums.begin(), Bsums.end());
            map<int, int> sum2winCnt;

            for (int Asum : Asums)
            {
                if (sum2winCnt.count(Asum))
                {
                    win += sum2winCnt[Asum];

                    continue;
                }

                int low = 0, high = Bsums.size();

                while (low + 1 < high)
                {
                    int mid = (low + high) / 2;

                    if (Asum > Bsums[mid])
                    {
                        low = mid;
                    }
                    else
                    {
                        high = mid;
                    }
                }

                sum2winCnt[Asum] = low;
                win += sum2winCnt[Asum];
            }

            if (win > maxWin)
            {
                for (int i = 0; i < A.size(); i++)
                {
                    answer[i] = A[i] + 1;
                }

                maxWin = win;
            }

            visited[{ASet, BSet}] = true;
        }
    } while (next_permutation(v.begin(), v.end()));

    return answer;
}