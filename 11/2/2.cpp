#include <cstdio>
#include <cstring>
#include <cmath>

const int MAX = 100001;
int wa[MAX], wb[MAX], wv[MAX], ws[MAX];
int rank[MAX], height[MAX];
int dp[MAX][20];
char str[MAX];

bool cmp(int *r, int a, int b, int l){
    return r[a] == r[b] && r[a + l] == r[b + l];
}

void da(char *r, int *sa, int n, int m){
    int i, j, p, *x = wa, *y = wb, *t;
    for(i = 0; i < m; ++i) ws[i] = 0;
    for(i = 0; i < n; ++i) ++ws[x[i] = r[i]];
    for(i = 1; i < m; ++i) ws[i] += ws[i - 1];
    for(i = n - 1; i >= 0; --i) sa[--ws[x[i]]] = i;

    for(j = 1, p = 1; p < n; j *= 2, m = p){
        for(p = 0, i = n - j; i < n; ++i) y[p++] = i;
        for(i = 0; i < n; ++i) if(sa[i] >= j) y[p++] = sa[i] - j;
        for(i = 0; i < n; ++i) wv[i] = x[y[i]];

        for(i = 0; i < m; ++i) ws[i] = 0;
        for(i = 0; i < n; ++i) ++ws[wv[i]];
        for(i = 1; i < m; ++i) ws[i] += ws[i - 1];
        for(i = n - 1; i >= 0; --i) sa[--ws[wv[i]]] = y[i];

        for(t = x, x = y, y = t, p = 1, x[sa[0]] = 0, i = 1; i < n; ++i){
            x[sa[i]] = cmp(y, sa[i - 1], sa[i], j) ? p - 1 : p++;
        }
    }
    return;
}

void calHeight(char *r, int *sa, int n){
    int i, j, k = 0;
    for(i = 1; i <= n; ++i) rank[sa[i]] = i;
    for(i = 0; i < n; height[rank[i++]] = k){
        for(k ? k-- : 0, j = sa[rank[i] - 1]; r[i + k] == r[j + k]; ++k);
    }
    return;
}

int min(int x, int y){
    return x < y ? x : y;
}

void RMQ(int num){
    for(int i = 1; i <= num; ++i){
        dp[i][0] = height[i];
    }
    for(int j = 1; j < 20; ++j){
        for(int i = 1; i <= num; ++i){
            if(i + (1 << j) - 1 <= num){
                dp[i][j] = min(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]);
            }
        }
    }
}

int lcp(int x, int y){
    int temp;
    x = rank[x], y = rank[y];
    if(x > y){
        temp = x; 
        x = y;
        y = temp;
    }
    ++x;
    temp = (int)((log(y - x + 1)) / (log(2.0)));
    return min(dp[x][temp], dp[y - (1 << temp) + 1][temp]);
}

void solve(int len){
    int ll, num, t, p, mx = 1, f = 1, node = 1;
    for(int i = 1; i <= len / 2; ++i){
        for(int j = 0; j + i < len; j += i){
            if(str[j] != str[j + i]) continue;
            ll = lcp(j, j + i);
            num = ll / i + 1;
            p = j;
            t =  i - ll % i;
            int cnt = 0;
            for(int k = j - 1; k >= 0 && k + i > j && str[k] == str[k + i]; --k){
                ++cnt;
                if(cnt == t){
                    ++num;
                    p = k;
                }else if(rank[k] < rank[p]){
                    p = k;
                }
            }
            if(mx < num){
                f = p;
                mx = num;
                node = i;
            }else if(mx == num && rank[f] > rank[p]){
                f = p;
                node = i;
            }
        }
    }
    if(mx == 1){
        char mn = 'z' + 1;
        for(int i = 0; i < len; ++i){
            if(str[i] < mn) mn = str[i];
        }
        printf("%c\n", mn);
    }else{
        for(int i = f; i < f + mx * node; ++i){
            printf("%c", str[i]);
        }
        printf("\n");
    }
}

int main(){
    int sa[MAX], Case = 1;
    while(scanf("%s", str) != EOF && str[0] != '#'){
        int len = strlen(str);
        int dp[MAX][20];
        da(str, sa, len + 1, 123);
        calHeight(str, sa, len);
        RMQ(len);
        printf("Case %d: ", Case++);
        solve(len);
    }
    return 0;
}
