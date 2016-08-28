#include <cstdio>
#include <cstring>

const int MAX = 100001;
bool flag, mark[MAX];
int pre[MAX], count;

void init(){
    for(int i = 1; i < MAX; ++i){
        pre[i] = i;
    }
    memset(mark, 0, sizeof(mark));
    flag = true;
    count = 0;
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
    if(ar == br || br != b){
        flag = false;
    }else{
        pre[br] = ar;
        --count;
    }
}

int main(){
    int n, m, cnt = 0;
    while(scanf("%d%d", &n, &m) == 2 && n >= 0 && m >= 0){
        ++cnt;
        init();
        if(n == 0 && m == 0){
            printf("Case %d is a tree.\n", cnt);
        }else{
            while(true){
                if(n == 0 && m == 0) break;
                if(!mark[n]) ++count;
                if(!mark[m]) ++count;
                mark[n] = mark[m] = true;
                if(flag) merge(n, m);
                scanf("%d%d", &n, &m);
            }
            if(flag && count == 1){
                printf("Case %d is a tree.\n", cnt);
            }else{
                printf("Case %d is not a tree.\n", cnt);
            }
        }
    }
    return 0;
}
