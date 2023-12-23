#include<iostream>
using namespace std;
void shellSort(long v[], long n)
{
    for (long gap = n/2; gap > 0; gap /= 2)
    {
        for (long i = gap; i < n; i += 1)
        {
            long aux = v[i];
            long j=i;    
            while(j >= gap && v[j - gap] > aux){
                v[j] = v[j - gap];
                j = j-gap;
            }
            v[j] = aux;
    }
}
}
void afisare(long arr[], long n)
{
    for (long i=0; i<n; i++)
        cout << arr[i] << " ";
}

int main(){

    long v[] = {13,4,13,7,2,52,54,43,3,545,14,4,41};
    long n = sizeof(v) / sizeof(long);
    shellSort(v,n);
    afisare(v,n);

}