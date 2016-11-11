#include <cstdio>
#include <cstring>

const int MAX = 200002;

int wa[MAX], wb[MAX], wv[MAX], ws[MAX];

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

int rank[MAX], height[MAX];
void calheight(char *r, int *sa, int n){
    int i, j, k = 0;
    for(i = 1; i <= n; ++i) rank[sa[i]] = i;
    for(i = 0; i < n; height[rank[i++]] = k){
        for(k ? k-- : 0, j = sa[rank[i] - 1]; r[i + k] == r[j + k]; ++k);
    }
    return;
}

int main(){
    char str1[MAX], str2[MAX / 2];
    int sa[MAX];
    while(scanf("%s%s", str1, str2) != EOF){
        int len, len1 = strlen(str1), len2 = strlen(str2);
        len = len1 + len2 + 1;
        str1[len1] = '$';
        for(int i = len1 + 1, j = 0; i <= len; ++i, ++j){
            str1[i] = str2[j];
        }

        da(str1, sa, len + 1, 123);
        calheight(str1, sa, len);
        int ans = 0;
        for(int i = 2; i <= len ; ++i){
            if(height[i] > ans && (sa[i - 1] <= len1  != sa[i] <= len1)) ans = height[i];
        }
        printf("%d\n", ans);
    }
    return 0;
}
