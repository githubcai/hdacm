#include <cstdio>
#include <cstring>

const int NMAX = 20001, MMAX = 50000;
struct Edge{
    int from, to, next;
};
Edge edge[MMAX];
int head[NMAX], edgeNum;
int DFN[NMAX], Low[NMAX], Stack[NMAX], Belong[NMAX], top, Time, taj;
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
            Belong[now] = taj;
        }while(now != u);
    }
}

void tarjan_init(int all){
    memset(DFN, -1, sizeof(DFN));
    memset(InStack, 0, sizeof(InStack));
    top = Time = taj = 0;
    for(int i = 1; i <= all; ++i) if(DFN[i] == -1) tarjan(i);
}

int inDu[NMAX], outDu[NMAX];
void suodian(){
    memset(inDu, 0, sizeof(inDu));
    memset(outDu, 0, sizeof(outDu));
    for(int i = 0; i < edgeNum; ++i){
        int u = Belong[edge[i].from], v = Belong[edge[i].to];
        if(u != v) ++inDu[v], ++outDu[u];
    }
}

int main(){
    int T; scanf("%d", &T);
    while(T-- > 0){
        int n, m; scanf("%d%d", &n, &m);
        init();
        for(int i = 0; i < m; ++i){
            int a, b; scanf("%d%d", &a, &b);
            add(a, b);
        }
        tarjan_init(n);
        if(taj == 1){
            printf("0\n");
        }else{
            suodian();
            int inNum = 0, outNum = 0;
            for(int i = 1; i <= taj; ++i){
                if(inDu[i] == 0) ++inNum;
                if(outDu[i] == 0) ++outNum;
            }
            printf("%d\n", inNum > outNum ? inNum : outNum);
        }
    }
    return 0;
}
