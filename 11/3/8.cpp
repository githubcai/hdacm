#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int MAX = 4, PMAX = 505;
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
char pstr[41];
int dp[11 * 11 * 11 * 11 + 1][PMAX];

int trs(char c){
    switch(c){
    case 'A': return 0;
    case 'T': return 1;
    case 'C': return 2;
    case 'G': return 3;
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
    ++trie[p].flag;
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
                trie[trie[temp].next[i]].flag += trie[trie[trie[temp].next[i]].fail].flag;
                que.push(trie[temp].next[i]);
            }else if(temp != 0){
                trie[temp].next[i] = trie[trie[temp].fail].next[i];
            }
        }
    }
}

int query(char *str){
    int bit[4], num[4];
    memset(num, 0, sizeof(num));
    for(int i = 0; str[i]; ++i){
        ++num[trs(str[i])];
    }
    bit[0] = (num[1] + 1) * (num[2] + 1) * (num[3] + 1);
    bit[1] = (num[2] + 1) * (num[3] + 1);
    bit[2] = num[3] + 1;
    bit[3] = 1;
    int totals = num[0] * bit[0] + num[1] * bit[1] + num[2] * bit[2] + num[3] * bit[3];
    for(int i = 0; i <= totals; ++i){
        for(int j = 0; j < cnts; ++j){
            dp[i][j] = -1;
        }
    }
    dp[0][0] = 0;
    for(int a = 0; a <= num[0]; ++a){
        for(int b = 0; b <= num[1]; ++b){
            for(int c = 0; c <= num[2]; ++c){
                for(int d = 0; d <= num[3]; ++d){
                    int temp = a * bit[0] + b * bit[1] + c * bit[2] + d;
                    for(int j = 0; j < cnts; ++j){
                        if(dp[temp][j] >= 0){
                            for(int k = 0; k < MAX; ++k){
                                if((k == 0 && a == num[0]) || (k == 1 && b == num[1]) || (k == 2 && c == num[2]) || (k == 3 && d == num[3]) || (temp + bit[k] > totals)) continue;
                                dp[temp + bit[k]][trie[j].next[k]] = max(dp[temp + bit[k]][trie[j].next[k]], dp[temp][j] + trie[trie[j].next[k]].flag);
                            }
                        }
                    }
                }
            }
        }
    }
    int ret = 0;
    for(int i = 0; i < cnts; ++i){
        ret = max(ret, dp[totals][i]);
    }
    return ret;
}

int main(){
    int N, Case = 1; char key[11];
    while(scanf("%d", &N) != EOF && N){
        cnts = 0; trie[cnts++].init();
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
