#include <cstdio>  
#include <cmath>  
#include <limits>
#include <algorithm>  
using namespace std;

struct Point{
    double x, y;
};

const double INF = numeric_limits<double>::max();
const int MAX = 100005;
int mpt[MAX];
Point points[MAX];

//以x为基准排序
bool cmpxy(const Point &a, const Point &b){
    if(a.x != b.x){
        return a.x < b.x;
    }
    return a.y < b.y;
}

bool cmpy(const int &a, const int &b){
    return points[a].y < points[b].y;
}

double min(double a, double b){
    return a < b ? a : b;
}

double dis(int i, int j){
    return sqrt((points[i].x - points[j].x) * (points[i].x - points[j].x) + (points[i].y - points[j].y) * (points[i].y - points[j].y));
}

double Closest_Pair(int left, int right){
    double d = INF;
    if(left == right) return d;
    if(left + 1 == right) return dis(left, right);
    int mid = (left + right) >> 1;
    double d1 = Closest_Pair(left, mid);
    double d2 = Closest_Pair(mid + 1, right);
    d = min(d1, d2);
    int k = 0;
    //分离出宽度为d的区间  
    for(int i = left; i <= right; ++i){
        if(fabs(points[mid].x - points[i].x) <= d){
            mpt[k++] = i;
        }
    }
    sort(mpt, mpt + k, cmpy);
    //线性扫描  
    for(int i = 0; i < k; ++i){
        for(int j = i + 1; j < k && points[mpt[j]].y - points[mpt[i]].y < d; ++j){
            double d3 = dis(mpt[i], mpt[j]);
            if(d > d3) d = d3;
        }
    }
    return d;
}

int main(){
    int n;
    while(scanf("%d", &n) == 1 && n != 0){
        for(int i = 0; i < n; i++){
            scanf("%lf%lf", &points[i].x, &points[i].y);
        }
        sort(points, points + n, cmpxy);
        printf("%.02lf\n", Closest_Pair(0, n - 1) / 2);
    }
    return 0;
}
