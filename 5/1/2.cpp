#include <cstdio>
#include <cstring>

const int MAX = 100001;
int pre[MAX], count;
bool flag, mark[MAX];

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
    ar = find(a);
    br = find(b);
    if(ar == br){
        flag = false;
    }else{
        pre[ar] = br;
        --count;
    }
}

int main(){
    int n, m;
    while(scanf("%d%d", &n, &m) == 2 && n != -1 && m != -1){
        init();
        if(n == 0 && m == 0){
            printf("Yes\n");
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
                printf("Yes\n");
            }else{
                printf("No\n");
            }
        }
    }
    return 0;
}
