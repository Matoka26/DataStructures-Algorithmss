#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <queue>
#include <algorithm>
#include <exception>
#include <string>
#include "edge.h"
using std::map;
using std::stack;
using std::vector;
using std::queue;
using std::pair;
using std::ostream;
using std::string;
using std::deque;

class OrientedGraph{
public:
    ///attributes
    map<int,vector<int>> adjacencyList;
    vector<Edge>         edges;
    vector<int>          nodes;

public:
    ///empty graph
    OrientedGraph();
    ///builds the graph from a list of adjacency
    OrientedGraph(map<int,vector<int>> adjacency);
    OrientedGraph(vector<vector<int>> adjacency);

    ///add a new edge
    virtual void newEdge(Edge edg);
    virtual void newEdge(int v, int w);
    virtual void newEdge(int v, int w, int weight);

    ///add new node
    void newNode(int node);
    ///remove edges
    void removeEdge(Edge edg);
    void removeEdge(int v , int w, int weight);
    //void removeNode(int node); not yet fixed
    ///number of vertexes
    int size();
    bool empty();
    vector<int> getNodes();
    friend ostream& operator<<(ostream& out, const OrientedGraph& gr);
    int nodeOutDegree(int node);
    int nodeInDegree(int node);
    vector<int> getAdjOfNode(int node);
    ///returns empty set if the graph is empty
    vector<int> dfs(int node);
    vector<int> bfs(int node);

    ///Solutions
    vector<int> topologicalSort();
    vector<int> eventualSafeStates();
};


OrientedGraph::OrientedGraph(){
    this->adjacencyList = {};
    this->edges = {};
    this->nodes = {};
}

OrientedGraph::OrientedGraph(map<int,vector<int>> adjacency){
    this->adjacencyList = adjacency;

    for(auto it = adjacency.begin() ; it != adjacency.end() ; it++){
        vector<int>tempList = it->second;
        this->nodes.push_back(it->first);

        for(int i = 0 ; i < tempList.size(); i++)
            this->edges.push_back({it->first , tempList[i]});

    }
}
OrientedGraph::OrientedGraph(vector<vector<int>> adjacency){
    ///copy the whole list in the map and note the nodes
    for(int i = 0 ; i < adjacency.size() ; i++){
        for(int j = 0 ; j < adjacency[i].size() ; j++){
            this->adjacencyList[i].push_back(adjacency[i][j]);
            this->edges.push_back({i,adjacency[i][j]});
        }
        this->nodes.push_back(i);
    }


}
void OrientedGraph::newEdge(Edge edg){
        ///if the reffered vertexes are not contained
        ///in the graph,add them to nodes
        bool checkV = false , checkW = false;
        for(int i = 0 ; i < nodes.size() ; i++){
            if(edg.from == nodes[i])
                checkV = true;
            if(edg.to == nodes[i])
                checkW = true;
        }
        if(!checkV)
            nodes.push_back(edg.from);
        if(!checkW)
            nodes.push_back(edg.to);

        this->adjacencyList[edg.from].push_back(edg.to);
        this->edges.push_back(edg);
}
void OrientedGraph::newEdge(int v, int w){
    ///if the reffered vertexes are not contained
        ///in the graph,add them to nodes
    ///not sure to return error if the edges dont
    ///yet exist or add them so i add them idk
        bool checkV = false , checkW = false;
        for(int i = 0 ; i < nodes.size() ; i++){
            if(v == nodes[i])
                checkV = true;
            if(w == nodes[i])
                checkW = true;
        }
        if(!checkV)
            nodes.push_back(v);
        if(!checkW)
            nodes.push_back(w);

    this->adjacencyList[v].push_back(w);
    this->edges.push_back({v,w});
}

void OrientedGraph::newEdge(int v, int w, int weight){
    ///if the reffered vertexes are not contained
        ///in the graph,add them to nodes
    ///not sure to return error if the edges dont
    ///yet exist or add them so i add them idk
        bool checkV = false , checkW = false;
        for(int i = 0 ; i < nodes.size() ; i++){
            if(v == nodes[i])
                checkV = true;
            if(w == nodes[i])
                checkW = true;
        }
        if(!checkV)
            nodes.push_back(v);
        if(!checkW)
            nodes.push_back(w);

    this->adjacencyList[v].push_back(w);
    this->edges.push_back({v,w,weight});
}

vector<int> OrientedGraph::getNodes(){
    vector<int> result;
    for(int i = 0 ; i < this->nodes.size() ; i++)
        result.push_back(this->nodes[i]);
    return result;
}

