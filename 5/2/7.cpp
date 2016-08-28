#include <cstdlib>
#include <cstdio>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;

struct HTreeNode{
    int Freq;
    HTreeNode *Left, *Right;
};

struct cmp{
    bool operator()(HTreeNode* a, HTreeNode* b){
        return a->Freq > b->Freq;
    }
};

HTreeNode* CreateHufTree(int *a, int n){
    HTreeNode *HT, *left, *right;
    priority_queue<HTreeNode*, vector<HTreeNode*>, cmp> que;
    for(int i = 0; i < n; ++i){
        HT = (HTreeNode*)malloc(sizeof(HTreeNode));
        HT->Freq = a[i];
        HT->Left = HT->Right = NULL;
        que.push(HT);
    }
    while(que.size() > 1){
        left = que.top(), que.pop();
        right = que.top(), que.pop();
        HT= (HTreeNode*)malloc(sizeof(HTreeNode));
        HT->Freq = left->Freq + right->Freq;
        HT->Left = left, HT->Right = right;
        que.push(HT);
    }
    HT = que.top();
    return HT;
}

int WeightPathLength(HTreeNode *HT, int len){
    if(NULL == HT) return 0;
    if(NULL == HT->Left && NULL == HT->Right){
        return HT->Freq * len;
    }
    return WeightPathLength(HT->Left, len + 1) + WeightPathLength(HT->Right, len + 1);
}

void DestroyHufTree(HTreeNode *HT){
    if(NULL == HT) return;
    DestroyHufTree(HT->Left);
    DestroyHufTree(HT->Right);
    free(HT);
}

int main(){
    char str[1000];
    while(true){
        scanf("%s", str);
        if(strcmp(str, "END") == 0) break;
        int len, a[27] = {0};
        for(int i = 0; str[i] != '\0'; ++i){
            if(str[i] == '_'){
                ++a[26];
            }else{
                ++a[str[i] - 'A'];
            }
        }
        len = 0;
        for(int i = 0; i < 27; ++i){
            if(a[i] != 0){
                a[len++] = a[i];
            }
        }
        int a1 = strlen(str) * 8, a2;
        float a3;
        if(len > 1){
            HTreeNode *root = CreateHufTree(a, len);
            a2 = WeightPathLength(root, 0);
            DestroyHufTree(root);
        }else{
            a2 = a[0];
        }
        a3 = a1 * 1.0 / a2;
        printf("%d %d %.1f\n", a1, a2, a3);
    }
    return 0;
}
