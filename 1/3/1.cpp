#include <cstdio>
#include <array>
#include <string>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

bool cmp(const pair<string, int> &x, const pair<string, int> &y){
    if(x.second > y.second){
        return true;
    }else if(x.second == y.second){
        return x.first < y.first;
    }else{
        return false;
    }
}

int main(){
    int N, M, G;
    array<int, 10> table;
    vector<pair<string, int>> ref;
    while(scanf("%d", &N) != EOF, N != 0){
        ref.clear();
        scanf("%d %d", &M, &G);
        for(int i = 0; i < M; ++i){
            scanf("%d", &table[i]);
        }
        for(int i = 0; i < N; ++i){
            char ctemp[22];
            int ntemp;
            scanf("%s %d", ctemp, &ntemp);
            int sum = 0;
            for(int j = 0; j < ntemp; ++j){
                int grade;
                scanf("%d", &grade);
                sum += table[grade - 1];
            }
            if(sum >= G){
                ref.push_back(make_pair(ctemp, sum));
            }
        }
        sort(ref.begin(), ref.end(), cmp);
        cout << ref.size() << endl;
        for(auto iter = ref.begin(); iter != ref.end(); ++iter){
            cout << iter->first << " " << iter->second << endl;
        }
    }
    return 0;
}
