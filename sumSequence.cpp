#include <iostream>
#include <string>
#include <vector>
#include<queue>
using namespace std;

vector<int> solution(vector<int> sequence, int k);
int main()
{
    vector<int> num1 = solution({ 2,2,2,2,2 }, 6);
   for (int num : num1) {
       cout << num;
   }
}
//큐를 이용해서 각 요소들을 넣고 
//큐안의 값이 k보다 커지면 pop하여 k보다 작거나 같을때까지 pop함
//큐안의 값의 합이 k가 되면 해당 인덱스를 기록함

//큐 선언
queue<int> q;
queue<int> idx_q;
int max_num= 1000001;
int first, second = 1000001;
int sum = 0;
vector<int> reslut_num;
vector<int> solution(vector<int> sequence, int k) {
    vector<int> answer;

    for (int i = 0; i < sequence.size(); i++) {
        sum += sequence[i];
        q.push(sequence[i]);
        idx_q.push(i);
        //만약 큐안의 합이 k보다 커지면 큐에서 pop함
        if (sum > k) {
            while (sum > k) {
                sum -= q.front();
                q.pop();
                idx_q.pop();
            }
        }
        //큐 안의 합이 k이고 현재 리스트 크기가 최소를 갱신했을 때만 지정함
        if (sum == k && max_num > idx_q.size()) {
            max_num = idx_q.size();
            first = idx_q.front();
            second = idx_q.back();
            //cout << max_num << "\n";
            //cout << first << second << "\n";
        }
        
        if (max_num == 1) {
            return { idx_q.front(),idx_q.front() };
        }
    }
    return { first,second };
}