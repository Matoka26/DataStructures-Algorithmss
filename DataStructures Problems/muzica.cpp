#include <iostream>
#include <fstream>
#include <unordered_set>

using namespace std;
ifstream fin("muzica.in");
ofstream fout("muzica.out");


int main(){
    long long n,m,a,b,c,d,e,mel,curent;
    fin>>n>>m>>a>>b>>c>>d>>e;
    unordered_set<long long> v;

    for(int i = 0 ; i < n ; i++){
        fin>>mel;
        v.insert(mel);
    }

    long long c1 = a ,c2 = b ,counter = 0;
    if(v.find(c1) != v.end()){
        v.erase(c1);
        counter++;
    }
    if(v.find(c2) != v.end()){
        v.erase(c2);
        counter++;
        }
    for(int i = 0 ; i < m-2 ; i++){
        curent = (c*c2 + d*c1) % e;
       // cout<<curent<<" ";

        if(v.find(curent) != v.end()){
            v.erase(curent);
            counter++;
        }
        c1 = c2;
        c2 = curent;
    }
    //cout<<endl;
   // for(auto it = v.begin() ; it!=v.end() ; it++)
     //   cout<<*it<<" ";

    fout<<counter;

fin.close();
fout.close();
return 0;
}
