#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int MAX = 26, PMAX = 110, NMAX = 26;
int cnts;
struct Node{
    int fail, next[MAX];
    int flag;
    void init(){
        flag = 0;
        fail = -1;
        memset(next, 0, sizeof(next));
    }
};

Node trie[PMAX];
char pstr[NMAX];
int dp[NMAX][PMAX][1 << 10 + 1];

void insert(char *str, int m){
    int p = 0;
    for(int i = 0; str[i]; ++i){
        int index = str[i] - 'a';
        if(!trie[p].next[index]){
            trie[cnts].init();
            trie[p].next[index] = cnts++;
        }
        p = trie[p].next[index];
    }
    trie[p].flag = 1 << m;
}

void buildAC(){
    queue<int> que;
    que.push(0);
    while(!que.empty()){
        int temp = que.front();
        que.pop();
        for(int i = 0; i < MAX; ++i){
            if(trie[temp].next[i]){
                int p = trie[temp].fail;
                while(p != -1){
                    if(trie[p].next[i]){
                        trie[trie[temp].next[i]].fail = trie[p].next[i];
                        break;
                    }
                    p = trie[p].fail;
                }
                if(p == -1) trie[trie[temp].next[i]].fail = 0;
                trie[trie[temp].next[i]].flag |= trie[trie[trie[temp].next[i]].fail].flag;
                que.push(trie[temp].next[i]);
            }else if(temp != 0){
                trie[temp].next[i] = trie[trie[temp].fail].next[i];
            }
        }
    }
}

int query(int n, int m, int l){
    int limit = 1 << m;
    for(int i = 0; i <= n; ++i ){
        for(int j = 0; j < cnts; ++j){
            for(int k = 0; k <= limit; ++k){
                dp[i][j][k] = 0;
            }
        }
    }
    dp[0][0][0] = 1;
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < cnts; ++j){
            for(int k = 0; k <= limit; ++k){
                if(dp[i][j][k]){
                    for(int d = 0; d < MAX; ++d){
                        int temp = trie[j].next[d];
                        int state = k | trie[temp].flag;
                        dp[i + 1][temp][state] += dp[i][j][k];
                        dp[i + 1][temp][state] %= 20090717;
                    }
                }
            }
        }
    }
    int ret = 0;
    for(int i = 0; i < cnts; ++i){
        for(int j = 0; j <= limit; ++j){
            int temp = 0, t = j;
            while(t){
                if(t & 1) ++temp;
                t >>= 1;
            }
            if(temp >= l) ret = (ret + dp[n][i][j]) % 20090717;
        }
    }
    return ret;
}

int main(){
    int n, m, k;
    char key[11];
    while(scanf("%d%d%d", &n, &m, &k) != EOF && (n || m || k)){
        cnts = 0; trie[cnts++].init();
        for(int i = 0;  i < m; ++i){
            scanf("%s", key);
            insert(key, i);
        }
        buildAC();
        printf("%d\n", query(n, m, k));
    }
    return 0;
}
