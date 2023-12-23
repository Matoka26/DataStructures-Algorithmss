#include<iostream>
#include<fstream>
#include<unordered_map>
using namespace std;
ifstream fin("pariuri.in");
ofstream fout("pariuri.out");

int main(){
    int n,k,bani,timp;
    unordered_map<int,int> dic;
    fin>>n;
    for(int i = 0 ; i < n ; i++){
        fin>>k;
        for(int j = 0 ; j < k ; j++){
            fin>>timp>>bani;
            dic[timp] += bani;
        }
    }
    fout<<dic.size()<<endl;
    for(auto x : dic)
        fout<<x.first<<" "<<x.second<<" ";

fin.close();
fout.close();
}
