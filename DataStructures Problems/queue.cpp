#include<iostream>
#include<fstream>
#include<stack>
#include<strings.h>
using namespace std;
ifstream fin("queue.in");
ofstream fout("queue.out");


int main(){
    int n,wr;
    stack<int>s1,s2;
    fin>>n;
    string instr;
    getline(fin,instr);
    for(int i = 0 ; i < n ; i++){
        getline(fin,instr);
        if(instr[1] == 'u'){
            wr = stoi(instr.substr(10,instr.size()-2-9));
            s1.push(wr);
            fout<<i+1<<": read("<<wr<<") push(1,"<<wr<<")\n";
        }
        if(instr[1] == 'o'){
            if(!s2.empty()){
                wr = s2.top();
                s2.pop();
                fout<<i+1<<": pop(2) write("<<wr<<")\n";
            }
            else{
                if(s1.size() > 1)
                    fout<<i+1<<": ";
                while(s1.size() > 1) {
                    wr = s1.top();
                    s1.pop();
                    s2.push(wr);
                    fout<<"pop(1) push(2,"<<wr<<") ";
                }
                wr = s1.top();
                s1.pop();
                fout<<"pop(1) write("<<wr<<") ";
                fout<<'\n';
            }
        }
    }
fin.close();
fout.close();
}
