#include <iostream>
using std::cout;

// Function to print the array.
void afisare(long v[],long n) {
    for (long i = 0 ; i < n ; i++) {
        cout<<v[i]<< " ";
    }
    cout<<'\n';
}

void interclasare(long *v,long left,long mij,long right) {
    long i=0, j=0, k=left;
    long lenSt = mij - left + 1;
    long lenDr = right - mij;

    long vecSt[lenSt], vecDr[lenDr];

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
}

void mergeSort(long *v, long left, long right) {
    if (left < right) {
        long mij = (left+right)/2;

        mergeSort(v, left, mij);
        mergeSort(v, mij + 1, right);

        interclasare(v, left, mij, right);
    }
}

int main()
{long v[] = {9,5,7,562,86,9,654,65},n = 8 ;

mergeSort(v, 0, n - 1);
afisare(v,n);

return 0;
}

