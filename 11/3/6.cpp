#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

const int MAX = 4, INF = 0x7fffffff, NMAX = 1005;
int cnts;
struct Node{
    int fail, next[MAX];
    bool flag;
    void init(){
        flag = false;
        fail = -1;
        memset(next, 0, sizeof(next));
    }
};

char pstr[NMAX];
int dp[NMAX][NMAX];
Node trie[NMAX];

int trs(char c){
    switch(c){
    case 'A': return 0;
    case 'T': return 1;
    case 'G': return 2;
    case 'C': return 3;
    }
}

void insert(char *str){
    int p = 0;
    for(int i = 0; str[i]; ++i){
        int index = trs(str[i]);
        if(!trie[p].next[index]){
            trie[cnts].init();
            trie[p].next[index] = cnts++;
        }
        p = trie[p].next[index];
    }
    trie[p].flag = true;
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

int query(char *str){
    int slen = strlen(str);
    for(int i = 0; i <= slen; ++i){
        for(int j = 0; j < cnts; ++j){
            dp[i][j] = INF;
        }
    }
    dp[0][0] = 0;
    for(int i = 0; i < slen; ++i){
        for(int j = 0; j < cnts; ++j){
            if(dp[i][j] == INF) continue;
            if(trie[j].flag) continue;
            for(int k = 0; k < MAX; ++k){
                int t = trie[j].next[k];
                if(trie[t].flag) continue;
                dp[i + 1][t] = min(dp[i + 1][t], dp[i][j] + ((trs(str[i]) != k) ? 1 : 0));
            }
        }
    }
    int ans = INF;
    for(int i = 0; i < cnts; ++i){
        if(dp[slen][i] < ans) ans = dp[slen][i];
    }
    if(ans == INF){
        return -1;
    }else{
        return ans;
    }
}

int main(){
    char key[21];
    int N, Case = 1;
    while(scanf("%d", &N) != EOF && N){
        cnts = 0;
        trie[0].init();
        ++cnts;
        for(int i = 0; i < N; ++i){
            scanf("%s", key);
            insert(key);
        }
        buildAC();
        scanf("%s", pstr);
        printf("Case %d: ", Case++);
        printf("%d\n", query(pstr));
    }
    return 0;
}
