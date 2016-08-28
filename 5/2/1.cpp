#include <cstdlib>
#include <cstdio>

const int MAX = 26;

struct Trie{
    int num;
    Trie *next[MAX];
};

Trie *root;

void init(){
    root = (Trie*)malloc(sizeof(Trie));
    for(int i = 0; i < MAX; ++i){
        root->next[i] = NULL;
    }
    root->num = 0;
}

void insert(char *word){
    Trie *temp = root;
    ++root->num;
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
        ++temp->num;
        ++word;
    }
}

int search(char *word){
    Trie *temp = root;
    for(int i = 0; word[i] != '\0'; ++i){
        if(temp == NULL || temp->next[word[i] - 'a'] == NULL){
            return 0;
        }
        temp = temp->next[word[i] - 'a'];
    }
    return temp->num;
}

void del(Trie *cur){
    for(int i = 0; i < MAX; ++i){
        if(cur->next[i] != NULL){
            del(cur->next[i]);
        }
    }
    free(cur);
}

int main(){
    char word[11];
    init();
    while(scanf("%c", &word[0]) == 1 && word[0] != '\n'){
        int i;
        for(i = 0; word[i] != '\n';){
            scanf("%c", &word[++i]);
        }
        word[i] = '\0';
        insert(word);
    }
    while(scanf("%s", word) != EOF){
        printf("%d\n", search(word));
    }
    del(root);
    return 0;
}
