#include <iostream>

using namespace std;

int main(){
    int N;
    while(cin >> N, N){
        int req, sum = 0, now = 0;
        while(N--){
            cin >> req;
            if(req >= now){
                sum += (req - now) * 6;
            }else{
                sum += (now - req) * 4;
            }
            sum += 5;
            now = req;
        }
        cout << sum << endl;
    }
}
