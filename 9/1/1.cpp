#include <cstdio>
#include <cstring>

const int MAX = 1000000;

int main(){
    char A[MAX], B[MAX];
    while(scanf("%s%s", A, B) != EOF){
        char oA = '+', oB = '+';
        int Al = strlen(A), Bl = strlen(B);
        if(A[0] == '+' || A[0] == '-'){
            oA = A[0];
            A[0] = '0';
        }
        if(B[0] == '+' || B[0] == '-'){
            oB = B[0];
            B[0] = '0';
        }

        int iA, iB;
        for(iA = 0; iA < Al; ++iA){
            if(A[iA] == '.') break;
        }
        for(iB = 0; iB < Bl; ++iB){
            if(B[iB] == '.') break;
        }
        int tA = iA - 1, tB = iB - 1;
        bool result = true;
        for(; tA >= 0 && tB >= 0; --tA, --tB){
            if(A[tA] != B[tB]){
                result = false;
                break;
            }
        }
        if(result){
            if(tA >= 0){
                while(tA >= 0){
                    if(A[tA] != '0'){
                        result = false;
                        break;
                    }
                    --tA;
                }
            }else if(tB >= 0){
                while(tB >= 0){
                    if(B[tB] != '0'){
                        result = false;
                        break;
                    }
                    --tB;
                }
            }
        }
        if(result){
            tA = iA + 1, tB = iB + 1;
            for(; tA < Al && tB < Bl; ++tA, ++tB){
                if(A[tA] != B[tB]){
                    result = false;
                    break;
                }
            }
            if(result){
                if(tA < Al){
                    while(tA < Al){
                        if(A[tA] != '0'){
                            result = false;
                            break;
                        }
                        ++tA;
                    }
                }else if(tB < Bl){
                    while(tB < Bl){
                        if(B[tB] != '0'){
                            result = false;
                            break;
                        }
                        ++tB;
                    }
                }
            }
        }
        if(result){
            printf("YES\n");
        }else{
            printf("NO\n");
        }
    }
    return 0;
}
