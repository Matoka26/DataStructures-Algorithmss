#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
using namespace std;
ifstream fin("hashuri.in");
ofstream fout("hashuri.out");

vector<int>v[666103];

vector<int>::iterator cautare(int nr,int rest){
    vector<int>::iterator i;
    for(i = v[rest].begin() ; i != v[rest].end() ; i++)
        if(*i == nr)
            return i;
    return v[rest].end();
}

void inserare(int nr,int rest){
    if(cautare(nr,rest) == v[rest].end())
        v[rest].push_back(nr);
}
void stergere(int nr,int rest){
    vector<int>::iterator poz = cautare(nr,rest);
    if(poz != v[rest].end())
        v[rest].erase(poz);
}
int main(){

    int n,k,nr;
    fin>>n;
    for(int i = 0 ; i < n ; i++){
        fin>>k>>nr;
        int mod = nr%666103;
        switch(k){
            case 1:
                inserare(nr,mod);
                break;

            case 2:
                stergere(nr,mod);
                break;

            case 3:
                if(cautare(nr,mod) != v[mod].end()) fout<<"1\n";
                else fout<<"0\n";
                break;
        }
    }

fin.close();
fout.close();
return 0;
}
