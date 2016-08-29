#include<cstdio>
#include<cmath>

struct Point{  
    double x, y;  
};

const double EPS = 1e-8;
Point a[100], d;
double r;

double distance(const Point &p1, const Point &p2){  
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));      
}

double multiply(const Point &p1, const Point &p2, const Point &p0){  
    return (p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y);
}

void MiniDiscWith2Point(const Point &p, const Point &q, int n){
    d.x = (p.x + q.x) / 2.0;
    d.y = (p.y + q.y) / 2.0;
    r = distance(p, q) / 2.0;
    double c1,c2,t1,t2,t3;
    for(int k = 0; k < n; ++k){
        if(distance(d, a[k]) <= r + EPS) continue;
        if(fabs(multiply(p, q, a[k])) > EPS){
            c1 = (p.x * p.x + p.y * p.y - q.x * q.x - q.y * q.y) / 2.0;
            c2 = (p.x * p.x + p.y * p.y - a[k].x * a[k].x - a[k].y * a[k].y) / 2.0;

            d.x = (c1 * (p.y - a[k].y) - c2 * (p.y - q.y)) / ((p.x - q.x) * (p.y - a[k].y) - (p.x - a[k].x) * (p.y - q.y));
            d.y = (c1 * (p.x - a[k].x) - c2 * (p.x - q.x)) / ((p.y - q.y) * (p.x - a[k].x) - (p.y - a[k].y) * (p.x - q.x));
            r = distance(d, a[k]);
        }else{
            t1 = distance(p, q);
            t2 = distance(q, a[k]);
            t3 = distance(p, a[k]);
            if(t1 >= t2 && t1 >= t3){
                d.x = (p.x + q.x) / 2.0;
                d.y = (p.y + q.y) / 2.0;
                r = t1 / 2.0;
            }else if(t2 >= t1 && t2 >= t3){
                d.x = (a[k].x + q.x) / 2.0;
                d.y = (a[k].y + q.y) / 2.0;
                r = t2 / 2.0;
            }else{
                d.x = (a[k].x + p.x) / 2.0;
                d.y = (a[k].y + p.y) / 2.0;
                r = t3 / 2.0;
            }
        }
    }
}

void MiniDiscWithPoint(const Point &pi, int n){
    d.x = (pi.x + a[0].x) / 2.0;
    d.y = (pi.y + a[0].y) / 2.0;
    r = distance(pi, a[0]) / 2.0;
    for(int j = 1; j < n; ++j){
        if(distance(d, a[j]) > r + EPS){
            MiniDiscWith2Point(pi, a[j], j);
        }
    }
}

int main(){
    int n;
    while(scanf("%d", &n) == 1 && n != 0){
        for(int i = 0; i < n; ++i){
            scanf("%lf%lf", &a[i].x, &a[i].y);
        }
        if(n == 1){
            printf("%.02lf %.02lf 0.00\n", a[0].x, a[0].y);
            continue;
        }
        r = distance(a[0], a[1]) / 2.0;
        d.x = (a[0].x + a[1].x) / 2.0;
        d.y = (a[0].y + a[1].y) / 2.0;
        for(int i = 2; i < n; i++){
            if(distance(d, a[i]) > r + EPS){
                MiniDiscWithPoint(a[i], i);
            }
        }
        printf("%.02lf %.02lf %.02lf\n", d.x, d.y, r);
    }
    return 0;
}
