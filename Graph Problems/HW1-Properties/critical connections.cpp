#include <iostream>
#include <vector>
using namespace std;

class Solution {
private:

    ///keep track of its level and the lowest level it can get to
    void dfs(int node,int parent,vector<int>adjacencyList[],vector<bool>&visited,vector<int>&minLvl,vector<int>&level,vector<vector<int>>&result,int& step){
        ///update the current node's info
        visited[node] = true;
        minLvl[node] =  step + 1;
        level[node] = step + 1;
        step++;

        for(int i = 0 ; i < adjacencyList[node].size() ; i++){
            int nextNode = adjacencyList[node][i];
            ///if the neighbour isnt visited
            if(nextNode != parent){
                if(!visited[nextNode]){
                    ///the neighbour is 1 step away from current
                    level[nextNode] = level[node] + 1;
                    dfs(nextNode,node , adjacencyList , visited , minLvl , level,result,step);
                    ///update node's value
                    minLvl[node] = min(minLvl[node] , minLvl[nextNode]);
                    ///test if the neighbour went lower than the node
                    if(minLvl[nextNode] > level[node])
                        result.push_back({node,nextNode});
                }
                else
                ///upeate if the vertex node-nextNode is for return
                    if(level[nextNode] < level[node] - 1)
                        minLvl[node] = min(minLvl[node] , level[nextNode]);
            }
        }
    }
public:

    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        vector<int>adjacencyList[n];
        vector<bool>visited(n);
        vector<int>minLvl(n);
        vector<int>level(n);
        vector<vector<int>>result;
        int step = 0;

        for(int i = 0 ; i < connections.size() ; i++){
            adjacencyList[connections[i][0]].push_back(connections[i][1]);
            adjacencyList[connections[i][1]].push_back(connections[i][0]);
        }


        level[0] = 0;
        dfs(0,-1,adjacencyList,visited,minLvl,level,result,step);

        return result;
    }
};
int main(){
    vector<vector<int>>g = {{0,1},{1,2},{2,0},{1,3}};

    Solution s;
    vector<vector<int>> results = s.criticalConnections(4,g);
    cout<<results.size();


    return 0;
}
