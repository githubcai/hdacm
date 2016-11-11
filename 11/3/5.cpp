#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int MAX = 26;
struct Node{
    Node *fail, *next[MAX];
    int count;
    Node(){
        fail = NULL;
        count = 0;
        memset(next, 0, sizeof(next));
    }
};

char pstr[1000001];

void insert(Node *root, char *str){
    Node *p = root;
    for(int i = 0; str[i]; ++i){
        int index = str[i] - 'a';
        if(p->next[index] == NULL) p->next[index] = new Node();
        p = p->next[index];
    }
    ++p->count;
}

void buildAC(Node *root){
    queue<Node*> que;
    root->fail = NULL;
    que.push(root);
    while(!que.empty()){
        Node *p, *temp = que.front();
        que.pop();
        for(int i = 0; i < 26; ++i){
            if(temp->next[i]){
                p = temp->fail;
                while(p){
                    if(p->next[i]){
                        temp->next[i]->fail = p->next[i];
                        break;
                    }
                    p = p->fail;
                }
                if(!p) temp->next[i]->fail = root;
                que.push(temp->next[i]);
            }
        }
    }
}

int query(Node *root, char *str){
    Node *p = root;
    int cnt = 0;
    for(int i = 0; str[i]; ++i){
        int index = str[i] - 'a';
        while(p != NULL && !p->next[index]) p = p->fail;
        p = (p == NULL) ? root : p->next[index];
        Node *temp = p;
        while(temp != root && temp->count != -1){
            cnt += temp->count;
            temp->count = -1;
            temp = temp->fail;
        }
    }
    return cnt;
}

void del(Node *cur){
    for(int i = 0; i < MAX; ++i){
        if(cur->next[i] != NULL){
            del(cur->next[i]);
        }
    }
    delete cur;
}

int main(){
    int T; scanf("%d", &T);
    char key[51];
    while(T--){
        int N; scanf("%d", &N);
        Node *root = new Node();
        for(int i = 0; i < N; ++i){
            scanf("%s", key);
            insert(root, key);
        }
        buildAC(root);
        scanf("%s", pstr);
        printf("%d\n", query(root, pstr));
        del(root);
    }
    return 0;
}
