#include <iostream>

void afisare(long v[],long n){
    for(long i = 0 ; i < n ; i++ )
        std::cout<<v[i]<<" ";
    std::cout<<std::endl;
}

void bubbleSort(long v[] , long n){
    bool inv = 0 ;
    long aux;
    for(long i = 0 ; i < n-1 ; i++){
        inv = 0;
        for(long j = 0 ; j < n-i-1 ; j++){
            if(v[j] > v[j+1]){
                aux = v[j];
                v[j] = v[j+1];
                v[j+1] = aux;
                inv = 1;
            }
        }
        if(inv == 0)
            break;

    }
}

int main()
{long v[] = {5,32,6,35,1,8,5} , n = 7;
afisare(v,n);
bubbleSort(v,n);;
afisare(v,n);
}
