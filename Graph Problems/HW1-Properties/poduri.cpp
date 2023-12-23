#include<iostream>
#include<vector>
#include<queue>
using namespace std;


class Solution {
private:
    void markFirstIsland(vector<vector<int>>& grid, pair<int,int>start, vector<vector<bool>>&visited);
    queue<pair<int,int>> layer(vector<vector<int>>& grid ,queue<pair<int,int>>&q,vector<vector<bool>>&visited);
public:
    int shortestBridge(vector<vector<int>>& grid);


};
void Solution::markFirstIsland(vector<vector<int>>& grid, pair<int,int>start,vector<vector<bool>>&visited){
        int i = start.first;
        int j = start.second;
        //dreapta

        if( j  < grid.size() -1 && j >= 0 && grid[i][j+1] &&!visited[i][j+1] ){
            visited[i][j+1] = 1;
            markFirstIsland(grid,{i,j+1},visited);
        }
        //stanga
        if( j  > 0 && j < grid.size() && grid[i][j-1]  && !visited[i][j-1] ){
            visited[i][j-1] = 1;
            markFirstIsland(grid,{i,j-1},visited);
        }
        //jos
        if( i < grid.size() -1 && i >= 0 && grid[i+1][j]  && !visited[i+1][j] ){
            visited[i+1][j] = 1;
            markFirstIsland(grid,{i+1,j},visited);
        }
        //sus
        if( i > 0 && i < grid.size() && grid[i-1][j]  && !visited[i-1][j] ){
            visited[i-1][j] = 1;
            markFirstIsland(grid,{i-1,j},visited);
        }
        return;

    }
///after marking the first island
///this function returns a queue with the
///nodes at the same distance from the first island
///each layer is 1+ distance from the previous one
queue<pair<int,int>> Solution::layer(vector<vector<int>>& grid ,queue<pair<int,int>>&q,vector<vector<bool>>&visited){
        queue<pair<int,int>>newQ;
        while(!q.empty()){
            int i = q.front().first;
            int j = q.front().second;
            q.pop();

            if( j  < grid.size() -1 && j >= 0 && !visited[i][j+1] ){
                if( !grid[i][j+1] ){
                    visited[i][j+1] = 1;
                    newQ.push({i,j+1});
                }
                else
                    return queue<pair<int,int>>();
            }
            if( j  > 0 && j < grid.size() && !visited[i][j-1] ){
                if( !grid[i][j-1] ){
                    visited[i][j-1] = 1;
                    newQ.push({i,j-1});
                }
                else
                    return queue<pair<int,int>>();
            }

            if( i < grid.size() -1 && i >= 0 && !visited[i+1][j] ){
                if( !grid[i+1][j] ){
                    visited[i+1][j] = 1;
                    newQ.push({i+1,j});
                }
                else
                    return queue<pair<int,int>>();

            }
            if(i > 0 && i < grid.size() && !visited[i-1][j] ){
                if( !grid[i-1][j]){
                    visited[i-1][j] = 1;
                    newQ.push({i-1,j});
                }
                else
                    return queue<pair<int,int>>();
            }

        }
        return newQ;
}

int Solution::shortestBridge(vector<vector<int>>& grid) {
        vector<vector<bool>>visited;
        ///keep a visited matrix
        for(int i = 0 ; i < grid.size() ; i++){
            visited.push_back({});
            for(int j = 0 ; j < grid.size() ; j++)
                visited[i].push_back(0);
        }

        ///look for the first 1
        pair<int,int> startPosition;
        bool found = false;
        for(int i = 0 ; i < grid.size() ; i++)
            for(int j = 0 ; j < grid.size() ; j++)
                if(grid[i][j] && !found){
                    startPosition.first = i;
                    startPosition.second = j;
                    found = true;
                }

        ///mark the first one found
        visited[startPosition.first][startPosition.second] = 1;

        ///mark the first island
        markFirstIsland(grid,startPosition,visited);

        queue<pair<int,int>> q;
        for(int i = 0 ; i < grid.size() ; i++)
            for(int j = 0 ; j < grid.size() ; j++)
                if(visited[i][j])
                    q.push({i,j});

        int cnt = -1;
        while(!q.empty()){
            q = layer(grid,q,visited);
            cnt++;
        }
        return cnt;


}


int main(){
vector<vector<int>>g1 ={{1,1,1,1,1},{1,0,0,0,1},{1,0,1,0,1},{1,0,0,0,1},{1,1,1,1,1}},
                    g2 = {{0,1,0},{0,0,0},{0,0,1}},
                    g3 = {{1,1,1,1,1},{1,0,0,0,1},{1,0,1,0,1},{1,0,0,0,1},{1,1,1,1,1}};
Solution rez;
cout<<rez.shortestBridge(g2)<<endl;


}
