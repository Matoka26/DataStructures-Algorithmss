#include "orientedGraph.h"
#include <strings.h>
using std::string;

class UnorientedGraph: public OrientedGraph{
private:
    ///methods
    int nodeOutDegree(int node) = delete;
    int nodeInDegree(int node) = delete;
    vector<int> topologicalSort() = delete;
    vector<int> eventualSafeStates() = delete;
    vector<int> bfsDistance(int node);
    vector<Edge> getEdges();

    bool bipartiteColoring(int node , vector<int>&colors);
    void criticalConnectionsDfs(int node, int parent , vector<bool>&visited, vector<int>&minLvl,vector<int>&level , vector<vector<int>>&result , int& step);

public:
    UnorientedGraph();
    UnorientedGraph(map<int,vector<int>> adjacency);
    UnorientedGraph(vector<vector<int>> adjacency);
    void removeEdge(Edge edg);
    void removeEdge(int v , int w , int weight);
    int nodeDegree(int node);

    ///void removeEdge(Edge edg);
    ///void removeEdge(int v , int w, int weight);

    void newEdge(Edge edg);
    void newEdge(int v, int w);
    void newEdge(int v, int w, int weight);

    ///Solutions
    bool possibleBipartition();
    int minimumMaximumDistance(vector<int>specialNodes);
    vector<vector<int>> criticalConnections();
    string graphWithoutLondDirectedPaths();

};
UnorientedGraph::UnorientedGraph():OrientedGraph(){};
UnorientedGraph::UnorientedGraph(vector<vector<int>> adjacency):OrientedGraph(adjacency){}

int UnorientedGraph::nodeDegree(int node){
    return OrientedGraph::getAdjOfNode(node).size();

}

void UnorientedGraph::newEdge(Edge edg){
    OrientedGraph::newEdge(edg);
    this->adjacencyList[edg.to].push_back(edg.from);

}
void UnorientedGraph::newEdge(int v, int w){
    OrientedGraph::newEdge(v,w);
    this->adjacencyList[w].push_back(v);
}
void UnorientedGraph::newEdge(int v, int w, int weight){
    OrientedGraph::newEdge(v,w,weight);
    this->adjacencyList[w].push_back(v);
}
vector<Edge> UnorientedGraph::getEdges(){
    vector<Edge> result;
    for(int i = 0 ; i < this->edges.size() ; i++){
        result.push_back(edges[i]);
    }
    return result;
}

bool UnorientedGraph::bipartiteColoring(int node , vector<int>&colors){
    ///assing the starting node a color
    colors[node] = 1;

    queue<int>q;
    q.push(node);

    while(!q.empty()){
        int current = q.front();
        q.pop();
        ///look in the neighbours
        for(int i = 0 ; i < this->adjacencyList[current].size() ; i++){
            int neighbour = adjacencyList[current][i];
            ///if it doesnt have an assigned color,
            ///color it diffrent from its current node
            if(colors[neighbour] == -1){
                if(colors[current] == 0)
                    colors[neighbour] = 1;
                else
                    colors[neighbour] = 0;
                q.push(neighbour);
            }
            else
                ///if 2 adjacent nodes have same color its bad
                if(colors[current] == colors[neighbour])
                    return false;

        }


    }
    return true;
}
bool UnorientedGraph::possibleBipartition(){
    ///if the graph is empty it is bipartite
    if(this->nodes.empty()) return true;
    ///0 & 1 ->2 disjoint classes of nodes
    ///could as well chose Red and Blue or smth
    ///-1 ->not assigned yet
    vector<int> colors(this->nodes.size(),-1);

    for(int i = 0 ; i < this->nodes.size() ; i++)
        if(colors[i] == -1)
            if(bipartiteColoring(i,colors) == false)
                return false;

    return true;
}

int UnorientedGraph::minimumMaximumDistance(vector<int> specialNodes){
    if(!specialNodes.size()) return 0;

    ///bfs on a random node to find the farthest special node
    vector<int> distances = bfsDistance(1);
    int maximum = 0;
    long farthestNode;
    for(int i = 0 ; i < specialNodes.size() ; i++)
        if(distances[specialNodes[i]] > maximum){
            maximum = distances[specialNodes[i]];
            farthestNode = specialNodes[i];
        }
    ///look for the farthest speical node from that one
    distances = bfsDistance(farthestNode);

    maximum = 0;
    for(int i = 0 ; i < specialNodes.size(); i++)
        if(distances[specialNodes[i]] > maximum)
            maximum = distances[specialNodes[i]];

    return (maximum+1)/2;

}
vector<int> UnorientedGraph::bfsDistance(int node){
    queue<int>q;
    vector<int>distances(size()+1,-1);
    distances[node] = 0;
    q.push(node);
    while(!q.empty()){
        int current = q.front();
        q.pop();
        for(int i = 0 ; i < this->adjacencyList[current].size() ; i++){
            int newNode = adjacencyList[current][i];
            if(distances[newNode] == -1){
                distances[newNode] = distances[current] + 1;
                q.push(newNode);
            }
        }
    }
    return distances;

}

vector<vector<int>> UnorientedGraph::criticalConnections(){
    vector<bool>visited(size(),0);
    vector<int>minLvl(size());
    vector<int>level(size());
    vector<vector<int>>result;

    int step = 0;
    level[0] = 0;

    criticalConnectionsDfs(0,-1,visited,minLvl,level,result,step);

    return result;
}

void UnorientedGraph::criticalConnectionsDfs(int node, int parent , vector<bool>&visited, vector<int>&minLvl,vector<int>&level , vector<vector<int>>&result , int& step){
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
                criticalConnectionsDfs(nextNode,node , visited , minLvl , level,result,step);
                ///update node's value
                minLvl[node] = std::min(minLvl[node] , minLvl[nextNode]);
                ///test if the neighbour went lower than the node
                if(minLvl[nextNode] > level[node])
                    result.push_back({node,nextNode});
            }
            else
            ///upeate if the vertex node-nextNode is for return
                if(level[nextNode] < level[node] - 1)
                    minLvl[node] = std::min(minLvl[node] , level[nextNode]);
        }
    }
}

string UnorientedGraph::graphWithoutLondDirectedPaths(){
    ///its the same as the bipart graph
    vector<int>colors(size()+1 , -1);
    if(!bipartiteColoring(1,colors))
        return "NO";

    string result = "YES\n";
    vector<Edge> edgs = getEdges();
    for(int i = 0 ; i < edgs.size() ; i++){
            ///edge[x,y]
            ///colors[x] = 0
            ///colors[y] = 1
            ///means the edge is directed from x to y
            if(colors[edgs[i].from] == 0 && colors[edgs[i].to] == 1)
                result += "0";
            else
                result += "1";
        }
    return result;
}
