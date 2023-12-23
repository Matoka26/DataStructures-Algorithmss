#include <iostream>
#include <fstream>
#include <unordered_map>
using namespace std;
ifstream fin("loto.in");
ofstream fout("loto.out");

struct trio{
    int primu;
    int doilea;
    int treilea;
};


int main(){
    unordered_map<int,trio> tabel;
    long n,sum,check = 0;
    fin>>n>>sum;
    int numere[n];
    for(int i = 0 ; i < n ; i++)
        fin>>numere[i];

    for(int i = 0 ; i < n; i++){
        for(int j = 0 ; j < n ; j++){
            for(int k = 0 ; k < n ; k++){
                int suma = numere[i] + numere[j] + numere[k];
                tabel[suma] = {numere[i],numere[j],numere[k]};
                if(tabel.find(sum - suma) != tabel.end()){
                        check = 1;
                        fout<<numere[i]<<" "<<numere[j]<<" "<<numere[k]<<" "<<tabel[sum-suma].primu<<" "<<tabel[sum-suma].doilea<<" "<<tabel[sum-suma].treilea;
                        break;
                }
            }
            if(check)
                break;
        }
        if(check)
            break;
    }
    if(!check)
        fout<<-1;
fin.close();
fout.close();
return 0;
}
