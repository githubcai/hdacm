#include <limits>
#include <algorithm>
#include <cstdio>
#include <cmath>
using namespace std;

struct Point{
    int x, y;
};

const int INF = numeric_limits<int>::max(), MAX = 1005;
Point p[MAX], s[MAX];
int top;

int direction(const Point &p1, const Point &p2, const Point &p3){
    return (p3.x - p1.x) * (p2.y - p1.y) - (p2.x - p1.x) * (p3.y - p1.y);
}

int dis(const Point &p1, const Point &p2){
    return (p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y);
}

bool cmp(const Point &p1, const Point &p2){
    int temp = direction(p[0], p1, p2);
    if(temp < 0) return true;
    if(temp == 0 && dis(p[0], p1) < dis(p[0], p2)) return true;
    return false;
}

void graham(int n){
    int pos, minx, miny;
    minx = miny = INF;
    for(int i = 0; i < n; ++i){
        if(p[i].x < minx || (p[i].x == minx && p[i].y < miny)){
            minx = p[i].x;
            miny = p[i].y;
            pos = i;
        }
    }
    swap(p[0], p[pos]);
    sort(p + 1, p + n, cmp);
    p[n] = p[0];
    s[0] = p[0], s[1] = p[1], s[2] = p[2];
    top = 2;
    for(int i = 3; i <= n; ++i){
        while(direction(s[top - 1], s[top], p[i]) >= 0 && top >= 2) --top;
        s[++top] = p[i];
    }
}

int main(){
    int n;
    while(scanf("%d", &n) == 1 && n != 0){
        for(int i = 0; i < n; ++i){
            scanf("%d%d", &p[i].x, &p[i].y);
        }
        if(n == 1){
            printf("0.00\n");
            continue;
        }
        if(n == 2){
            printf("%.02lf\n", sqrt(dis(p[0], p[1])));
            continue;
        }
        graham(n);
        double sum = 0;
        for(int i = 0; i < top; ++i){
            sum += sqrt(dis(s[i], s[i + 1]));
        }
        printf("%.02lf\n", sum);
    }
    return 0;
}
