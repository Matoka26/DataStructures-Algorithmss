#include<iostream>
#include<vector>
#include<queue>
#include<cmath>
//#include<fstream>
using namespace std;
//ifstream f("ns.in");


vector<long> bfs(vector<vector<long>>adiacenta, long nod){
    queue<long>q;
    vector<long>dist(adiacenta.size()+1,-1);
    dist[nod] = 0;
    q.push(nod);
    while(!q.empty()){
        long nodCurent = q.front();
        q.pop();
        for(long i = 0 ; i < adiacenta[nodCurent].size() ; i++){
            long nodNou = adiacenta[nodCurent][i];
            if(dist[nodNou] == -1){
                dist[nodNou] = dist[nodCurent] + 1;
                q.push(nodNou);
            }
        }
    }
    return dist;

}


long testCase(long nrNoduri , long nrSpeciale){
    vector<long>speciale;
    vector<vector<long>>adiacenta(nrNoduri+1);
    ///citire date
    long aux;
    for(long i = 0 ; i < nrSpeciale ; i++){
        cin>>aux;
        speciale.push_back(aux);
    }
    for(long i = 0 ; i < nrNoduri - 1 ; i++){
        long a,b;
        cin>>a>>b;
        adiacenta[a].push_back(b);
        adiacenta[b].push_back(a);
    }
    if(nrSpeciale == 1)
        return 0;

    ///bfs pe un nod random
    vector<long> dist = bfs(adiacenta,1);


    long celMaiDeparte;
    float maximul = 0;
    ///cautam cel mai departe nod marcat de la alesu random
    for(long i = 0 ; i < speciale.size() ; i++)
        if(dist[speciale[i]] > maximul){
            maximul = dist[speciale[i]];
            celMaiDeparte = speciale[i];
        }


    dist = bfs(adiacenta,celMaiDeparte);
    maximul = 0;
    for(long i = 0 ; i < speciale.size(); i++)
        if(dist[speciale[i]] > maximul)
            maximul = dist[speciale[i]];

    return (maximul+1)/2;
}

int main(){
    long nrTests;
    cin>>nrTests;
    for(long test = 0 ; test < nrTests ; test++){
        long nr1,nr2;
        cin>>nr1>>nr2;
        cout<<testCase(nr1,nr2)<<endl;
    }

//f.close();

}
