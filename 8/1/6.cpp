#include <string>
#include <queue>
#include <iostream>
using namespace std;

struct Node{
    string name;
    int pri, pra, id;
    friend bool operator<(const Node &a, const Node &b){
        if(a.pri == b.pri) return a.id > b.id;
        return a.pri > b.pri;
    }
};

int main(){
    string comm, name;
    int id = 0, pri, pra;
    priority_queue<Node> que;
    while(cin >> comm){
        if(comm == "GET"){
            if(que.empty()){
                cout << "EMPTY QUEUE!" << endl;
            }else{
                Node p = que.top();
                que.pop();
                cout << p.name << " " << p.pra << endl;
            }
        }else{
            cin >> name >> pra >> pri;
            Node p = {name, pri, pra, id++};
            que.push(p);
        }
    }
    return 0;
}
