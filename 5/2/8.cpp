#include <cstdlib>
#include <cstdio>
#include <queue>
#include <vector>
using namespace std;

struct HTreeNode{
    int Freq;
    HTreeNode *Left, *Right;
};

struct cmp{
    bool operator()(HTreeNode *a, HTreeNode *b){
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
        HT = (HTreeNode*)malloc(sizeof(HTreeNode));
        HT->Freq = left->Freq + right->Freq;
        HT->Left = left, HT->Right = right;
        que.push(HT);
    }
    HT = que.top();
    return HT;
}

int WeightPathLength(HTreeNode *HT, int len){
    if(HT == NULL) return 0;
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
    int n;
    scanf("%d", &n);
    while(n-- > 0){
        int m;
        scanf("%d", &m);
        char str[1000];
        scanf("%s", str);
        int a[26] = {0};
        for(int i = 0; '\0' != str[i]; ++i){
            ++a[str[i] - 'a'];
        }
        int len = 0;
        for(int i = 0; i < 26; ++i){
            if(a[i] != 0){
                a[len++] = a[i];
            }
        }
        int result;
        if(len > 1){
            HTreeNode *HT = CreateHufTree(a, len);
            result = WeightPathLength(HT, 0);
            DestroyHufTree(HT);
        }else{
            result = a[0];
        }
        if(result <= m){
            printf("yes\n");
        }else{
            printf("no\n");
        }
    }
    return 0;
}
