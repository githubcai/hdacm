#include <cstdio>
#include <cstring>
#include <map>
#include <vector>
using namespace std;

const int MAX = 20001;
int father[MAX], Rank[MAX], N;

void init(){
    for(int i = 0; i < MAX; ++i){
        father[i] = i;
    }
    memset(Rank, 0, sizeof(Rank));
}

int find(int x){
    if(x == father[x]) return x;
    int temp = father[x];
    father[x] = find(temp);
    Rank[x] ^= Rank[temp];
    return father[x];
}

bool merge(int a, int b, int v){
    int ar = find(a), br = find(b);
    if(ar != br){
        if(ar == N){
            father[br] = ar;
            Rank[br] = Rank[a] ^ Rank[b] ^ v;
        }else{
            father[ar] = br;
            Rank[ar] = Rank[a] ^ Rank[b] ^ v;
        }
    }else{
        return (Rank[a] ^ Rank[b]) == v;
    }
    return true;
}

int main(){
    int Q, cnt = 1;
    while(scanf("%d%d", &N, &Q) == 2){
        if(N == 0 && Q == 0) break;
        printf("Case %d:\n", cnt++);
        init();
        bool flag = true;
        char comm[2];
        int p, q, v, k, conflict = 0;
        for(int i = 0; i < Q; ++i){
            scanf("%s", comm);
            if(comm[0] == 'I'){
                scanf("%d%d", &p, &q);
                char temp; scanf("%c", &temp);
                if(temp == ' '){
                    scanf("%d", &v);
                    if(flag){
                        flag = merge(p, q, v);
                        ++conflict;
                        if(!flag){
                            printf("The first %d facts are conflicting.\n", conflict);
                        }
                    }
                }else{
                    if(flag){
                        flag = merge(p, N, q);
                        ++conflict;
                        if(!flag){
                            printf("The first %d facts are conflicting.\n", conflict);
                        }
                    }
                }
            }else{
                int k; scanf("%d", &k);
                map<int, vector<int> > store;
                for(int j = 0; j < k; ++j){
                    int temp; scanf("%d", &temp);
                    int r = find(temp);
                    store[r].push_back(temp);
                }
                if(flag){
                    bool tempFlag = true;
                    int result = 0;
                    for(auto iter = store.begin(); iter != store.end(); ++iter){
                        int size = (iter->second).size();
                        if(iter->first != N && size % 2 == 1){
                            tempFlag = false;
                            break;
                        }
                        if(iter->first == N){
                            for(int i = 0; i < size; ++i){
                                result ^= Rank[(iter->second)[i]];
                            }
                        }else{
                            for(int i = 0; i < size; i += 2){
                                result ^= Rank[(iter->second)[i]] ^ Rank[(iter->second)[i + 1]];
                            }
                        }
                    }
                    if(!tempFlag){
                        printf("I don't know.\n");
                    }else{
                        printf("%d\n", result);
                    }
                }
            }
        }
        printf("\n");
    }
    return 0;
}
