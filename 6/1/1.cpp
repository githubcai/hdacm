#include <cstdio>
#include <limits>
using namespace std;

const int INF = numeric_limits<int>::max(), MAX = 100;
int N, distance[MAX][MAX];

void prim(){
    int a[N], dis[N];
    for(int i = 0; i < N; ++i){
        a[i] = i;
        dis[i] = distance[0][i];
    }
    int result = 0, mark = 0;
    for(int i = 0; i < N - 1; ++i){
        int tMin = INF;
        for(int j = i + 1; j < N; ++j){
            if(distance[a[i]][a[j]] < dis[a[j]]){
                dis[a[j]] = distance[a[i]][a[j]];
            }
            if(tMin > dis[a[j]]){
                tMin = dis[a[j]];
                mark = j;
            }
        }
        result += tMin;
        int t = a[mark];
        a[mark] = a[i + 1];
        a[i + 1] = t;
    }
    printf("%d\n", result);
}

int main(){
    while(scanf("%d", &N) == 1){
        for(int i = 0; i < N; ++i){
            for(int j = 0; j < N; ++j){
                scanf("%d", &distance[i][j]);
            }
        }
        int Q;
        scanf("%d", &Q);
        for(int i = 0; i < Q; ++i){
            int a, b;
            scanf("%d%d", &a, &b);
            distance[a - 1][b - 1] = distance[b - 1][a - 1] = 0;
        }
        prim();
    }
    return 0;
}
