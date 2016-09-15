#include <cstdio>
#include <cstring>

const int MAX = 30001;
int father[MAX], rank[MAX], total[MAX];

void init(){
    for(int i = 0; i < MAX; ++i){
        father[i] = i;
        total[i] = 1;
    }
    memset(rank, 0, sizeof(rank));
}

int find(int x){
    if(x == father[x]) return x;
    int temp = father[x];
    father[x] = find(father[x]);
    rank[x] += rank[temp];
    return father[x];
}

void merge(int a, int b){
    int ar, br;
    ar = find(a), br = find(b);
    if(ar != br){
        father[br] = ar;
        rank[br] += total[ar];
        total[ar] += total[br];
    }
}

int main(){
    int P;
    while(scanf("%d", &P) == 1){
        init();
        for(int i = 0; i < P; ++i){
            char oper[2]; scanf("%s", oper);
            switch(oper[0]){
                case 'M':{
                    int a, b;
                    scanf("%d%d", &a, &b);
                    merge(a, b);
                    break;
                }
                case 'C':{
                    int a; scanf("%d", &a);
                    int ar = find(a);
                    printf("%d\n", total[ar] - rank[a] - 1);
                    break;
                }
            }
        }
    }
    return 0;
}
