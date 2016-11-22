#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>

const int MAX = 17, SMAX = 65550, VMAX = 8000, NMAX = 400, MMAX = 17;
const double EPS = 1e-7;
struct Node{
    double x, y;
};

Node s[MAX];
int n, K, st[SMAX];
bool has[SMAX];
int dir[MAX]={1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536};

double distance(Node a, Node b){
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

Node whirl(double cosl, double sinl, Node a, Node b){
    b.x -= a.x, b.y -= a.y;
    Node c;
    c.x = b.x * cosl - b.y * sinl + a.x;
    c.y = b.x * sinl + b.y * cosl + a.y;
    return c;
}

Node inst(Node u1, Node u2, Node v1, Node v2){
    Node ans = u1;
    double t = ((u1.x - v1.x) * (v1.y - v2.y) - (u1.y - v1.y) * (v1.x - v2.x)) / 
               ((u1.x - u2.x) * (v1.y - v2.y) - (u1.y - u2.y) * (v1.x - v2.x));
    ans.x += (u2.x - u1.x) * t;
    ans.y += (u2.y - u1.y) * t;
    return ans;
}

Node fun(Node a, Node b, double r){
    double l = distance(a, b);
    double ans = acos((l / 2) / r);
    Node k1 = whirl(cos(ans), sin(ans), a, b);
    Node k2 = whirl(cos(ans), -sin(ans), b, a);
    Node cent = inst(a, k1, b, k2);
    return cent;
}

struct DLX{
    int n, m, size;
    int U[VMAX], D[VMAX], R[VMAX], L[VMAX], Row[VMAX], Col[VMAX];
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
        for(int i = 1; i <= n; ++i) H[i] = -1;
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

DLX dlx;

int main(){
    int T; scanf("%d", &T);
    while(T-- > 0){
        scanf("%d%d", &n, &K);
        for(int i = 1; i <= n; ++i){
            scanf("%lf%lf", &s[i].x, &s[i].y);
        }
        double left = 0, right = 7.1;
        while(right - left >= EPS){
            double mid = (left + right) / 2;
            int sum = 0;
            memset(has, 0, sizeof(has));
            for(int i = 1; i <= n; ++i){
                int bit = 0;
                for(int j = 1; j <= n; ++j){
                    if(distance(s[i], s[j]) <= mid){
                        bit += dir[j - 1];
                    }
                }
                if(!has[bit]){
                    has[bit] = true;
                    st[++sum] = bit;
                }
            }
            for(int i = 1; i <= n; ++i){
                for(int j = i + 1; j <= n; ++j){
                    double d = distance(s[i], s[j]);
                    if(d < 2 * mid){
                        Node a = {s[i].x, s[i].y}, b = {s[j].x, s[j].y};
                        Node cnt = fun(a, b, mid), cnt1;
                        double ansx = (a.x + b.x) / 2, ansy = (a.y + b.y) / 2;
                        cnt1.x = 2 * ansx - cnt.x;
                        cnt1.y = 2 * ansy - cnt.y;
                        int bit = 0;
                        for(int k = 0; k <= n; ++k){
                            if(k == i){
                                bit += dir[i - 1];
                                continue;
                            }
                            if(k == j){
                                bit += dir[j - 1];
                                continue;
                            }
                            if(distance(s[k], cnt) <= mid) bit += dir[k - 1];
                        }
                        if(!has[bit]){
                            has[bit] = true;
                            st[++sum] = bit;
                        }
                        bit = 0;
                        for(int k = 1; k <= n; ++k){
                            if(k == i){
                                bit += dir[i - 1];
                                continue;
                            }
                            if(k == j){
                                bit += dir[j - 1];
                                continue;
                            }
                            if(distance(s[k], cnt1) <= mid) bit += dir[k - 1];
                        }
                        if(!has[bit]){
                            has[bit] = true;
                            st[++sum] = bit;
                        }
                    }else if(d == 2 * mid){
                        Node cnt = {(s[i].x + s[j].x) / 2, (s[i].y + s[j].y) / 2};
                        int bit = 0;
                        for(int k = 1; k <= n; ++k){
                            if(k == i){
                                bit += dir[i - 1];
                                continue;
                            }
                            if(k == j){
                                bit += dir[j - 1];
                                continue;
                            }
                            if(distance(s[k], cnt) <= mid) bit += dir[k - 1];
                        }
                        if(!has[bit]){
                            has[bit] = true;
                            st[++sum] = bit;
                        }
                    }
                }
            }
            std::sort(st + 1, st + sum + 1);
            int r = 0;
            dlx.init(sum, n);
            for(int i = sum; i > 0; --i){
                for(int j = 1; j <= n; ++j){
                    if(st[i] & dir[j - 1]) has[st[i] - dir[j - 1]] = false;
                }
                if(!has[st[i]]) continue;
                ++r;
                for(int j = 1; j <= n; ++j){
                    if(st[i] & dir[j - 1]){
                        dlx.link(r, j);
                        has[dir[j - 1]] = false;
                    }
                }
            }
            if(dlx.dance(0)){
                right = mid;
            }else{
                left = mid;
            }
        }
        printf("%.6lf\n", left);
    }
    return 0;
}
