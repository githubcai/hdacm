#include <iostream>
#include <stack>
#include <queue>
#include <string>
using namespace std;

int main(){
    int T, n;
    string comm;
    cin >> T;
    while(T-- > 0){
        cin >> n >> comm;
        string ts; int ti;
        if(comm == "FIFO"){
            queue<int> que;
            for(int i = 0; i < n; ++i){
                cin >> ts;
                if(ts == "IN"){
                    cin >> ti;
                    que.push(ti);
                }else{
                    if(!que.empty()){
                        int temp = que.front();
                        que.pop();
                        cout << temp << endl;
                    }else{
                        cout << "None" << endl;;
                    }
                }
            }
        }else{
            stack<int> st;
            for(int i = 0; i < n; ++i){
                cin >> ts;
                if(ts == "IN"){
                    cin >> ti;
                    st.push(ti);
                }else{
                    if(!st.empty()){
                        int temp = st.top();
                        st.pop();
                        cout << temp << endl;
                    }else{
                        cout << "None" << endl;
                    }
                }
            }
        }
    }
    return 0;
}
