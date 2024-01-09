using System;
using System.Collections.Generic;
using System.Linq;

public class Solution
{
    public int solution(string[] friends, string[] gifts)
    {
        Dictionary<(string, string), int> giftEqual = new Dictionary<(string, string), int>();
        Dictionary<string, int> giftCount = new Dictionary<string, int>();
        Dictionary<string, int> answer = new Dictionary<string, int>();

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

        foreach (var friend in friends)
        {
            foreach (var friend2 in friends)
            {
                var key1 = (friend, friend2);
                var key2 = (friend2, friend);

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