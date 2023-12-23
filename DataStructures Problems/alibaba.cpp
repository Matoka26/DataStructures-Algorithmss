#include<iostream>
#include<fstream>
#include<stack>
#include<vector>
using std::cout;
std::ifstream fin("alibaba.in");
std::ofstream fout("alibaba.out");

int main(){
    std::stack<char> stiva,stivaAux;
    std::vector<char>cifre;
    int n,k;

    fin>>n>>k;
    for(int i = 0 ; i < n ; i++){
        char cifra;
        fin>>cifra;
        cifre.push_back(cifra);

    }

    for(int i = 0 ; i < n ; i++){
        while(!stiva.empty() && cifre[i] > stiva.top() && k > 0){
            stiva.pop();
            k--;
        }
        stiva.push(cifre[i]);
    }
    while(k){
        stiva.pop();
        k--;
    }

while(!stiva.empty()){
    stivaAux.push(stiva.top());
    stiva.pop();
}
while(!stivaAux.empty()){
    fout<<stivaAux.top();
    stivaAux.pop();
}

fin.close();
fout.close();
}
