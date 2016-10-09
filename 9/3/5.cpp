#include <cstdio>
#include <cstdlib>
#include <vector>
#include <map>
#include <cstring>
using namespace std;

const int MAX = 26;
struct Trie{
    int num;
    Trie *next[MAX];
};

Trie *root;
char input[105], result[105], tresult[105];
map<int, vector<char>> store;
int maxProb;

void saveKey(){
    store[2].push_back('a'), store[2].push_back('b'), store[2].push_back('c');
    store[3].push_back('d'), store[3].push_back('e'), store[3].push_back('f');
    store[4].push_back('g'), store[4].push_back('h'), store[4].push_back('i');
    store[5].push_back('j'), store[5].push_back('k'), store[5].push_back('l');
    store[6].push_back('m'), store[6].push_back('n'), store[6].push_back('o');
    store[7].push_back('p'), store[7].push_back('q'), store[7].push_back('r'), store[7].push_back('s');
    store[8].push_back('t'), store[8].push_back('u'), store[8].push_back('v');
    store[9].push_back('w'), store[9].push_back('x'), store[9].push_back('y'), store[9].push_back('z');
}

void init(){
    root = (Trie*)malloc(sizeof(Trie));
    for(int i = 0; i < MAX; ++i){
        root->next[i] = NULL;
    }
    root->num = 0;
}

void insert(char *word, int prob){
    Trie *temp = root;
    while(*word != '\0'){
        if(temp->next[*word - 'a'] == NULL){
            Trie *cur = (Trie*)malloc(sizeof(Trie));
            for(int i = 0; i < MAX; ++i){
                cur->next[i] = NULL;
            }
            cur->num = 0;
            temp->next[*word - 'a'] = cur;
        }
        temp = temp->next[*word - 'a'];
        temp->num += prob;
        ++word;
    }
}

void del(Trie *cur){
    for(int i = 0; i < MAX; ++i){
        if(cur->next[i] != NULL){
            del(cur->next[i]);
        }
    }
    free(cur);
}

void dfs(int cur, int leng, Trie *r){
    if(cur == leng){
        if(r->num > maxProb){
            tresult[cur] = '\0';
            strcpy(result, tresult);
            maxProb = r->num;
        }
        return;
    }
    int temp = input[cur] - '0';
    for(auto iter = store[temp].begin(); iter != store[temp].end(); ++iter){
        if(r->next[*iter - 'a'] != NULL){
            tresult[cur] = *iter;
            dfs(cur + 1, leng, r->next[*iter - 'a']);
        }
    }
}

int main(){
    saveKey();
    int T; scanf("%d", &T);
    int cnt = 1;
    while(T-- > 0){
        printf("Scenario #%d:\n", cnt++);
        init();
        int m; scanf("%d", &m);
        for(int i = 0; i < m; ++i){
            int prob; scanf("%s%d", input, &prob);
            insert(input, prob);
        }
        scanf("%d", &m);
        for(int i = 0; i < m; ++i){
            scanf("%s", input);
            int leng = strlen(input);
            for(int i = 1; i < leng; ++i){
                maxProb = -1;
                dfs(0, i, root);
                if(maxProb == -1){
                    printf("MANUALLY\n");
                }else{
                    printf("%s\n", result);
                }
            }
            printf("\n");
        }
        del(root);
        printf("\n");
    }
    return 0;
}
