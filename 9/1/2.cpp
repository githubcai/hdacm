#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

struct Node{
    int time, score;
};

const int MAX = 1000;
Node store[MAX];
bool flag[MAX];

bool cmp(const Node &a, const Node &b){
    if(a.score == b.score) return a.time < b.time;
    return a.score > b.score;
}

int main(){
    int T; scanf("%d", &T);
    while(T-- > 0){
        int N; scanf("%d", &N);
        memset(store, 0, sizeof(store));
        for(int i = 0; i < N; ++i){
            scanf("%d", &store[i].time);
        }
        for(int i = 0; i < N; ++i){
            scanf("%d", &store[i].score);
        }
        sort(store, store + N, cmp);
        memset(flag, 0, sizeof(flag));
        int result = 0;
        for(int i = 0; i < N; ++i){
            int j;
            for(j = store[i].time - 1; j >= 0; --j){
                if(!flag[j]){
                    flag[j] = true;
                    break;
                }
            }
            if(j < 0) result += store[i].score;
        }
        printf("%d\n", result);
    }
    return 0;
}
