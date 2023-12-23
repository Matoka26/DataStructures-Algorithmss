#include <iostream>
#include <fstream>
#include <queue>
using namespace std;
ifstream fin("proc2.in");
ofstream fout("proc2.out");

int main(){
    priority_queue<int,vector<int>,greater<int>>proc;
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>q;
    int nr,taskuri,s,d;
    fin>>nr>>taskuri;
    for(int i = 0 ; i < taskuri ; i++)
        proc.push(i+1);

    for(int i = 0 ; i < taskuri ; i++){
        fin>>s>>d;
        while(!q.empty() && q.top().first <= s){
            proc.push(q.top().second);
            q.pop();
        }
        q.push({s+d,proc.top()});
        fout<<proc.top()<<endl;
        proc.pop();
    }

fin.close();
fout.close();
return 0;
}
