#include <cstdio>
#include <cstring>

const int NMAX = 100000, MAX = 10000000;
int edge, ref[NMAX], pre[MAX], N, M;
bool flag[MAX];

void init(){
    for(int i = 0; i < N; ++i){
        pre[i] = ref[i] = i;
    }
    edge = N;
}

int find(int x){
    if(x == pre[x]) return x;
    int temp = pre[x];
    pre[x] = find(pre[x]);
    return pre[x];
}

void merge(int a, int b){
    int ar, br;
    ar = find(a), br = find(b);
    if(ar != br){
        pre[ar] = br;
    }
}

int main(){
    int cnt = 0;
    while(scanf("%d %d\n", &N, &M) == 2 && !(M == 0 && N == 0)){
        init();
        for(int i = 0; i < M; ++i){
            char c;
            scanf("%c", &c);
            if(c == 'M'){
                int a, b;
                scanf("%d %d\n", &a, &b);
                merge(ref[a], ref[b]);
            }else{
                int a;
                scanf("%d\n", &a);
                ref[a] = pre[edge] = edge;
                ++edge;
            }
        }
        ++cnt;
        int root, count = 0;
        memset(flag, 0, sizeof(flag));
        for(int i = 0; i < N; ++i){
            root = find(ref[i]);
            if(!flag[root]){
                ++count;
                flag[root] = true;
            }
        }
        printf("Case #%d: %d\n", cnt, count);
    }
    return 0;
}
