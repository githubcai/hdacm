#include <cstdio>
#include <cmath>
#include <cstring>
#include <limits>
using namespace std;

struct Node{
    double x, y;
};

const int MAX = 100;
const double INF = numeric_limits<double>::max();
int n;
double distance[MAX][MAX];

double calDist(const Node &a, const Node &b){
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

void prim(){
    int a[n];
    double dist[n];
    for(int i = 0; i < n; ++i){
        a[i] = i;
        dist[i] = distance[0][i];
    }
    double result = 0;
    for(int i = 0; i < n - 1; ++i){
        int mark = 0;
        double tMin = INF;
        for(int j = i + 1; j < n; ++j){
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
    printf("%.02lf\n", result);
}

int main(){
    while(scanf("%d", &n) == 1){
        Node points[n];
        for(int i = 0; i < n; ++i){
            scanf("%lf%lf", &points[i].x, &points[i].y);
        }
        memset(distance, 0, sizeof(distance));
        for(int i = 0; i < n - 1; ++i){
            for(int j = i + 1; j < n; ++j){
                distance[i][j] = distance[j][i] = calDist(points[i], points[j]);
            }
        }
        prim();
    }
    return 0;
}
