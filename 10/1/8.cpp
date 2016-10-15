#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAX = 55;
struct Point{
    int x, y;
};
int g[MAX][MAX], dp[MAX], can[MAX][MAX], mx, verNum, dist[1300], gdist[MAX][MAX];
Point points[MAX];

bool dfs(int pcnt, int dep){
    if(0 == pcnt){
        if(dep > mx) mx = dep;
        return true;
    }
    for(int i = 0; i < pcnt; ++i){
        int k = can[dep - 1][i], cnt = 0;
        if(dep + verNum - k <= mx) return false;
        if(dep + dp[k] <= mx) return false;
        for(int j = i + 1; j < pcnt; ++j){
            int p = can[dep - 1][j];
            if(g[k][p] == 1) can[dep][cnt++] = p;
        }
        dfs(cnt, dep + 1);
    }
    return true;
}

bool clique(int k){
    mx = 0;
    for(int i = verNum - 1; i >= 0; --i){
        int pcnt = 0;
        for(int j = i + 1; j < verNum; ++j){
            if(g[i][j] == 1) can[0][pcnt++] = j;
        }
        dfs(pcnt, 1);
        dp[i] = mx;
        if(mx >= k) return true;;
    }
    return mx >= k;
}

int Distance(const Point &a, const Point &b){
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);;
}

int main(){
    int k, cnt;
    while(scanf("%d%d", &verNum, &k) == 2){
        for(int i = 0; i < verNum; ++i){
            scanf("%d%d", &points[i].x, &points[i].y);
        }
        cnt = 0;
        for(int i = 0; i < verNum; ++i){
            for(int j = i + 1; j < verNum; ++j){
                gdist[i][j] = gdist[j][i] = Distance(points[i], points[j]);
                dist[cnt++] = gdist[i][j];
            }
        }
        sort(dist, dist + cnt);
        int left = 1, right = cnt - 1, ans = 0;
        while(left <= right){
            int mid = (left + right) / 2;
            memset(g, 0, sizeof(g));
            for(int i = 0; i < verNum; ++i){
                for(int j = i + 1; j < verNum; ++j){
                    if(gdist[i][j] >= dist[mid]){
                        g[i][j] = g[j][i] = 1;
                    }
                }
            }
            if(clique(k)){
                ans = mid;
                left = mid + 1;
            }else{
                right = mid - 1;
            }
        }
        printf("%.2lf\n", sqrt(dist[ans]));
    }
    return 0;
}
