#include <string>
#include <iostream>
#include <array>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX = 100;

array<int, MAX> scores;
array<int, 6> cnt;
int N, P;

bool cmp(const pair<int, string> &x, const pair<int, string> &y){
    return x.second < y.second;
}

void calPoint(array<vector<pair<int, string>>, MAX> &solvedTime){
    for(int i = 1; i <= 4; ++i){
        if(cnt[i] == 0) continue;
        if(cnt[i] == 1) scores[solvedTime[i][0].first] += 5;
        sort(solvedTime[i].begin(), solvedTime[i].end(), cmp);
        int end = cnt[i] / 2;
        for(int j = 0; j < end; ++j){
            scores[solvedTime[i][j].first] += 5;
        }
    }
}

void printPoint(){
    for(int i = 0; i < N; ++i){
        cout << scores[i] << endl;
    }
    cout << endl;
}

int main(){
    string time;
    while(cin >> N, N != -1){
        array<vector<pair<int, string>>, MAX> solvedTime;
        cnt.fill(0);
        for(int i = 0; i < N; ++i){
            cin >> P >> time;
            cnt[P] += 1;
            solvedTime[P].push_back(make_pair(i, time));
            switch(P){
            case 0: scores[i] = 50; break;
            case 1: scores[i] = 60; break;
            case 2: scores[i] = 70; break;
            case 3: scores[i] = 80; break;
            case 4: scores[i] = 90; break;
            case 5: scores[i] = 100; break;
            }
        }
        calPoint(solvedTime);
        printPoint();
    }
}
