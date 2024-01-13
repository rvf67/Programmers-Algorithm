using System;
using System.Collections.Generic;

public class Solution
{
    void Main(string[] args)
    // ^ This method should be named Main with an uppercase 'M'
    {
        Solution s = new Solution();
        s.solution(new int[,] { { 2, 3 }, { 4, 3 }, { 1, 1 }, { 2, 1 } });
    }

    public class DataClass
    {
        public int giveCount;
        public int receiveCount;

        public DataClass()
        {
            giveCount = 0;
            receiveCount = 0;
        }
    }

    public int[] solution(int[,] edges)
    {
        int[] answer = new int[4] { 0, 0, 0, 0 };
        int maxNum = 0;
        int graphNum = 0; // Added a missing semicolon here

        var dict = new Dictionary<int, DataClass>();

        for (int i = 0; i < edges.GetLength(0); i++) // Removed the "=" in the loop condition
        {
            int giveNum = edges[i, 0];
            int receiveNum = edges[i, 1];

            if (maxNum < giveNum) maxNum = giveNum;
            if (maxNum < receiveNum) maxNum = receiveNum;

            if (!dict.ContainsKey(giveNum))
                dict.Add(giveNum, new DataClass());
            if (!dict.ContainsKey(receiveNum))
                dict.Add(receiveNum, new DataClass());

            dict[giveNum].giveCount++;
            dict[receiveNum].receiveCount++;
        }

        for (int n = 0; n <= maxNum; n++)
        {
            if (dict.ContainsKey(n) && dict[n].receiveCount == 0)
            {
                answer[0] = n;
                graphNum = dict[n].giveCount;
            }
            else if (dict.ContainsKey(n) && dict[n].giveCount == 0)
            {
                answer[2]++;
            }
            else if (dict.ContainsKey(n) && dict[n].receiveCount == 2 && dict[n].giveCount == 2)
            {
                answer[3]++;
            }
        }

        answer[1] = graphNum - answer[2] - answer[3];
        return answer;
    }
}