#include <cstdio>
#include <cstring>
#include <limits>
using namespace std;

const int INF = numeric_limits<int>::max(), MAX = 100;
int N, distance[MAX][MAX];

void prim(){
    int a[N], dist[N];
    for(int i = 0; i < N; ++i){
        a[i] = i;
        dist[i] = distance[0][i];
    }
    int result = 0;
    for(int i = 0; i < N - 1; ++i){
        int tMin = INF, mark;
        for(int j = i + 1; j < N; ++j){
            if(distance[a[i]][a[j]] < dist[a[j]]){
                dist[a[j]] = distance[a[i]][a[j]];
            }
            if(tMin > dist[a[j]]){
                tMin = dist[a[j]];
                mark = j;
            }
        }
        int t = a[i + 1];
        a[i + 1] = a[mark];
        a[mark] = t;
        result += tMin;
    }
    printf("%d\n", result);
}

int main(){
    while(scanf("%d", &N) == 1 && N != 0){
        int temp = N * (N - 1) / 2;
        memset(distance, 0, sizeof(distance));
        for(int i = 0; i < temp; ++i){
            int a, b, c, d;
            scanf("%d%d%d%d", &a, &b, &c, &d);
            if(d == 0){
                distance[a - 1][b - 1] = distance[b - 1][a - 1] = c;
            }
        }
        prim();
    }
    return 0;
}
