#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

struct Tree{
    int X, H;
};

const int MAX = 100000;
int C[2][MAX + 1];

bool cmp1(const Tree &a, const Tree &b){
    return a.X < b.X;
}

bool cmp2(const Tree &a, const Tree &b){
    return a.H < b.H;
}

bool cmp3(const Tree &a, const Tree &b){
    return a.H > b.H;
}

int lowbit(int x){
    return x & (-x);
}

void update(int i, int x, int add){
    while(x <= MAX){
        C[i][x] += add;
        x += lowbit(x);
    }
}

long long getSum(int i, int x){
    long long ret = 0;
    while(x > 0){
        ret += C[i][x];
        x -= lowbit(x);
    }
    return ret;
}

int main(){
    int N;
    while(scanf("%d", &N) == 1){
        vector<Tree> store;
        for(int i = 0; i < N; ++i){
            Tree temp;
            scanf("%d%d", &temp.X, &temp.H);
            store.push_back(temp);
        }
        sort(store.begin(), store.end(), cmp1);
        int pre = -1, cnt = 0, pcnt;
        for(auto iter = store.begin(); iter != store.end(); ++iter){
            ++cnt;
            if(iter->X != pre){
                pre = iter->X;
                iter->X = cnt;
                pcnt = cnt;
            }else{
                iter->X = pcnt;
            }
        }
        sort(store.begin(), store.end(), cmp2);
        pre = - 1, cnt = 0;
        for(auto iter = store.begin(); iter != store.end(); ++iter){
            ++cnt;
            if(iter->H != pre){
                pre = iter->H;
                iter->H = cnt;
                pcnt = cnt;
            }else{
                iter->H = pcnt;
            }
        }
        sort(store.begin(), store.end(), cmp3);

        memset(C, 0, sizeof(C));
        long long ans = 0;
        for(auto iter = store.begin(); iter != store.end(); ++iter){
            long long num1 = getSum(0, iter->X - 1), num2 = getSum(0, MAX) - getSum(0, iter->X);
            long long sum1 = getSum(1, iter->X - 1), sum2 = getSum(1, MAX) - getSum(1, iter->X);
            ans += iter->H * (num1 * iter->X - sum1 + sum2 - num2 * iter->X);
            update(0, iter->X, 1);
            update(1, iter->X, iter->X);
        }
        printf("%lld\n", ans);
    }
    return 0;
}
