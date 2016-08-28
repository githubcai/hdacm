#include <cstdio>

const int MAX = 1000;
int pre[MAX + 1], N, count;

void init(){
    for(int i = 1; i <= N; ++i){
        pre[i] = i;
    }
    count = N;
}

int find(int x){
    if(x == pre[x]) return x;
    pre[x] = find(pre[x]);
    return pre[x];
}

void merge(int a, int b){
    int ar, br;
    ar = find(a), br = find(b);
    if(ar != br){
        pre[ar] = br;
        --count;
    }
}

int main(){
    while(scanf("%d", &N) == 1 && N != 0){
        int M;
        scanf("%d", &M);
        init();
        for(int i = 0; i < M; ++i){
            int a, b;
            scanf("%d%d", &a, &b);
            merge(a, b);
        }
        printf("%d\n", count - 1);
    }
    return 0;
}
