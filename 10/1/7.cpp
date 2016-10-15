#include <cstdio>
#include <cstring>
#include <vector>
#include <cmath>
using namespace std;

const int NMAX = 10001, MMAX = 20000;
struct Edge{
    int from, to, next;
    bool cut;
};
Edge edge[2 * MMAX];
int head[NMAX], edgeNum;
int num[NMAX], DFN[NMAX], Low[NMAX], Stack[NMAX], top, Index, block, bridge, Belong[NMAX];
bool InStack[NMAX];

void addEdge(int u, int v){
    Edge E1 = {u, v, head[u], false}; edge[edgeNum] = E1; head[u] = edgeNum++;
    Edge E2 = {v, u, head[v], false}; edge[edgeNum] = E2; head[v] = edgeNum++;
}

void init(){
    edgeNum = 0;
    memset(head, -1, sizeof(head));
}

void Tarjan(int u, int pre){
    Low[u] = DFN[u] = ++Index;
    Stack[top++] = u;
    InStack[u] = true;
    int v, pre_num = 0;
    for(int i = head[u]; i != -1; i = edge[i].next){
        v = edge[i].to;
        if(v == pre && pre_num == 0){
            ++pre_num;
            continue;
        }
        if(DFN[v] == 0){
            Tarjan(v, u);
            Low[u] = Low[u] < Low[v] ? Low[u] : Low[v];
            if(Low[v] > DFN[u]){
                ++bridge;
                edge[i].cut = true;
                edge[i ^ 1].cut = true;
            }
        }else if(InStack[v]){
            Low[u] = Low[u] < DFN[v] ? Low[u] : DFN[v];
        }
    }
    if(Low[u] == DFN[u]){
        ++block;
        do{
            v = Stack[--top];
            InStack[v] = false;
            Belong[v] = block;
        }while(v != u);
    }
}

void work(int l, int r){
    memset(DFN, 0, sizeof(DFN));
    memset(InStack, 0, sizeof(InStack));
    Index = top = block = bridge = 0;
    for(int i = l; i <= r; ++i) if(!DFN[i]) Tarjan(i, i);
}

vector<int> G[NMAX];
int count[NMAX], total;
void suodian(){
    bool flag[NMAX];
    memset(flag, 0, sizeof(flag));
    memset(count, 0, sizeof(count));
    for(int i = 1; i <= block; ++i) G[i].clear();
    for(int i = 0; i < edgeNum; i += 2){
        int u = Belong[edge[i].from], v = Belong[edge[i].to];
        if(u != v){
            G[u].push_back(v), G[v].push_back(u);
        }
        if(!flag[edge[i].from]){
            flag[edge[i].from] = true;
            count[u] += num[edge[i].from];
        }
        if(!flag[edge[i].to]){
            flag[edge[i].to] = true;
            count[v] += num[edge[i].to];
        }
    }
}

int ans;
int dfs(int u, int fa){
    int sum = 0;
    for(auto iter = G[u].begin(); iter != G[u].end(); ++iter){
        if(*iter != fa){
            sum += dfs(*iter, u);
        }
    }
    sum += count[u];
    int temp = fabs(total - 2 * sum);
    ans = temp < ans ? temp : ans;
    return sum;
}

int main(){
    int N, M;
    while(scanf("%d%d", &N, &M) == 2){
        total = 0;
        for(int i = 0; i < N; ++i){
            scanf("%d", &num[i]);
            total += num[i];
        }
        init();
        for(int i = 0; i < M; ++i){
            int a, b; scanf("%d%d", &a, &b);
            addEdge(a, b);
        }
        work(0, N - 1);
        if(block < 2){
            printf("impossible\n");
            continue;
        }else{
            suodian();
        }
        ans = 0x7fffffff;
        dfs(1, 1);
        printf("%d\n", ans);
    }
    return 0;
}
