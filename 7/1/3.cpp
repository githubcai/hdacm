#include <cstdio>

int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        int N; scanf("%d", &N);
        double x1, y1, x2, y2, x3, y3, area = 0.0, xt = 0.0, yt = 0.0;
        scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
        for(int i = 2; i < N; ++i){
            scanf("%lf%lf", &x3, &y3);
            double ax, ay, s;
            ax = x1 + x2 + x3;
            ay = y1 + y2 + y3;
            s = ((x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1)) / 2.0;
            xt += ax * s, yt += ay * s, area += s;
            x2 = x3, y2 = y3;
        }
        double  xr = xt / area / 3, yr = yt / area / 3;
        printf("%.02lf %.02lf\n", xr, yr);
    }
    return 0;
}
