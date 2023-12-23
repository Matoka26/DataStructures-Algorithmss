#include <iostream>
#include <map>
#include <vector>
#include <queue>
using namespace std;

bool coloringDfs(int node , vector<vector<int>>adjacency,vector<int>&colors){
    queue<int>q;
    q.push(node);
    colors[node] = 1;
    while(!q.empty()){

        int current = q.front();
        q.pop();
        for(int i = 0 ; i < adjacency[current].size() ; i++){
            int next = adjacency[current][i];
            if(colors[next] == -1){
                colors[next] = 1 - colors[current];
                q.push(next);
            }
            else
                if(colors[next] == colors[current])
                     return false;
        }

    }

    return true;
}


int main(){
    int n,m,v,w;
    cin>>n>>m;

    vector<vector<int>>adjacency(n+1);
    vector<pair<int,int>>edges(m);
    vector<int>colors(n+1,-1);

    for(int i = 0 ; i < m ; i++){
        cin>>v>>w;
        adjacency[v].push_back(w);
        adjacency[w].push_back(v);
        edges[i] = {v,w};
    }

    colors[1] = 0;
    if(coloringDfs(1,adjacency,colors)){
        cout<<"YES\n";
        for(int i = 0 ; i < edges.size() ; i++){
            if(colors[edges[i].first] == 0 && colors[edges[i].second] == 1)
                cout<<0;
            else
                cout<<1;
        }
    }
    else
        cout<<"NO";


}
