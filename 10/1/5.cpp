#include <cstdio>
#include <cstring>

const int NMAX = 10001, MMAX = 100000;
struct Edge{
    int from, to, next;
};

Edge edge[MMAX];
int head[NMAX], edgeNum;
int DFN[NMAX], Low[NMAX], Stack[NMAX], top, Time, taj;
bool InStack[NMAX];

void init(){
    memset(head, -1, sizeof(head));
    edgeNum = 0;
}

void add(int u, int v){
    Edge E = {u, v, head[u]};
    edge[edgeNum] = E;
    head[u] = edgeNum++;
}

void tarjan(int u){
    DFN[u] = Low[u] = ++Time;
    Stack[top++] = u;
    InStack[u] = true;
    for(int i = head[u]; i != -1; i = edge[i].next){
        int v = edge[i].to;
        if(DFN[v] == -1){
            tarjan(v);
            Low[u] = Low[u] < Low[v] ? Low[u] : Low[v];
        }else if(InStack[v]){
            Low[u] = Low[u] < DFN[v] ? Low[u] : DFN[v];
        }
    }
    if(Low[u] == DFN[u]){
        int now; ++taj;
        do{
            now = Stack[--top];
            InStack[now] = false;
        }while(now != u);
    }
}

void tarjan_init(int all){
    memset(DFN, -1, sizeof(DFN));
    memset(InStack, 0, sizeof(InStack));
    top = Time = taj = 0;
    for(int i = 1; i <= all; ++i){
        if(DFN[i] == -1) tarjan(i);
    }
}

int main(){
    int N, M;
    while(scanf("%d%d", &N, &M) == 2){
        if(N == 0 && M == 0) break;
        init();
        for(int i = 0; i < M; ++i){
            int a, b;
            scanf("%d%d", &a, &b);
            add(a, b);
        }
        tarjan_init(N);
        if(taj == 1){
            printf("Yes\n");
        }else{
            printf("No\n");
        }
    }
    return 0;
}
