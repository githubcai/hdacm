#include <cstdio>
#include <algorithm>
using namespace std;

const int MAX = 50005;
int wa[MAX], wb[MAX], wv[MAX], ws[MAX];
int rk[MAX], height[MAX];
int pos;

bool cmp(int *r, int a, int b, int l){
    return r[a] == r[b] && r[a + l] == r[b + l];
}

void da(int *r, int *sa, int n, int m){
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
}

void calHeight(int *r, int *sa, int n){
    int i, j, k = 0;
    for(i = 1; i <= n; ++i) rk[sa[i]] = i;
    for(i = 0; i < n; height[rk[i++]] = k){
        for(k ? k-- : 0, j = sa[rk[i] - 1]; r[i + k] == r[j + k]; ++k);
    }
}

int findNum(int num, int n, int *ref){
    int left = 1, right = n;
    while(left < right){
        int mid = (left + right) >> 1;
        if(ref[mid] == num){
            return mid;
        }else if(ref[mid] > num){
            right = mid - 1;
        }else{
            left = mid + 1;
        }
    }
    return left;
}

bool judge(int *que, int rear, int k, int mid){
    sort(que, que + rear);
    int pre = que[0], cnt = 1;
    for(int i = 1; i < rear; ++i){
        if(que[i] - pre >= mid){
            ++cnt;
            pre = que[i];
        }
    }
    if(cnt >= k) return true;
    return false;
}

bool check(int mid, int *sa, int n, int k){
    int que[MAX], rear = 0;
    que[rear++] = sa[1];
    for(int i = 2; i <= n; ++i){
        if(height[i] >= mid){
            que[rear++] = sa[i];
        }else{
            if(judge(que, rear, k, mid)){
                pos = que[0];
                return true;
            }
            rear = 0;
            que[rear++] = sa[i];
        }
    }
    if(judge(que, rear, k, mid)){
        pos = que[0];
        return true;
    }
    return false;
}

int main(){
    int input[MAX], ref[MAX], sa[MAX], T, N, K;
    scanf("%d", &T);
    bool flag = true;
    while(T-- > 0){
        scanf("%d%d", &N, &K);
        for(int i = 0; i < N; ++i){
            scanf("%d", &input[i]);
            ref[i + 1] = input[i];
        }
        sort(ref + 1, ref + N + 1);
        int cnt = 1;
        for(int i = 2; i <= N; ++i){
            if(ref[cnt] != ref[i]) ref[++cnt] = ref[i];
        }
        for(int i = 0; i < N; ++i){
            input[i] = findNum(input[i], cnt, ref);
        }
        input[N] = 0;
        da(input, sa, N + 1, cnt + 1);
        calHeight(input, sa, N);
        int left = 1, right = N, ans = 1;
        while(left <= right){
            int mid = (left + right) >> 1;
            if(check(mid, sa, N, K)){
                left = mid + 1;
                ans = mid;
            }else{
                right = mid - 1;
            }
        }
        if(flag){
            flag = false;
        }else{
            printf("\n");
        }
        printf("%d\n", ans);
        for(int i = 0; i < ans; ++i){
            printf("%d\n", ref[input[i + pos]]);
        }
    }
    return 0;
}
