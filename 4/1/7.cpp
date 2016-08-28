#include <cstdio>
#include <cmath>

class Point{
public:
    double r, h;
};

const int MAX = 10000;
Point points[MAX];

double cal(double r, int n){
    double mh = -1;
    for(int i = 0; i < n; ++i){
        double h = points[i].h / (r - points[i].r);
        if(mh < h) mh = h;
    }
    return mh * r;
}

int main(){
    int T;
    scanf("%d", &T);
    while(T-- > 0){
        int n;
        scanf("%d", &n);
        double x, y, rmax = -1;
        for(int i = 0; i < n; ++i){
            scanf("%lf%lf%lf", &x, &y, &points[i].h);
            points[i].r = sqrt(x * x + y * y);
            if(rmax < points[i].r) rmax = points[i].r;
        }
        double left = rmax, right = 1500;
        double th1, th2, tv1, tv2;
        while(right - left > 1e-7){
            double mid1 = (left + right) / 2;
            double mid2 = (mid1 + right) / 2;
            th1 = cal(mid1, n), th2 = cal(mid2, n);
            tv1 = th1 * mid1 * mid1, tv2 = th2 * mid2 * mid2;
            if(tv1 > tv2){
                left = mid1;
            }else{
                right = mid2;
            }
        }
        printf("%.03lf %.03lf\n", th1, left);
    }
    return 0;
}
