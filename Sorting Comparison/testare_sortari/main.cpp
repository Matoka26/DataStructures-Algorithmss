#include<bits/stdc++.h>
using namespace std;
using namespace std::chrono;

void afisare(long v[],long n){
    for(long i = 0 ; i < n ; i++ )
        cout<<v[i]<<" ";
    cout<<endl;
}

///RadixSort baza 10
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
    long counter[10];
    long *aux = new long[n];
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

    delete[] aux;
}
void radixSort(long v[] , long n){
    long *aux = new long[n];
    long nrPasi = cateCifre(nrMaxim(v,n));
    for(int i = 0 ; i < nrPasi ; i++){
        puneZero(aux,n);
        numara(v,n,i);
    }
    delete[] aux;
}
//

///BubbleSort
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
//

///CountSort
void countSort(long v[],long n){
    long maximul = 0,j=0;
    for(long i = 0 ; i < n ; i++ )
        if( v[i] > maximul)
            maximul = v[i];

    long *counter = new long[maximul+1];

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
    delete[] counter;
}
//


///MergeSort
void interclasare(long *v,long left,long mij,long right) {
    long i=0, j=0, k=left;
    long lenSt = mij - left + 1;
    long lenDr = right - mij;

    long *vecSt = new long[lenSt];
    long *vecDr = new long[lenDr];

    for (long a = 0; a < lenSt; a++) {
        vecSt[a] = v[left + a];
    }
    for (long a = 0; a < lenDr; a++) {
        vecDr[a] = v[mij + 1 + a];
    }

    while (i< lenSt && j < lenDr) {
        if (vecSt[i] <= vecDr[j])
            v[k++] = vecSt[i++];
         else
            v[k++] = vecDr[j++];

    }

    while (i < lenSt)
        v[k++] = vecSt[i++];

    while (j < lenDr)
        v[k++] = vecDr[j++];

    delete[] vecSt;
    delete[] vecDr;
}
void mergeSort(long *v, long left, long right) {
    if (left < right) {
        long mij = (left+right)/2;

        mergeSort(v, left, mij);
        mergeSort(v, mij + 1, right);

        interclasare(v, left, mij, right);
    }
}
//

///ShellSort
void shellSort(long v[], long n)
{
    for (int gap = n/2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i += 1)
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
///declarare
/*int n = 8;      ///puterea lui 10 de elemente
    int putereExp = 8;  ///cate cifre sa aibe numarul
    long nrElemente = pow(10,n);
   long *v = new long[nrElemente];
*/
int main(){
/*
    long exp = pow(10,putereExp);
    random_device rd;
    default_random_engine generator(rd());
    uniform_int_distribution<long long unsigned> distribution(0,0xFFFFFFFFFFFFFFFF);

    for (int i = 0; i < nrElemente; i++)
          v[i] = distribution(generator)%exp;
*/

int nrElemente;
cout<<"n = ";cin>>nrElemente;
long *v = new long[nrElemente];
for(int i = 0 ; i < nrElemente ; i++){
    cin>>v[i];
}

        //auto start = high_resolution_clock::now();
    mergeSort(v,0,nrElemente-1);
    //bubbleSort(v,nrElemente);
    //radixSort(v,nrElemente);
    //shellSort(v,nrElemente);
    //countSort(v,nrElemente);
    //sort(v,v+nrElemente);
      //  auto stop = high_resolution_clock::now();
    //afisare(v,nrElemente);
    //auto duration = duration_cast<microseconds>(stop - start);
    //cout<<"Time: "<<duration.count();  //microsec
afisare(v,nrElemente);
    delete[] v;

      return 0;


}
