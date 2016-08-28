#include <cstdio>
#include <limits>
using namespace std;

const int MAX = 27, INF = numeric_limits<int>::max();
int distance[MAX][MAX], N;

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
                mark = j;
                tMin = dist[a[j]];
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
        for(int i = 0; i < N; ++i){
            for(int j = 0; j < N; ++j){
                distance[i][j] = INF;
            }
        }
        for(int i = 1; i < N; ++i){
            char ch[2];
            int temp;
            scanf("%s%d", ch, &temp);
            for(int j = 0; j < temp; ++j){
                char str[2];
                int a;
                scanf("%s%d", str, &a);
                distance[ch[0] - 'A'][str[0] - 'A'] = 
                distance[str[0] - 'A'][ch[0] - 'A'] = a;
            }
        }
        prim();
    }
   return 0;
}
