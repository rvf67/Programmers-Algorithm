using System;
using System.Collections.Generic;
using System.ComponentModel;


//문제 설명
//당신은 1~n 사이의 수가 적힌 카드가 하나씩 있는 카드 뭉치와 동전 coin개를 이용한 게임을 하려고 합니다. 카드 뭉치에서 카드를 뽑는 순서가 정해져 있으며, 게임은 다음과 같이 진행합니다.

//처음에 카드 뭉치에서 카드 n/3장을 뽑아 모두 가집니다. (n은 6의 배수입니다.) 당신은 카드와 교환 가능한 동전 coin개를 가지고 있습니다.
//게임은 1라운드부터 시작되며, 각 라운드가 시작할 때 카드를 두 장 뽑습니다. 카드 뭉치에 남은 카드가 없다면 게임을 종료합니다. 뽑은 카드는 카드 한 장당 동전 하나를 소모해 가지거나, 동전을 소모하지 않고 버릴 수 있습니다.
//카드에 적힌 수의 합이 n+1이 되도록 카드 두 장을 내고 다음 라운드로 진행할 수 있습니다. 만약 카드 두 장을 낼 수 없다면 게임을 종료합니다.
//예를 들어 n = 12, coin = 4이고 [3, 6, 7, 2, 1, 10, 5, 9, 8, 12, 11, 4] 순서대로 카드를 뽑도록 카드 뭉치가 섞여 있습니다.

//처음에 3, 6, 7, 2 카드 4장(= n/3)과 동전 4개(= coin)를 가지고 시작합니다. 다음 라운드로 진행하기 위해 내야 할 카드 두 장에 적힌 수의 합은 13(= n+1)입니다. 다음과 같은 방법으로 최대 5라운드까지 도달할 수 있습니다.

//1라운드에서 뽑은 카드 1, 10을 동전 두 개를 소모해서 모두 가집니다. 카드 3, 10을 내고 다음 라운드로 진행합니다. 이때 손에 남은 카드는 1, 2, 6, 7이고 동전이 2개 남습니다.
//2라운드에서 뽑은 카드 5, 9를 동전을 소모하지 않고 모두 버립니다. 카드 6, 7을 내고 다음 라운드로 진행합니다. 이때 손에 남은 카드는 1, 2고 동전이 2개 남습니다.
//3라운드에서 뽑은 카드 8, 12 중 동전 한 개를 소모해서 카드 12를 가집니다. 카드 1, 12을 내고 다음 라운드로 진행합니다. 이때 손에 남은 카드는 2이고 동전이 1개 남습니다.
//4라운드에서 뽑은 카드 11, 4 중 동전 한 개를 소모해서 카드 11을 가집니다. 카드 2, 11을 내고 다음 라운드로 진행합니다. 이때 손에 남은 카드와 동전은 없습니다.
//5라운드에서 카드 뭉치에 남은 카드가 없으므로 게임을 종료합니다.
//처음에 가진 동전수를 나타내는 정수 coin과 카드를 뽑는 순서대로 카드에 적힌 수를 담은 1차원 정수 배열 cards가 매개변수로 주어질 때, 게임에서 도달 가능한 최대 라운드의 수를 return 하도록 solution 함수를 완성해 주세요.
public class Solution
{
    static void Main(string[] args)
    {
        Solution s = new Solution();
        Console.Write(s.solution(4, [3, 6, 7, 2, 1, 10, 5, 9, 8, 12, 11, 4]));
    }
    public int solution(int coin, int[] cards)
    {
        int answer = 1;
        int n = cards.Length;
        int max_turn = (n - n / 3) / 2+1; //최대턴수       
        List<int> deck = new List<int>(cards);//남은 덱 안의 카드 개수
        List<int> hands = new List<int>();        //손패 리스트
        List<int> keep_card = new List<int>();//드로우된 카드들을 임시저장할 리스트

        //카드 전체의 3분의1만큼 손패 채우기
        for (int i = 0; i < n / 3; i++)
        {
            hands.Add(deck[0]);
            deck.RemoveAt(0);
        }
        //현재 있는 손패로 자체적으로 2장을 썻을 때 n+1을 만들 수 있는 기회
        //n은 6의 배수이기 때문에 n+1은 무조건 홀수(짝이 무조건 있음)
        bool loop = true;
        while (loop)
        {
            foreach (var data in hands)
            {
                //짝이 존재하면 기회를 추가하고 최대턴수를 하나 증가시킴
                //기존의 짝들은 제거하여 반복을 줄임
                if (hands.Contains(n + 1 - data))
                {
                    answer++;
                    hands.RemoveAll(x => x == data || x == n + 1 - data);
                    for (int i = 0; i < 2; i++) //턴을 넘겨서 미리 드로우될 카드들을 저장카드뭉치에 담음
                    {
                        keep_card.Add(deck[0]);
                        deck.RemoveAt(0);
                    }
                    break;
                }
                if (data == hands.Last())
                {
                    loop=false;
                }
            }
        }
      
        while (answer<max_turn)
        {
            for (int i = 0;i < 2; i++) //드로우된 카드를 추가함
            {
                keep_card.Add(deck[0]);
                deck.RemoveAt(0);
            }
            foreach (var data in keep_card) //코인 사용 여부 및 전체적인 로직
            {
                if (hands.Contains(n + 1 - data) && coin > 0) //저장된 카드뭉치와 손패로 n+1을 만들 수 있는 숫자가 존재
                {
                    coin--;
                    hands.Remove(n + 1 - data);
                    keep_card.Remove(data);
                    answer++;
                    break;
                }else if(coin == 0)
                {
                    answer = Math.Min(max_turn, answer);
                    return answer;
                }
                if (data == keep_card.Last()) //손패와 저장 카드뭉치 조합으로 만들 수 없을 때
                {
                    foreach (var data2 in keep_card) //저장된 카드뭉치끼리의 조합으로 만들 수 있는지 찾음
                    {
                        if (keep_card.Contains(n + 1 - data2) && coin > 1) //저장 카드뭉치에서 n+1을 만들 수 있는 경우
                        {
                            coin -= 2;
                            keep_card.Remove(n + 1 - data2);
                            keep_card.Remove(data2);
                            answer++;
                            break;
                        }
                        else if (data2 == keep_card.Last() || coin < 2)
                        {
                            answer = Math.Min(max_turn, answer);
                            return answer;
                        }
                    }
                    break;
                }                                            
            }
        }
        return answer;
    }
}