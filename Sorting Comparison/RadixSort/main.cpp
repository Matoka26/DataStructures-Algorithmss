#include <iostream>
#include <cmath>
//using namespace std;
void afisare(long v[],long n){
    for(long i = 0 ; i < n ; i++ )
        std::cout<<v[i]<<" ";
    std::cout<<std::endl;
}


void puneZero(long v[] , long n){
    for(long i = 0; i < n ; i++)
        v[i] = 0;
}
long nrMaxim(long v[] , long n){
    long maxim = 0;
    for(long i = 0; i < n ; i++)
        if(maxim < v[i])
            maxim = v[i];
    return maxim;
}
long cateCifre(long n){
    long counter = 0;
    while(n){
        counter++;
        n = n/10;
    }
    return counter;
}
void numara(long v[] , long n,long exp){
    long counter[10], aux[n];
    exp = pow(10,exp);
    puneZero(counter,10);
    for(long i = 0 ; i < n ; i++)
        counter[(v[i]/exp)%10]++;

    counter[0]--;
    for(long i = 1 ; i < 10 ; i++)
        counter[i] += counter[i-1];

    for(long i = n-1 ; i >= 0 ; i--){
        aux[counter[(v[i]/exp)%10]] = v[i];
        counter[(v[i]/exp)%10]--;
    }


    for(long i = 0 ; i < n ; i++){
        v[i] = aux[i];
    }
}

void radixSort(long v[] , long n){
    long aux[n];
    long nrPasi = cateCifre(nrMaxim(v,n));
    for(long i = 0 ; i < nrPasi ; i++){
        puneZero(aux,n);
        numara(v,n,i);
    }

}



int main()
{long v[] = {10,9,8,7,6,5,4,3,2,1},n = 10;
radixSort(v,n);
afisare(v,n);

}
