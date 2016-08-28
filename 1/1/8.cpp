#include <iostream>

using namespace std;

int main(){
    int a, b, N;
    bool flag = false;
    cin >> N;
    while(N--){
        int M, sum = 0, a;
        cin >> M;
        while(M--){
            cin >> a;
            sum += a;
        }

        if(flag){
            cout << endl;
        }else{
            flag = true;
        }
        cout << sum << endl;
    }
}
