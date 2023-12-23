#include <iostream>

void afisare(long v[],long n){
    for(long i = 0 ; i < n ; i++ )
        std::cout<<v[i]<<" ";
}

void countsort(long v[],long n){
    long maximul = 0,j=0;
    for(long i = 0 ; i < n ; i++ )
        if( v[i] > maximul)
            maximul = v[i];

    long counter[maximul+1];

    for(long i = 0 ; i <= maximul ; i++)
        counter[i] = 0;

    for(long i = 0 ; i < n ; i++)
        counter[v[i]]++;

    for(long i =0 ; i <= maximul ; i++)
        if(counter[i] != 0){
            for(long k = 0; k < counter[i] ; k++)
                {v[j] = i;
                j++;
                }
        }
}

int main(){
long v[]={4,654,3,5,4,3145,57,5,4,4,65,6,0},n=13;

countsort(v,n);
afisare(v,n);
return 0;
}
