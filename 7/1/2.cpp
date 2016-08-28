#include <cstdio>

struct Node{
    double x, y;
};

struct Seg{
    Node a, b;
};

const int MAX = 100;
Seg segs[MAX];

double min(double a, double b){
    return a < b ? a : b;
}

double max(double a, double b){
    return a > b ? a : b;
}

bool judge(const Seg &n, const Seg &m){
    if(max(min(n.a.x, n.b.x), min(m.a.x, m.b.x)) > min(max(n.a.x, n.b.x), max(m.a.x, m.b.x)) ||
       max(min(n.a.y, n.b.y), min(m.a.y, m.b.y)) > min(max(n.a.y, n.b.y), max(m.a.y, m.b.y))){
        return false;
    }
    double v11, v12, v21, v22;
    v11 = (n.b.x - m.a.x) * (n.b.y - n.a.y) - (n.b.x - n.a.x) * (n.b.y - m.a.y);
    v12 = (n.b.x - m.b.x) * (n.b.y - n.a.y) - (n.b.x - n.a.x) * (n.b.y - m.b.y);
    v21 = (m.b.x - n.a.x) * (m.b.y - m.a.y) - (m.b.x - m.a.x) * (m.b.y - n.a.y);
    v22 = (m.b.x - n.b.x) * (m.b.y - m.a.y) - (m.b.x - m.a.x) * (m.b.y - n.b.y);
    return v11 * v12 <= 0 && v21 * v22 <= 0;
}

int main(){
    int N;
    while(scanf("%d", &N) == 1 && N != 0){
        for(int i = 0; i < N; ++i){
            scanf("%lf%lf%lf%lf", &segs[i].a.x, &segs[i].a.y, &segs[i].b.x, &segs[i].b.y);
        }
        int count = 0;
        for(int i = 0; i < N - 1; ++i){
            for(int j = i + 1; j < N; ++j){
                if(judge(segs[i], segs[j])) ++count;
            }
        }
        printf("%d\n", count);
    }
 return 0;
}
