#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

//프로그래머스 공원산책 문제
//단순 길찾기

vector<int> solution(vector<string> park, vector<string> routes) {
    vector<int> answer;
    int height = park.size();
    int weight = park[0].size();
    vector<int> dog;
    void transform(vector<string>& park, vector<int>& dog, string direction, int distance);
    vector<string> split(string input, char delimiter);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < weight; j++) {
            if (park[i][j] == 'S') {
                dog.push_back(i);
                dog.push_back(j);
                break;
            }
        }
    }
    for (int i = 0; i < routes.size(); i++) {
        vector<string> tokens = split(routes[i], ' ');
        transform(park, dog, tokens[0], stoi(tokens[1]));
    }
    answer = dog;
    return answer;
}

void transform(vector<string>& park, vector<int>& dog,string direction, int distance) {
    if (direction == "W") {
        if (dog[1] - distance < 0) {
            return;
        }
        for (int i = 1; i <= distance; i++) {
            if (park[dog[0]][dog[1]-i] == 'X') {
                return;
            }
        }
        park[dog[0]][dog[1]] = 'O';
        park[dog[0]][dog[1] - distance] = 'S';
        dog[1] = dog[1] - distance;
    }else if (direction == "E") {
        if (dog[1] + distance > park[0].size()-1) {
            return;
        }
        for (int i = 1; i <= distance; i++) {
            if (park[dog[0]][dog[1] + i] == 'X') {
                return;
            }
        }
        park[dog[0]][dog[1]] = 'O';
        park[dog[0]][dog[1] + distance] = 'S';
        dog[1] = dog[1] + distance;
    }else if (direction == "N") {
        if (dog[0] - distance < 0) {
            return;
        }
        for (int i = 1; i <= distance; i++) {
            if (park[dog[0]-i][dog[1]] == 'X') {
                return;
            }
        }
        park[dog[0]][dog[1]] = 'O';
        park[dog[0]-distance][dog[1]] = 'S';
        dog[0] = dog[0] - distance;
    }else if (direction == "S") {
        if (dog[0] + distance > park.size()-1) {
            return;
        }
        for (int i = 1; i <= distance; i++) {
            if (park[dog[0]+i][dog[1]] == 'X') {
                return;
            }
        }
        park[dog[0]][dog[1]] = 'O';
        park[dog[0]+distance][dog[1]] = 'S';
        dog[0] = dog[0] + distance;
    }
}

vector<string> split(string input, char delimiter) {
    vector<string> answer;
    stringstream ss(input);
    string temp;

    while (getline(ss, temp, delimiter)) {
        answer.push_back(temp);
    }

    return answer;
}

int main()
{
    vector<int> result = solution({ "OSO", "OOO", "OXO", "OOO" }, { "E 2", "S 3", "W 1" });
    for (int i = 0; i < result.size(); i++) {
        cout << result[i];
    }
}