int OrientedGraph::size(){
    return this->nodes.size();
}
bool OrientedGraph::empty(){
    return size() == 0;
}

void OrientedGraph::removeEdge(Edge edg){
    bool checkEdg = false;
    ///check if the reffered edge is containted
    ///and delete that edge from edges vector
    for(int i = 0 ; i < this->edges.size() ; i++){
        if(edges[i] == edg){
            checkEdg = true;
            edges.erase(edges.begin() + i);
        }
    }
    if(!checkEdg)
        return;
    ///delete the ref from the adj list
    for(int i = 0 ; i < this->adjacencyList[edg.from].size() ; i++)
        if(adjacencyList[edg.from][i] == edg.to)
            adjacencyList[edg.from].erase(adjacencyList[edg.from].begin() + i);

}
void OrientedGraph::removeEdge(int v , int w , int weight){
    bool checkEdg = false;
    ///check if the reffered edge is containted
    ///and delete that edge from edges vector
    for(int i = 0 ; i < this->edges.size() ; i++){
        if(edges[i].from == v && edges[i].to == w && edges[i].weight == weight){
            checkEdg = true;
            edges.erase(edges.begin() + i);
        }
    }
    if(!checkEdg)
        return;
    ///delete the ref from the adj list

    for(int i = 0 ; i < this->adjacencyList[v].size() ; i++)
        if(adjacencyList[v][i] == w)
            adjacencyList[v].erase(adjacencyList[v].begin() + i);

}
/*
void OrientedGraph::removeNode(int node){
    bool checkNode = false;
    ///check if the reffered node is containted
    ///and delete from the nodes vector
    for(int i = 0 ; i < this->nodes.size() ; i++)
        if(nodes[i] == node){
            checkNode = true;
            nodes.erase(nodes.begin() + i);
            break;
        }
    if(!checkNode)
        return;

    ///delete node's adjacency
    for(auto it = this->adjacencyList.begin() ; it != this->adjacencyList.end() ; it++)
        if(it->first == node){
            adjacencyList.erase(it);
            break;
        }

    ///delete all edges
    for(int i = 0 ; i < this->edges.size() ; i++){
        ///if we find an edge with that node
        if(edges[i].from == node){
            ///look in the adjList of the other node and delete the refferece from there
            for(int j = 0 ; j < this->adjacencyList[edges[i].to].size() ; j++){
                if(adjacencyList[edges[i].to][j] == node);
                    adjacencyList[edges[i].to].erase(adjacencyList[edges[i].to].begin() + j );
            }
            ///delete the edge from the edge list
            edges.erase(edges.begin() + i);
        }
        if(edges[i].to == node){
            for(int j = 0 ; j < this->adjacencyList[edges[i].from].size() ; j++){
                if(adjacencyList[edges[i].from][j] == node);
                    adjacencyList[edges[i].from].erase(adjacencyList[edges[i].from].begin() + j );
                }
            edges.erase(edges.begin() + i);
        }
    }


}
*/
void OrientedGraph::newNode(int node){
    ///if the reffered node already exists exit
    for(int i = 0 ; i < this->nodes.size() ; i++)
        if(nodes[i] == node)
            return;

    nodes.push_back(node);
    adjacencyList[node] = {};

}

ostream& operator<<(ostream& out, const OrientedGraph& gr){
    for(int i = 0 ; i < gr.edges.size() ; i++)
        out<<gr.edges[i]<<'\n';
    return out;
}

    ///not sure if it should return 0 if the node
    ///is not contained or an error so i guess 0
int OrientedGraph::nodeOutDegree(int node){
    return adjacencyList[node].size();
}

int OrientedGraph::nodeInDegree(int node){
    int countEdges = 0;
    ///count the number of times an edge is
    ///incident to that node
    for(int i = 0 ; i < this->edges.size() ; i++)
        if(edges[i].to == node)
            countEdges++;
    return countEdges;
}

vector<int> OrientedGraph::getAdjOfNode(int node){
    bool checkNode = false;
    for(int i = 0 ; i < this->nodes.size() ; i++)
        if(nodes[i] == node)
            checkNode = true;
    if(checkNode)
        return this->adjacencyList[node];
    else
        throw badNode;
}


