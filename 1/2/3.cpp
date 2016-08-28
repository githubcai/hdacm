#include <iostream>

using namespace std;

const unsigned int MAX = 50;
unsigned int his[MAX];

int main(){
    unsigned int n, cnt = 0;
    while(cin >> n, n != 0){
        unsigned int sum = 0;
        for(int i = 0; i < n; ++i){
            cin >> his[i];
            sum += his[i];
        }
        unsigned int avg = sum / n , result = 0;
        for(int i = 0; i < n; ++i){
            if(his[i] > avg){
                result += (his[i] - avg);
            }
        }
        ++cnt;
        cout << "Set #" << cnt << endl;
        cout << "The minimum number of moves is " << result << "." << endl << endl;
    }
    return 0;
}
