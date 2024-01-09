﻿//문제 설명
//선물을 직접 전하기 힘들 때 카카오톡 선물하기 기능을 이용해 축하 선물을 보낼 수 있습니다. 
//당신의 친구들이 이번 달까지 선물을 주고받은 기록을 바탕으로 다음 달에 누가 선물을 많이 받을지 예측하려고 합니다.

//두 사람이 선물을 주고받은 기록이 있다면, 이번 달까지 두 사람 사이에 더 많은 선물을 준 사람이 다음 달에 선물을 하나 받습니다.
//예를 들어 A가 B에게 선물을 5번 줬고, B가 A에게 선물을 3번 줬다면 다음 달엔 A가 B에게 선물을 하나 받습니다.
//두 사람이 선물을 주고받은 기록이 하나도 없거나 주고받은 수가 같다면,
//선물 지수가 더 큰 사람이 선물 지수가 더 작은 사람에게 선물을 하나 받습니다.
//선물 지수는 이번 달까지 자신이 친구들에게 준 선물의 수에서 받은 선물의 수를 뺀 값입니다.
//예를 들어 A가 친구들에게 준 선물이 3개고 받은 선물이 10개라면 A의 선물 지수는 -7입니다. 
//B가 친구들에게 준 선물이 3개고 받은 선물이 2개라면 B의 선물 지수는 1입니다. 
//만약 A와 B가 선물을 주고받은 적이 없거나 정확히 같은 수로 선물을 주고받았다면, 다음 달엔 B가 A에게 선물을 하나 받습니다.
//만약 두 사람의 선물 지수도 같다면 다음 달에 선물을 주고받지 않습니다.
//위에서 설명한 규칙대로 다음 달에 선물을 주고받을 때, 당신은 선물을 가장 많이 받을 친구가 받을 선물의 수를 알고 싶습니다.

//친구들의 이름을 담은 1차원 문자열 배열 friends 이번 달까지 친구들이 주고받은 선물 기록을 담은 1차원 문자열 배열 gifts가 매개변수로 주어집니다.
//이때, 다음달에 가장 많은 선물을 받는 친구가 받을 선물의 수를 return 하도록 solution 함수를 완성해 주세요.

using System;
using System.Collections.Generic;
using System.Linq;

public class Solution
{
    public int solution(string[] friends, string[] gifts)
    {
        //선물을 누구에게 줬는지, 선물의 지수,답에 대한 사전 지정
        Dictionary<(string, string), int> giftEqual = new Dictionary<(string, string), int>();
        Dictionary<string, int> giftCount = new Dictionary<string, int>();
        Dictionary<string, int> answer = new Dictionary<string, int>();
        
        //누가 누구에게 줬는지 토큰을 나눠 2명으로 문자열을 쪼개어 누구에게 준지와 선물지수를 업데이트
        foreach (var record in gifts)
        {
            string[] tokens = record.Split(' ');
            string giver = tokens[0];
            string receiver = tokens[1];
            var key = (giver, receiver);

            giftEqual[key] = giftEqual.GetValueOrDefault(key, 0) + 1;
            giftCount[giver] = giftCount.GetValueOrDefault(giver, 0) + 1;
            giftCount[receiver] = giftCount.GetValueOrDefault(receiver, 0) - 1;
        }
        //최종 가장 많은 선물의 개수 구하기
        foreach (var friend in friends)
        {
            foreach (var friend2 in friends)
            {
                var key1 = (friend, friend2);
                var key2 = (friend2, friend);
                //선물을 주고받지 않은 경우 방지용 코드
                int equalCount1 = giftEqual.GetValueOrDefault(key1, 0);
                int equalCount2 = giftEqual.GetValueOrDefault(key2, 0);

                if (equalCount1 > equalCount2)
                {
                    answer[friend] = answer.GetValueOrDefault(friend, 0) + 1;
                }
                else if (equalCount1 == equalCount2)
                {
                    int countFriend, countFriend2;
                    giftCount.TryGetValue(friend, out countFriend);
                    giftCount.TryGetValue(friend2, out countFriend2);
                    //선물지수 비교
                    if (countFriend > countFriend2)
                    {
                        answer[friend] = answer.GetValueOrDefault(friend, 0) + 1;
                    }
                }
            }
        }

        return answer.Values.Any() ? answer.Values.Max() : 0;
    }
}