vector<int> OrientedGraph::dfs(int node){
    ///if size = 0 the graph is empty
    if(!size()) return {};

    vector<int>     result;
    map<int,bool>   visited;
    ///check if the given node is valid

    bool checkIfContained = false;
    for(int i = 0 ; i < this->nodes.size() ; i++)
        if(nodes[i] == node)
            checkIfContained = true;
    if(!checkIfContained)
        throw badNode;

    ///mark all nodes as unvisited
    for(int i = 0 ; i < this->nodes.size() ; i++)
        visited[nodes[i]] = false;

    ///put the reffered node in stack to begin with
    stack<int> nextToVisit;
    nextToVisit.push(node);


    while(!nextToVisit.empty()){

        ///take the current node out
        int current = nextToVisit.top();
        nextToVisit.pop();

        ///if the node is not visited add it to the solution
        ///and mark it as visited
        if(!visited[current]){
            visited[current] = true;
            result.push_back(current);
        }
        ///put all of current's node neighbours in stack
        for(int i = 0 ; i < this->adjacencyList[current].size() ; i++)
            if(!visited[adjacencyList[current][i]])
                nextToVisit.push(adjacencyList[current][i]);
    }
    return result;
}

vector<int> OrientedGraph::bfs(int node){
    ///if size = 0 the graph is empty
    if(!size()) return {};

    vector<int>     result;
    map<int,bool>   visited;
    ///check if the given node is valid

    bool checkIfContained = false;
    for(int i = 0 ; i < this->nodes.size() ; i++)
        if(nodes[i] == node)
            checkIfContained = true;
    if(!checkIfContained)
        throw badNode;

    queue<int>q;
    q.push(node);

    while(!q.empty()){

        ///take out the current node and add to solution and mark it visited
        int current = q.front();
        q.pop();
        visited[current] = true;
        result.push_back(current);
        ///push the neighbours if they havent been visited
        for(int i = 0 ; i < this->adjacencyList[current].size() ; i++)
            if(!visited[adjacencyList[current][i]])
                q.push(adjacencyList[current][i]);

    }

    return result;
}

vector<int> OrientedGraph::topologicalSort(){
    vector<int> result;
    map<int,int> inDegrees;
    ///make a list of all in degrees
    for(int i = 0 ; i < size() ; i++)
        inDegrees[nodes[i]] = nodeInDegree(nodes[i]);

    ///start from the nodes with no nodes coming in
    queue<int> q;
    for(int i = 0 ; i < size() ; i++)
        if(!inDegrees[nodes[i]])
            q.push(nodes[i]);

    while(!q.empty()){
        ///take out the node and add to solution
        int current = q.front();
        q.pop();
        result.push_back(current);

        for(int i = 0 ; i < this->adjacencyList[current].size() ; i++){
            ///as we move to the next node,lower its inDegree
            int next = adjacencyList[current][i];
            inDegrees[next]--;
            if(!inDegrees[next])
                q.push(next);
        }
    }

    if(result.size() == size())
        return result;
    return vector<int>();
}

///A node is a terminal node if there are no outgoing edges.
///A node is a safe node if every possible path starting
///from that node leads to a terminal node (or another safe node).

///The function returns a sorted list of safe nodes
vector<int> OrientedGraph::eventualSafeStates(){
    vector<int> result;
    map<int,int> outDegrees;
    map<int,vector<int>> enteringNodes;

    ///get the outDegree of each node and a list of all the nodes
    ///that go in that node
    for(int i = 0 ; i < this->nodes.size() ; i++){
        outDegrees[nodes[i]] = nodeOutDegree(nodes[i]);
        for(int j = 0 ; j < this->adjacencyList[nodes[i]].size() ; j++)
            enteringNodes[adjacencyList[nodes[i]][j]].push_back(nodes[i]);
    }
    queue<int> q;
    for(int i = 0 ; i < size() ; i++)
        if(!outDegrees[nodes[i]])
            q.push(nodes[i]);

    while(!q.empty()){
        int node = q.front();
        result.push_back(node);
        q.pop();

        for(int i = 0 ; i < enteringNodes[node].size() ; i++){
            outDegrees[enteringNodes[node][i]]--;
            if(!outDegrees[enteringNodes[node][i]])
                q.push(enteringNodes[node][i]);
        }

    }
    std::sort(result.begin() , result.end());
    return result;

}


///Metode pe care nu le am putut integra in clasa de graf
///la Shortest Bridge si Padure puteam folosi cateva metode comune

