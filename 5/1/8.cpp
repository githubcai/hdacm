#include <cstdio>
#include <cstring>

const int NMAX = 200001;
int count, N, M, pre[NMAX], sum[NMAX];

void init(){
    memset(sum, 0, sizeof(sum));
    for(int i = 0; i <= N; ++i){
        pre[i] = i;
    }
    count = 0;
}

int find(int x){
    if(x == pre[x]) return x;
    int temp = pre[x];
    pre[x] = find(pre[x]);
    sum[x] = sum[x] + sum[temp];
    return pre[x];
}

int merge(int a, int b, int s){
    int ar, br;
    ar = find(a), br = find(b);
    if(ar < br){
        pre[ar] = br;
        sum[ar] = sum[b] - sum[a] + s;
    }else if(ar == br){
        if(sum[a] - sum[b] != s) ++count;
    }else{
        pre[br] = ar;
        sum[br] = sum[a] - sum[b] - s;
    }
}

int main(){
    while(scanf("%d%d", &N, &M) == 2){
        init();
        for(int i = 0; i < M; ++i){
            int Ai, Bi, Si;
            scanf("%d%d%d", &Ai, &Bi, &Si);
            if(Ai <= Bi){
                merge(Ai - 1, Bi, Si);
            }else{
                merge(Bi - 1, Ai, Si);
            }
        }
        printf("%d\n", count);
    }
    return 0;
}
