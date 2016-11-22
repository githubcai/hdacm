#include <cstdio>
#include <cmath>

const int NMAX = 51, MMAX = 51, MAX = NMAX * MMAX;
const double EPS = 1e-8;
int N, M, K;
double city[MMAX][2], radar[NMAX][2], dist[NMAX][MMAX];

struct DLX{
    int n, m, size;
    int U[MAX], D[MAX], R[MAX], L[MAX], Row[MAX], Col[MAX];
    int H[NMAX];
    int S[MMAX];
    bool flag[MMAX];
    
    void init(int _n, int _m){
        n = _n, m = _m;
        for(int i = 0; i <= m; ++i){
            S[i] = 0;
            U[i] = D[i] = i;
            L[i] = i - 1;
            R[i] = i + 1;
        }
        R[m] = 0, L[0] = m;
        size = m;
        for(int i = 1; i <= n; ++i){
            H[i] = -1;
        }
    }

    void link(int r, int c){
        ++S[Col[++size] = c];
        Row[size] = r;
        D[size] = c;
        U[size] = U[c];
        U[D[size]] = size;
        D[U[size]] = size;
        if(H[r] < 0){
            H[r] = L[size] = R[size] = size;
        }else{
            R[size] = H[r];
            L[size] = L[H[r]];
            L[R[size]] = size;
            R[L[size]] = size;
        }
    }

    void remove(int c){
        for(int i = D[c]; i != c; i = D[i]){
            L[R[i]] = L[i], R[L[i]] = R[i];
        }
    }

    void resume(int c){
        for(int i = U[c]; i != c; i = U[i]){
            L[R[i]] = R[L[i]] = i;
        }
    }
    
    int getH(){
        int ret = 0;
        for(int c = R[0]; c != 0; c = R[c]) flag[c] = true;
        for(int c = R[0]; c != 0; c = R[c]){
            if(flag[c]){
                ++ret;
                flag[c] = false;
                for(int i = D[c]; i != c; i = D[i]){
                    for(int j = R[i]; j != i; j = R[j]){
                        flag[Col[j]] = false;
                    }
                }
            }
        }
        return ret;
    }

    bool dance(int d){
        if(d + getH() > K) return false;
        if(R[0] == 0) return true;
        int c = R[0];
        for(int i = R[0]; i != 0; i = R[i]){
            if(S[i] < S[c]) c = i;
        }
        for(int i = D[c]; i != c; i = D[i]){
            remove(i);
            for(int j = R[i]; j != i; j = R[j]) remove(j);
            if(dance(d + 1)) return true;
            for(int j = L[i]; j != i; j = L[j]) resume(j);
            resume(i);
        }
        return false;
    }
};

double distance(double x1, double y1, double x2, double y2){
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

void calDist(){
    for(int i = 1; i <= N; ++i){
        for(int j = 1; j <= M; ++j){
            dist[i][j] = distance(radar[i][0], radar[i][1], city[j][0], city[j][1]);
        }
    }
}

DLX dlx;
bool judge(double mid){
    dlx.init(N, M);
    for(int i = 1; i <= N; ++i){
        for(int j = 1; j <= M; ++j){
            if(mid - dist[i][j] >= EPS) dlx.link(i, j);
        }
    }
    return dlx.dance(0);
}

int main(){
    int T; scanf("%d", &T);
    while(T-- > 0){
        scanf("%d%d%d", &M, &N, &K);
        for(int i = 1; i <= M; ++i){
            scanf("%lf%lf", &city[i][0], &city[i][1]);
        }
        for(int i = 1; i <= N; ++i){
            scanf("%lf%lf", &radar[i][0], &radar[i][1]);
        }
        calDist();
        double left = 0, right = 1420;
        while(right - left >= EPS){
            double mid = (right + left) / 2;
            if(judge(mid)){
                right = mid;
            }else{
                left = mid;
            }
        }
        printf("%.6lf\n", left);
    }
    return 0;
}
