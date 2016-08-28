#include <cmath>
#include <iostream>

using namespace std;

int main(){
    int N, T;
    cin >> T;
    while(T-- > 0){
        cin >> N;
        double a = N * log10(N);
        double b = a - static_cast<long long int>(a);
        double c = pow(10, b);
        long long int result = static_cast<long long int>(c);
        cout << result << endl;
    }
    return 0;
}
