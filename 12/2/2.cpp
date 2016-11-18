#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

const int MAX = 19;

char s[MAX], t[MAX];
int pt[MAX + 1];
bool smove[1 << MAX];
vector<int> edge[MAX][MAX];
queue<int> que[2];
bool vis[2][1 << MAX];

void ins(char *dest, int n, int i, int j){
    if(strstr(s, dest) != NULL){
        smove[(pt[j - i + 1] - 1) << i] = true;
    }else{
        reverse(dest, dest + n);
        if(strstr(s, dest) != NULL){
            smove[(pt[j - i + 1] - 1) << i] = true;
        }
        reverse(dest, dest + n);
    }
}

vector<int> match(char *dest, int n, int lent){
    vector<int> ret;
    for(int i = 0; i + n - 1 < lent; ++i){
        int v = (pt[n] - 1) << i;
        char *pos = strstr(&t[i], dest);
        if(pos == &t[i]){
            ret.push_back(v);
        }else{
            reverse(dest, dest + n);
            pos = strstr(&t[i], dest);
            if(pos == &t[i]){
                ret.push_back(v);
            }
            reverse(dest, dest + n);
        }
    }
    return ret;
}

bool bfs(int x, int n){
    int full = (1 << n) - 1;
    int size = que[x].size();
    while(size-- > 0){
        int now = que[x].front();
        que[x].pop();
        for(int i = 0; i < n; ++i){
            for(int j = i; j < n; ++j){
                if(((1 << j) & now) == (x ^ 1)) break;
                int v = (pt[j - i + 1] - 1) << i;
                if(!smove[v]) break;
                v = ((x == 0) ? (v | now) : (v ^ now));
                if(vis[x ^ 1][v]) return true;
                if(vis[x][v]) continue;
                vis[x][v] = true;
                que[x].push(v);
            }
        }
        for(int i = 0; i < n; ++i){
            for(int j = i; j < n; ++j){
                if(((1 << j) & now) == 0) break;
                for(int k = 0; k < edge[i][j].size(); ++k){
                    int v = edge[i][j][k];
                    if(v & ((pt[j - i + 1] - 1) << i)) continue;
                    if(x == 0 && (v & now) == 0){
                        v |= now;
                    }else if(x == 1 && (v & now) == v){
                        v ^= now;
                    }else{
                        continue;
                    }
                    if(vis[x ^ 1][v]) return true;
                    if(vis[x][v]) continue;
                    vis[x][v] = true;
                    que[x].push(v);
                }
            }
        }
    }
}

int dbfs(int n){
    int full = (1 << n) - 1;
    for(int i = 0; i < 2; ++i){
        memset(vis[i], 0, sizeof(bool) * ((1 << n) + 3));
        while(!que[i].empty()) que[i].pop();
    }
    que[0].push(0); que[1].push(full);
    vis[0][0] = true; vis[1][full] = true;
    int step = 0;
    while(!que[0].empty() || !que[1].empty()){
        ++step;
        if(step & 1){
            if(bfs(0, n)) return step;
        }else{
            if(bfs(1, n)) return step;
        }
    }
    return -1;
}

bool check(int lens, int lent){
    bool ext[128] = {false};
    for(int i = 0; i < lens; ++i) ext[s[i]] = true;
    for(int i = 0; i < lent; ++i){
        if(!ext[t[i]]) return false;
    }
    return true;
}

int main(){
    int T; scanf("%d", &T);
    pt[0] = 1;
    for(int i = 1; i <= MAX; ++i) pt[i] = pt[i - 1] * 2;
    while(T-- > 0){
        scanf("%s%s", s, t);
        int lens = strlen(s), lent = strlen(t);
        if(!check(lens, lent)){
            printf("impossible\n");
            continue;
        }
        memset(smove, 0, sizeof(bool) * ((1 << lent) + 3));
        char temp[MAX];
        for(int i = 0; i < lent; ++i){
            int k = 0;
            for(int j = i; j < lent; ++j){
                temp[k] = t[j]; ++k; temp[k] = 0;
                ins(temp, k, i, j);
                edge[i][j] = match(temp, k, lent);
            }
        }
        int ans = dbfs(lent);
        if(ans == -1){
            printf("impossible\n");
        }else{
            printf("%d\n", ans);
        }
    }
    return 0;
}
