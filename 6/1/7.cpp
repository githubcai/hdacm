#include <cstdio>
#include <limits>
using namespace std;

const int MAX = 500, INF = numeric_limits<int>::max();
int N, distance[MAX][MAX];

void prim(){
    bool flag = true;
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
        if(tMin == INF){
            flag = false;
            break;
        }
        int t = a[i + 1];
        a[i + 1] = a[mark];
        a[mark] = t;
        result += tMin;
    }
    if(flag){
        printf("%d\n", result);
    }else{
        printf("-1\n");
    }
}

int main(){
    int T;
    scanf("%d", &T);
    while(T-- > 0){
        int m, k;
        scanf("%d%d%d", &N, &m, &k);
        for(int i = 0; i < N; ++i){
            for(int j = 0; j < N; ++j){
                distance[i][j] = INF;
            }
        }
        for(int i = 0; i < m; ++i){
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            if(c < distance[a - 1][b - 1]){
                distance[a - 1][b - 1] = distance[b - 1][a - 1] = c;
            }
        }
        for(int i = 0; i < k; ++i){
            int t, temp[N];
            scanf("%d", &t);
            for(int i = 0; i < t; ++i){
                scanf("%d", &temp[i]);
            }
            for(int i = 0; i < t - 1; ++i){
                for(int j = i + 1; j < t; ++j){
                    distance[temp[i] - 1][temp[j] - 1] = 
                    distance[temp[j] - 1][temp[i] - 1] = 0;
                }
            }
        }
        prim();
    }
    return 0;
}
