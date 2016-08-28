#include <cstdio>
#include <cstring>

const int MAX = 2001;
int rank[MAX], pre[MAX];
bool flag;

void init(int n){
    memset(rank, 0, sizeof(rank));
    for(int i = 1; i <= n; ++i){
        pre[i] = i;
    }
    flag = true;
}

int find(int x){
    if(pre[x] == x) return x;
    int temp = pre[x];
    pre[x] = find(temp);
    rank[x] = (rank[temp] + rank[x]) % 2;
    return pre[x];
}

void merge(int a, int b){
    int ar, br;
    ar = find(a), br = find(b);
    if(ar == br){
        if(rank[a] == rank[b]){
            flag = false;
        }
    }else{
        pre[ar] = br;
        rank[ar] = ((rank[a] - rank[b] - 1) % 2 + 2) % 2;
    }
}

int main(){
    int T, cnt = 0;
    scanf("%d", &T);
    while(T-- > 0){
        int n, m;
        scanf("%d%d", &n, &m);
        init(n);
        for(int i = 0; i < m; ++i){
            int t1, t2;
            scanf("%d%d", &t1, &t2);
            if(!flag) continue;
            merge(t1, t2);
        }
        ++cnt;
        printf("Scenario #%d:\n", cnt);
        if(flag){
            printf("No suspicious bugs found!\n");
        }else{
            printf("Suspicious bugs found!\n");
        }
        printf("\n");
    }
    return 0;
}
