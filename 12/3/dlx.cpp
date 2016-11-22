/* 精确覆盖 */
#include <cstdio>
using namespace std;

const int MAX = 100010, NMAX = 1010, MMAX = 1010;

struct DLX{
    int n, m, size;
    int U[MAX], D[MAX], R[MAX], L[MAX], Row[MAX], Col[MAX];
    int H[NMAX];//行头节点
    int S[MMAX];//每列有多少个节点
    int ansd, ans[NMAX];//如果有答案，则选了ansd行，具体是哪几行放在ans[ ]数组里面，ans[0~ansd-1];

    void init(int _n,int _m){
        n = _n, m = _m;
        for(int i = 0; i <= m; ++i){
            S[i] = 0;
            U[i] = D[i] = i;//初始状态下，上下自己指向自己
            L[i] = i - 1;
            R[i] = i + 1;
        }
        R[m] = 0, L[0] = m;
        size = m;//编号，每列都有一个头节点，编号1-m
        for(int i = 1; i <= n; ++i){
            H[i] = -1;//每一行的头节点
        }
    }

    void link(int r, int c){//第r行，第c列
        ++S[Col[++size] = c];//第size个节点所在的列为c,当前列的节点数++
        Row[size] = r;//第size个节点行位置为r
        D[size] = c;
        U[size] = U[c];
        U[D[size]] = size;
        D[U[size]] = size;
        if(H[r] < 0){
            H[r] = L[size] = R[size] = size;
        }else{
            R[size] = H[r];
            L[size] = L[H[r]];
            L[R[size]] = size;
            R[L[size]] = size;
        }
    }

    void remove(int c){//删除节点c，以及c上下节点所在的行,每次调用这个函数，都是从列头节点开始向下删除，这里c也可以理解为第c列, 因为第c列的列头节点编号为c
        L[R[c]] = L[c];
        R[L[c]] = R[c];
        for(int i = D[c]; i != c; i = D[i]){
            for(int j = R[i]; j != i; j = R[j]){
                U[D[j]] = U[j];
                D[U[j]] = D[j];
                --S[Col[j]];
            }
        }
    }

    void resume(int c){//恢复节点c,以及c上下节点所在的行(同上，也可以理解为从第c列的头节点开始恢复
        for(int i = U[c]; i != c; i = U[i]){
            for(int j = L[i]; j != i; j = L[j]){
                ++S[Col[U[D[j]] = D[U[j]] = j]];
            }
        }
        L[R[c]] = R[L[c]] = c;
    }

    bool dance(int d){//递归深度
        if(R[0] == 0){
            ansd = d;
            return true;
        }
        int c = R[0];
        for(int i = R[0]; i != 0; i = R[i]){
            if(S[i] < S[c]) c = i;
        }
        remove(c);//找到节点数最少的列，当前元素不是原图上0，1的节点，而是列头节点
        for(int i = D[c]; i != c; i = D[i]){
            ans[d] = Row[i];//列头节点下面的一个节点
            for(int j = R[i]; j != i; j = R[j]){
                remove(Col[j]);
            }
            if(dance(d + 1)) return true;
            for(int j = L[i]; j != i; j = L[j]){
                resume(Col[j]);
            }
        }
        resume(c);
        return false;
    }
};

DLX x;
int n, m;

int main(){
    while(scanf("%d%d", &n, &m) != EOF){
        x.init(n, m);
        for(int i = 1; i <= n; ++i){
            int cnt, j;
            scanf("%d", &cnt);
            while(cnt--){
                scanf("%d", &j);
                x.link(i, j);
            }
        }
        if(!x.dance(0)){
            printf("NO\n");
        }else{
            printf("%d", x.ansd);
            for(int i = 0; i < x.ansd; ++i){
                printf(" %d", x.ans[i]);
            }
            printf("\n");
        }
    }
    return 0;
}

