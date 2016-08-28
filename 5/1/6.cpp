#include <cstdio>

const int MAX = 10001;
int pre[MAX], N, Q, num[MAX], tran[MAX];

void init(){
    for(int i = 1; i <= N; ++i){
        pre[i] = i;
        num[i] = 1;
        tran[i] = 0;
    }
}

int find(int x){
    if(x == pre[x]) return x;
    int temp = pre[x];
    pre[x] = find(pre[x]);
    tran[x] = tran[x] + tran[temp];
    return pre[x];
}

void merge(int a, int b){
    int ar, br;
    ar = find(a), br = find(b);
    if(ar != br){
        pre[ar] = br;
        tran[ar] += 1;
        num[br] += num[ar];
    }
}

int main(){
    int T, cnt = 0;
    scanf("%d", &T);
    while(T-- > 0){
        ++cnt;
        printf("Case %d:\n", cnt);
        scanf("%d %d\n", &N, &Q);
        init();
        for(int i = 0; i < Q; ++i){
            char c;
            scanf("%c", &c);
            if(c == 'T'){
                int a, b;
                scanf("%d %d\n", &a, &b);
                merge(a, b);
            }else{
                int a, ar;
                scanf("%d\n", &a);
                ar = find(a);
                printf("%d %d %d\n", ar, num[ar], tran[a]);
            }
        }
    }
    return 0;
}
