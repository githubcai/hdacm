#include <cstdio>
#include <cstring>
#include <cmath>

const int NMAX = 210, MMAX = 40010;
struct Edge{
    int to, next;
};

struct Point{
    int x, y;
};

Edge edge[MMAX];
int head[NMAX], edgeNum, Stack[NMAX], top;
bool mark[NMAX];
Point s[NMAX];

void init(){
    memset(head, -1, sizeof(head));
    edgeNum = 0;
    memset(mark, 0, sizeof(mark));
}

void addEdge(int u, int v){
    Edge E = {v, head[u]};
    edge[edgeNum] = E;
    head[u] = edgeNum++;
}

bool dfs(int x){
    if(mark[x ^ 1]) return false;
    if(mark[x]) return true;
    mark[x] = true;
    Stack[top++] = x;
    for(int i = head[x]; i != -1; i = edge[i].next){
        if(!dfs(edge[i].to)) return false;
    }
    return true;
}

bool solve(int n){
    for(int i = 0; i < n; i += 2){
        if(!mark[i] && !mark[i ^ 1]){
            top = 0;
            if(!dfs(i)){
                while(top) mark[Stack[--top]] = false;
                if(!dfs(i ^ 1)) return false;
            }
        }
    }
    return true;
}

double Distance(Point a, Point b){
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int main(){
    int N;
    while(scanf("%d", &N) == 1){
        for(int i = 0; i < N; ++i){
            scanf("%d%d%d%d", &s[2 * i].x, &s[2 * i].y, &s[2 * i + 1].x, &s[2 * i + 1].y);
        }
        double left = 0.0, right = 40000.0, radius;
        while(right - left >= 1e-5){
            radius = (right + left) / 2;
            init();
            for(int i = 0; i < 2 * N - 2; ++i){
                int t;
                if(i % 2 == 0){
                    t = i + 2;
                }else{
                    t = i + 1;
                }
                for(int j = t; j < N * 2; ++j){
                    if(Distance(s[i], s[j]) < radius * 2){
                        addEdge(i, j ^ 1);
                        addEdge(j, i ^ 1);
                    }
                }
            }
            if(solve(2 * N)){
                left = radius;
            }else{
                right = radius;
            }
        }
        printf("%.2lf\n", radius);
    }
    return 0;
}
