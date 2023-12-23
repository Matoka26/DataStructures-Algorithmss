#include<iostream>
#include<fstream>
#include<vector>
#include<string.h>
#include<stack>
using std::cout;
std::ifstream fin("paranteze.in");
std::ofstream fout("paranteze.out");

int main(){
    std::stack<int>stiva;stiva.push(-1);
    std::vector<char>paranteze;

    long n,maxi = 0;

    fin>>n;
    for(int i = 0 ; i < n ; i++){
        char aux;
        fin>>aux;
        paranteze.push_back(aux);

    }
    for(int i = 0 ; i < n ; i++ ){
        if(strchr("([{",paranteze[i]))
            stiva.push(i);
        else
            if(!stiva.empty() && ((paranteze[i] == ')' && paranteze[stiva.top()] == '(') || (paranteze[i] == '}' && paranteze[stiva.top()] == '{') || (paranteze[i] == ']' && paranteze[stiva.top()] == '['))){
                    stiva.pop();
                    if(maxi < i - stiva.top()) maxi = i-stiva.top();
                    }
                else
                    stiva.push(i);

    }
fout<<maxi;
fin.close();
fout.close();
}
