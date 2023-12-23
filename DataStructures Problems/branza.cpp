#include <iostream>
#include <fstream>
#include <deque>

using namespace std;
ifstream fin("branza.in");
ofstream fout("branza.out");

struct Sapt{
    int index;
    long long pret;
    long long buc;
    Sapt(int i,long p,long b){index = i,pret=p;buc=b;}
};

int main(){
    deque<Sapt>dec;
    int n,s,t;
    fin>>n>>s>>t;
    long pret,buc,bani = 0;

    for(int i = 0 ; i < n ; i++){
        fin>>pret>>buc;

        if(!dec.empty() && dec.front().index < i-t)     //daca ii trece termenu ceaw
            dec.pop_front();
        while(!dec.empty() && (s*(i-dec.back().index) +dec.back().pret) >= pret)    //daca nu i worth s o tin ceaw
            dec.pop_back();

        dec.push_back({i,pret,buc});

        bani = bani+ s*buc*(i - dec.front().index) +buc*dec.front().pret; //cat am cheltuit deja + cat ma costa sa o depozitez + cat ma costa s o fac

    }
fout<<bani;
fin.close();
fout.close();
}
