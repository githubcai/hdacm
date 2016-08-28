#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
#include <stack>

using namespace std;

class Mouse{
public:
    int weight;
    int speed;
    int num;
};

bool comp(const Mouse &a, const Mouse &b){
    return a.weight < b.weight;
}

int main(){
    vector<Mouse> store;
    Mouse temp;
    for(int i = 1; scanf("%d%d", &temp.weight, &temp.speed) == 2; ++i){
        temp.num = i;
        store.push_back(temp);
    }
    sort(store.begin(), store.end(), comp);
    
    int dp[1000], pi[1000];
    memset(pi, -1, sizeof(pi));
    dp[0] = 1;
    for(int i = 1; i < store.size(); ++i){
        dp[i] = 1;
        for(int j = 0; j < i; ++j){
            if(store[i].speed < store[j].speed && dp[i] < dp[j] + 1 && store[i].weight != store[j].weight){
                dp[i] = dp[j] + 1;
                pi[i] = j;
            }
        }
    }
    int max = 0, mi;
    for(int i = 0; i < store.size(); ++i){
        if(max < dp[i]){
            max = dp[i];
            mi = i;
        }
    }
    printf("%d\n", max);
    stack<int> result;
    result.push(store[mi].num);
    while(pi[mi] != -1){
        mi = pi[mi];
        result.push(store[mi].num);
    }
    while(!result.empty()){
        printf("%d\n", result.top());
        result.pop();
    }
    return 0;
}
