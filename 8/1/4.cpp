#include <queue>
#include <iostream>
using namespace std;

struct Node{
    int pri, id;
    friend bool operator<(const Node &a, const Node &b){
        if(a.pri == b.pri) return a.id > b.id;
        return a.pri < b.pri;
    }
};

int main(){
    int N, A, B;
    string comm;
    while(cin >> N){
        priority_queue<Node> que[3];
        int cnt = 1;
        for(int i = 0; i < N; ++i){
            cin >> comm >> A;
            if(comm == "IN"){
                cin >> B;
                Node p= {B, cnt++};
                que[A - 1].push(p);
            }else{
                if(!que[A - 1].empty()){
                    Node temp = que[A - 1].top();
                    que[A - 1].pop();
                    cout << temp.id <<endl;
                }else{
                    cout << "EMPTY" << endl;
                }
            }
        }
    }
    return 0;
}
