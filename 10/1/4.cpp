#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const int NMAX = 1001, MMAX = 2000;
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
        int now;
        ++taj;
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
    for(int i = 1; i <= all; ++i){
        if(DFN[i] == -1) tarjan(i);
    }
}

int du[NMAX], money[NMAX];
void suodian(){
    memset(du, 0, sizeof(du));
    for(int i = 0; i < edgeNum; ++i){
        int u = Belong[edge[i].from], v = Belong[edge[i].to];
        if(u != v) ++du[v];
    }
}

int main(){
    int N, M, result[NMAX];
    while(scanf("%d%d", &N, &M) == 2){
        for(int i = 1; i <= N; ++i){
            scanf("%d", &money[i]);
        }
        init();
        for(int i = 0; i < M; ++i){
            int a, b;
            scanf("%d%d", &a, &b);
            add(a, b);
        }
        tarjan_init(N);
        suodian();
        memset(result, -1, sizeof(result));
        for(int i = 1; i <= N; ++i){
            if(du[Belong[i]] == 0){
                if(result[Belong[i]] == -1){
                    result[Belong[i]] = money[i];
                }else{
                    result[Belong[i]] = result[Belong[i]] < money[i] ? result[Belong[i]] : money[i];
                }
            }
        }
        int sum = 0, num = 0;
        for(int i = 1; i <= taj; ++i){
            if(result[i] != -1){
                sum += result[i];
                num += 1;
            }
        }
        printf("%d %d\n", num, sum);
    }
    return 0;
}