class Others {
private:
    ///shortest bridge
    void markFirstIsland(vector<vector<int>>& grid, pair<int,int>start, vector<vector<bool>>&visited);
    queue<pair<int,int>> layer(vector<vector<int>>& grid ,queue<pair<int,int>>&q,vector<vector<bool>>&visited);
    ///EquationsPossible
    char searchRep(map<char,char> rep , char chr);
    ///Padure
    void lee(int forest[1001][1001],int diamonds[1001][1001],int n ,int m , int iStart , int jStart);
    bool inMat(int i , int j , int n , int m);
public:
    ///ShortestBridge
    int shortestBridge(vector<vector<int>>& grid);
    ///EquationsPossible
    bool equationsPossible(vector<string>& equations);
    ///Padure
    int minDiamonds(int forest[1001][1001],int n ,int m , int iStart , int jStart , int iFinish , int jFinish);
};





//////////////////////SHORTEST BRIDGE///////////////////////
void Others::markFirstIsland(vector<vector<int>>& grid, pair<int,int>start,vector<vector<bool>>&visited){
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


queue<pair<int,int>> Others::layer(vector<vector<int>>& grid ,queue<pair<int,int>>&q,vector<vector<bool>>&visited){
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

int Others::shortestBridge(vector<vector<int>>& grid) {
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

//////////////////////////PADURE////////////////////////////////
void Others::lee(int forest[1001][1001],int diamonds[1001][1001],int n ,int m , int iStart , int jStart){
    int dirI[4] = {-1 , 1 , 0 , 0};
    int dirJ[4] = {0 , 0 , -1 , 1};

    deque<pair<int,int>>q;

    q.push_front({iStart,jStart});
    diamonds[iStart][jStart] = 0;

    while(!q.empty()){
        int iOld = q.front().first;
        int jOld = q.front().second;
        q.pop_front();

        ///in all directions
        for(int k = 0 ; k < 4 ; k++){
            int iNew = dirI[k] + iOld;
            int jNew = dirJ[k] + jOld;

            ///if the next element is not out of the forest
            ///and its cost is higher than the next than means we didnt check him yet
            if(inMat(iNew,jNew,n,m) && diamonds[iNew][jNew] > diamonds[iOld][jOld]){
                ///if its the same as the current dont increase the cost
                ///and put it in front so we continue with the same value and dont increase it stupidly
                if(forest[iOld][jOld] == forest[iNew][jNew]){
                    diamonds[iNew][jNew] = diamonds[iOld][jOld];
                    q.push_front({iNew,jNew});
                }

                else{
                ///if its a diffrent value increase it s cost and put it back to be checked
                ///after we finish with the current value
                    diamonds[iNew][jNew] = diamonds[iOld][jOld] + 1;
                    q.push_back({iNew,jNew});
                    }
            }
        }
    }
}
int Others::minDiamonds(int forest[1001][1001],int n ,int m , int iStart , int jStart,int iFinish , int jFinish){
        int diamonds[1001][1001];
        ///make the cost matrix
        for(int i = 1 ; i <= n ; i++ )
            for(int j = 1 ; j <= m ; j++){
                diamonds[i][j] = 3000;
        }
        lee(forest,diamonds,n,m,iStart,jStart);
        return diamonds[iFinish][jFinish];

}
///check if the value is in the matrix
bool Others::inMat(int i , int j, int n , int m){
    return i >= 1 && j >= 1 && i <= n && j <= m;
}

////////////////////////POSSIBLE EQUATIONS///////////////
char Others::searchRep(map<char,char> rep , char chr){
        ///if the eleemnt is it s own representant return it
        if( rep[chr] == chr) return chr;
        ///else look at who represents it's represenant
        return searchRep(rep , rep[chr]);
    }

bool Others::equationsPossible(vector<string>& equations) {
            map<char,char> rep;
            ///every element holds the representant of that letter
            for(char i = 'a' ; i <= 'z' ; i++)
                rep[i] = i;

            char word1 , word2;
            for(int i = 0 ; i < equations.size() ; i++){
                string word = equations[i];
                if(word[1] == '='){
                        word1 = searchRep(rep , word[0]);
                        word2 = searchRep(rep , word[3]);
                        ///if they dont have the same represenant
                        ///join them
                        if(word1 != word2)
                            rep[word2] = word1;
                    }
            }

            for(int i = 0 ; i < equations.size() ; i++){
               string word = equations[i];

               if(word[1] == '!'){
                    word1 = searchRep(rep , word[0]);
                    word2 = searchRep(rep , word[3]);
                    if(word1 == word2)
                        return false;
               }
            }
    return true;
    }

