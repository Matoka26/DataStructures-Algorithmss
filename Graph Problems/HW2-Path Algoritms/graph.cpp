#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <queue>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <queue>
#include <climits>
using std::vector;
using std::unordered_map;
using std::pair;
using std::ifstream;
using std::ofstream;
using std::deque;
using std::queue;
using std::ostream;
using std::cout;

//#define INT_MAX 2147483647
//#define LLONG_MAX 9,223,372,036,854,775,807
///////////////////EDGE CLASS////////////////////
struct Edge{
    int from;
    int to;
    int weight = 0;

    Edge();
    Edge(int v , int w);
    Edge(int v , int w , int weight);
    bool operator==(const Edge& edg);
    bool operator<(const Edge& edg);
    friend ostream& operator<<(ostream& out ,const Edge& edg);
};
Edge::Edge(){
    this->from = 0;
    this->to = 0;
    this->weight = 0;
}
Edge::Edge(int v , int w){
    this->from = v;
    this->to = w;
}
Edge::Edge(int v , int w, int weight){
    this->from = v;
    this->to = w;
    this->weight = weight;
}
bool Edge::operator==(const Edge& edg){
    if(this->from == edg.from &&
       this->to == edg.from &&
       this->weight == edg.weight)
        return true;
    return false;
}
bool Edge::operator<(const Edge& edg){
    return this->weight < edg.weight;
}
ostream& operator<<(ostream& out,const Edge& edg){
    out<<'(';
    out<<edg.from<<','<<edg.to<<')';
    if(edg.weight)
        out<<"->"<<edg.weight;
    return out;
}
Edge min(Edge v , Edge w){
    if( v < w) return v;
    else return w;
}

////////////////////////////////////DSU////////////
class DSU{
private:
    vector<int> parent;
    vector<int> size;

public:
    DSU(int n){
        this->size = vector<int>(n,0);
        this->parent = vector<int>(n);

        for(int i = 0 ; i < n ; i++)
            this->parent[i] = i;

    }

    int Find(int n){
        if(parent[n] == n)
            return n;
        return parent[n] = Find(parent[n]);
    }

    ///union operation implemented by size and not by rank cuz its cleaner
    void Union(int x ,int y){
        int a = Find(x);
        int b = Find(y);


        //by size
        if(a != b)
            if (size[a] < size[b])
                std::swap(a, b);

        parent[b] = a;
        size[a] += size[b];

        /*
         //by rank
         if (a != b) {
            if (rank[a] < rank[b])
                std::swap(a, b);
            parent[b] = a;
            if (rank[a] == rank[b])
                rank[a]++;
        }
        */
    }

};

///////////////////////////////////////////////

class Graph{
private:
    ///adjacency list
    unordered_map<int,vector<pair<int,int>>> adjacency;
    ///edge list if u want to use it idk
    vector<Edge> edges;


public:
        //adds a new edge to the edges vector
    void addEdge(int a, int b, int w);

        //returns the address of the respective list
    vector<pair<int,int>>& operator[](int index);

        //sorts the edge list with resp to the weights
    void sort();
        //returns number of nodes
    int size();
        //returns the address of the edge list
    vector<Edge>& getEdges();

        //dijkstra on n nodes, visiting maximum k nodes
    int dijkstra(int n, int src,int dst, int k);
        //returns a vector of pair giving the dad's vector and the cost to that node
            //structure: <dad,cost>
    vector<pair<int,long long>>dijkstraPathAndCost(int src);

        //return the costs from node src to all the nodes in that connex component
            //if a node is contained in another connex component, it will have distance
            //INT_MAX
    vector<int> zeroOneBFS(int src);
};

vector<pair<int,int>>& Graph::operator[](int index){
    return this->adjacency[index];
}

void Graph::addEdge(int a, int b, int w){
    Edge edg(a,b,w);
    this->edges.push_back(edg);
}

void Graph::sort(){
    std::sort(edges.begin(), edges.end());
}

int Graph::size(){
    if(edges.size() == 0)
        return this->adjacency.size();
    return edges.size();
}

vector<Edge>& Graph::getEdges(){
    return this->edges;
}

int Graph::dijkstra(int n ,int src, int dst, int k){

    vector<int>cost(n+1, INT_MAX);

    ///node,,distance from source, k steps from source
    queue<vector<int>>q;
    q.push({src,0,0});
    cost[src] = 0;

    while(!q.empty()){
        int current = q.front()[0];
        int dist = q.front()[1];
        int steps = q.front()[2];
        q.pop();

     ///for the neighbours
        for(int i = 0 ; i < this->adjacency[current].size() ; i++){
            int nextNode = this->adjacency[current][i].first;
            int nextWeight = this->adjacency[current][i].second;

             ///if we don t move past k
            if(steps  <= k )
                /// if it s cheaper to go there,update
                if(dist + nextWeight < cost[nextNode]){
                    cost[nextNode] = dist + nextWeight;
                    q.push({nextNode,cost[nextNode], steps+1});

                    }

            }
        }
    if(cost[dst] == INT_MAX)
        return -1;
    return cost[dst];

}
vector<pair<int,long long>> Graph::dijkstraPathAndCost(int src){
    int n = size();

    vector<pair<int,long long>>parentsAndCost(n + 1, {0, LLONG_MAX});
    vector<bool>visited(n+1, false);
    std::priority_queue <pair <long long,int>,
                        vector<pair <long long,int>>,
                        std::greater<pair<long long,int>>
                        > minHeap;

    ///push source
    minHeap.push({0,src});
    parentsAndCost[src].second = 0;
    parentsAndCost[src].first = -1;
    //visited[src] = true;

    while(!minHeap.empty()){
        int current = minHeap.top().second;
        minHeap.pop();

        if(!visited[current]){
            visited[current] = true;

            for(int i = 0 ; i < this->adjacency[current].size() ; i++){
                int nextNode = this->adjacency[current][i].first;
                int nextWeight = this->adjacency[current][i].second;

                ///if there is a shorted path ,update and push
                if(parentsAndCost[nextNode].second > parentsAndCost[current].second + nextWeight){

                    parentsAndCost[nextNode].second = parentsAndCost[current].second + nextWeight;
                    parentsAndCost[nextNode].first = current;
                    minHeap.push({parentsAndCost[nextNode].second, nextNode});

                }
            }
        }
    }
    return parentsAndCost;
}


vector<int> Graph::zeroOneBFS(int src){
    vector<int>cost(this->adjacency.size()+1,50005);

    deque<int>deq;
    deq.push_back(src);
    cost[src] = 0;

     while(!deq.empty()){
        int current = deq.front();
        deq.pop_front();

        for(int i = 0 ; i < this->adjacency[current].size(); i++){
            int next = this->adjacency[current][i].first;
            int nextCost = this->adjacency[current][i].second;

            ///if we havent found a cheaper road already
            if (cost[current] < cost[next] - nextCost){

                ///update cost
                cost[next] = cost[current] + nextCost;

                ///if the cost of the edge is 0 we want to explore it sooner
                if(!nextCost)
                    deq.push_front(next);
                else
                    deq.push_back(next);
            }

        }

    }
    return cost;
}







//////////////////////////////////////////////////






class Solution{
private:
    ///helpers
    double distance(pair<int,int>A, pair<int,int>B);
    int dragoni1(ifstream& f, int m, int dmax[]);
    int dragoni2(ifstream& f, int m, int dmax[]);
    //int apm2MaximumCost( Graph& graf,int n, int x, int y);
    void MSTKruskal(Graph graf, vector<Edge>& result,int n);
    void trilantOutput(ofstream& g, vector<pair<int,long long>>& parents, int src);
    bool helperdistanceLimitedPathsExist(int n, vector<vector<int>>& edgeList,vector<int>query);

public:

    ///problems
    void camionas();
    void cablaj();
    void rusuoaica();
    void dragoni();
    void apm2();
    void oracol();
    void trilant();
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k);
    vector<bool> distanceLimitedPathsExist(int n, vector<vector<int>>& edgeList, vector<vector<int>>& queries);
    //unfiniesd
    int jzzhuAndCities();
};

double Solution::distance(pair<int,int>A, pair<int,int>B){
    double x = A.first - B.first;
    double y = A.second - B.second;
    return sqrt(x*x + y*y);
}


///solutions to problems
void Solution::camionas(){
    ifstream f("camionas.in");
    ofstream g("camionas.out");
    ///read data
    Graph graf;

    int n,m,weight,u,v,gr;
    f>>n>>m>>weight;


    for(int i = 0 ; i < m ; i++){
        f>>u>>v>>gr;
        graf[u].push_back({v, gr < weight });
        graf[v].push_back({u, gr < weight });
    }

    vector<int>cost = graf.zeroOneBFS(1);

    g<<cost[n];

    f.close();
    g.close();

}

void Solution::cablaj(){
    ifstream f("cablaj.in");
    ofstream g("cablaj.out");

    int n = 0;
    double s = 0;
    f>>n;

    pair<int,int>points[n];

    ///smallest edge incident to that node
    double keys[n];
    bool visited[n];

    for(int i = 0; i < n ; i++){
        f>>points[i].first>>points[i].second;
        visited[i] = false;
        keys[i] = 50000;
    }

    ///start from first point
    keys[0] = 0;
    visited[0] = true;

    ///make the keys the min distance from the first note
    for(int i = 0 ; i < n ; i++)
        keys[i] = distance(points[0],points[i]);

     ///for every other node,take the min key at each step and recalculate the keys
    for(int k = 0 ; k < n - 1; k++){

        ///index of the next node to be checked
        int minInd = -1;
        for(int i = 0 ; i < n ; i++){
            if(!visited[i]){
                if(minInd == -1) minInd = i;
                else if(keys[i] < keys[minInd]) minInd = i;
            }
        }

        visited[minInd] = true;
        s += keys[minInd];

        ///update the keys
        for(int i = 0 ; i < n ; i++)
            if(!visited[i])
                keys[i] = std::min(keys[i] , distance(points[minInd] , points[i]));


    }
    g<<std::fixed<<std::setprecision(4)<<s;

    f.close();
    g.close();
}

void Solution::rusuoaica(){
    ifstream f("rusuoaica.in");
    ofstream g("rusuoaica.out");

    int n,m,a, sum = 0 , cnt = 0;
    f>>n>>m>>a;

    Graph graf;

    for(int i = 0 ; i < m ; i++){
        int x,y,z;
        f>>x>>y>>z;
        graf.addEdge(x,y,z);
    }

    ///sort the edges with respect to the weights
    graf.sort();
    vector<Edge> newEdgeList = graf.getEdges();

    DSU rep(n+1);
    for(int i = 0 ; i < newEdgeList.size() ; i++){
        Edge edg = newEdgeList[i];

        int x = rep.Find(edg.from);
        int y = rep.Find(edg.to);
        int cost = edg.weight;

        ///if the 2 vertexes are in diff connex componnents
        ///and it costs less to build it now then to dig it again
        if(x != y && cost <= a){
            sum += cost;
            rep.Union(x,y);
            cnt++;
        }
        else
            ///we dont use the tunnel so we sell
            sum -= cost;

    }

    g<<sum + (n-cnt-1)*a;
    f.close();
    g.close();
}

int Solution::findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k){

    Graph graf;

    for(int i = 0; i < flights.size() ; i++)
            graf[flights[i][0]].push_back({flights[i][1],flights[i][2]});

    return graf.dijkstra(n,src,dst,k);

}
int Solution::dragoni1(ifstream& f,int m ,int dmax[]){
    Graph graf;

    for(int i = 0 ; i < m ; i++){
        int u,v,w;
        f>>u>>v>>w;
        graf[u].push_back({v,w > dmax[0]});
        graf[v].push_back({u,w > dmax[0]});
    }

    vector<int> costs = graf.zeroOneBFS(1);
    int maxDrake = -1;

    for(int i = 1 ; i < costs.size() ; i++){
        //std::cout<<dmax[i-1]<<" ";
        if(costs[i] == 0 && dmax[i-1] > maxDrake)
            maxDrake = dmax[i-1];
    }
    return maxDrake;
}

    ///like a dijkstra but weirder
int Solution::dragoni2(ifstream& f, int m, int dmax[]){
    Graph graf;

    for(int i = 0 ; i < m ; i++){
        int u,v,w;
        f>>u>>v>>w;
        graf[u].push_back({v,w});
        graf[v].push_back({u,w});
    }

    ///how far can i get from a node
    vector<int>howFar(graf.size() +1 ,-1);

    ///min heap comparing the costs {cost,{node,currentDrake}}
    std::priority_queue <pair <int, pair <int, int>>, vector<pair<int,pair <int, int>>>, std::greater<pair<int,pair<int, int>>>> minHeap;

    minHeap.push({0,{1,dmax[0]}});

    while(!minHeap.empty()){
        pair<int,pair<int,int>>current = minHeap.top();
        minHeap.pop();


        int currentNode = current.second.first;
        int distance    = current.first;
        int drake       = current.second.second;

        ///if the current drake would improve the distance that we can travel
        if(drake >= howFar[currentNode]){

            howFar[currentNode] = drake;
            if(currentNode == graf.size() )
                return distance;

            for(int i = 0 ; i < graf[currentNode].size() ; i++){
                pair<int,int>nextNode = graf[currentNode][i];

                ///we ll take the better drake between current and next drake
                int nextDrake = std::max(drake, dmax[nextNode.first - 1]);

                ///if my current drake can take me to the next node
                ///and
                ///if the next drake can take me is better then the next one
                if(nextNode.second <= drake && howFar[nextNode.first] < nextDrake)
                                //the cost to the next node = cost of this node + distance to it
                                //the next node
                                //the drake we took to it
                    minHeap.push({nextNode.second + distance , {nextNode.first , nextDrake}});
            }
        }
    }
}

void Solution::dragoni(){
    ifstream f("dragoni.in");
    ofstream g("dragoni.out");

    int oneOrTwo,result;
    int n,m;

    f>>oneOrTwo;
    f>>n>>m;

    int dmax[n+1];
    for(int i = 0 ; i < n ; i++)
        f>>dmax[i];

    if(oneOrTwo == 1)
        result = dragoni1(f,m,dmax);
    else
        result = dragoni2(f,m,dmax);

    g<<result;
    f.close();
    g.close();
}

void Solution::apm2(){
    ifstream f("apm2.in");
    ofstream g("apm2.out");

    Graph graf;
    int n,m,q;
    f>>n>>m>>q;


    ///add regular edges
    for(int i = 0 ; i < m ; i++){
        int u,v,w;
        f>>u>>v>>w;
        graf.addEdge(u,v,w);
    }

    graf.sort();

    vector<Edge>result(q);
    ///check for each mandatory edge (u,v)
    for(int i = 0 ; i < q ; i++){
        int u,v;
        f>>u>>v;
        result[i] = {u, v, -1};
    }

    MSTKruskal(graf,result,n);

    for(int i = 0; i < q ; i++)
        g<<result[i].weight<<'\n';

    f.close();
    g.close();

}

void Solution::MSTKruskal(Graph graf, vector<Edge>& result, int n){
    DSU rep(n+1);

    for(Edge edg: graf.getEdges()){
        int x = rep.Find(edg.from);
        int y = rep.Find(edg.to);
        int weight = edg.weight;

        ///if the edges are not yet connected
        if(x != y){
            ///connect
            rep.Union(x,y);
            ///check if we connected the pair of edges that we were looking for
            for(int i = 0 ; i < result.size() ; i++){
                if(result[i].weight == -1 && rep.Find(result[i].from) == rep.Find(result[i].to))
                    result[i].weight = weight - 1;
            }
        }

    }
}

/*
vector<Edge> Solution::MSTKruskal(){
    vector<Edge>result(graf.size())
    cout<<
    /*
    DSU rep(n+1);
    int weight;
        ///for each edge check which one connects the 2 nodes
        for(Edge edg:graf.getEdges()){

            int x = rep.Find(edg.from);
            int y = rep.Find(edg.to);

            ///if they have the same rep,not worth checking
            if(x != y){

                ///if they are not yet connected we save the weight in case they connect
                if(rep.Find(u) != rep.Find(v))
                    weight = edg.weight;
                else
                    return weight - 1;

                ///unite the 2 nodes of the graph
                rep.Union(y, x);
            }
        }
    return weight - 1;
    return result;
}
*/

void Solution::oracol(){
    ifstream f("oracol.in");
    ofstream g("oracol.out");

    Graph graf;
    int n;
    f>>n;
    for(int i = 0 ; i < n ; i++){
        for(int j = i ; j < n ; j++){
            int cost;
            f>>cost;
            graf.addEdge(i, j+1, cost);
        }
    }

    DSU rep(n+1);
    graf.sort();

    int cost = 0;
    for(Edge edg:graf.getEdges()){
        int x = rep.Find(edg.from);
        int y = rep.Find(edg.to);

        if(x != y ){
                //cout<<edg.weight<<" ";
            cost += edg.weight;
            rep.Union(x,y);
        }

    }

    g<<cost;
    f.close();
    g.close();
}

void Solution::trilantOutput(ofstream& g, vector<pair<int,long long>>& parents, int src){
    ///count iterations
    int cnt = 0;
    queue<int>path;

    int current = src;
    do{
        cnt++;
        path.push(current);
        current = parents[current].first;
    }while(current != -1);

    g<<cnt<<" ";

    ///print the way
    while(!path.empty()){
        g<<path.front()<<" ";
        path.pop();
    }


    g<<'\n';
}


void Solution::trilant(){
    ifstream f("trilant.in");
    ofstream g("trilant.out");

    int n,m;
    f>>n>>m;

    int a,b,c;
    f>>a>>b>>c;

    Graph graf;

    for(int i = 0 ; i < m ; i++){
        int u,v,w;
        f>>u>>v>>w;
        graf[u].push_back({v,w});
        graf[v].push_back({u,w});
    }

    ///return the distances to every node from that node and the dads vector
    vector<pair<int,long long>>pathCostA = graf.dijkstraPathAndCost(a);
    vector<pair<int,long long>>pathCostB = graf.dijkstraPathAndCost(b);
    vector<pair<int,long long>>pathCostC = graf.dijkstraPathAndCost(c);

    ///get the node with the smallest sum out of the 3 chains
    ///index will be the node that connects the 3 chains
    int index = 0;
    long long minim = LLONG_MAX;
    for(int i = 1 ; i <= n ; i++){

        long long sum = pathCostA[i].second + pathCostB[i].second + pathCostC[i].second;
        if(sum < minim){
            index = i;
            minim = sum;
        }
    }

    g<<minim<<'\n';
    trilantOutput(g,pathCostA,index);
    trilantOutput(g,pathCostB,index);
    trilantOutput(g,pathCostC,index);

    f.close();
    g.close();
}


int Solution::jzzhuAndCities(){

/*
    ifstream f("jzz.in");

    Graph graf;
    int n,m,t;
    f>>n>>m>>t;

    int u,v,w;
    for(int i = 0 ; i < m ; i++){
        f>>u>>v>>w;
        //graf.addEdge()

    }
*/

}
bool Solution::helperdistanceLimitedPathsExist(int n, vector<vector<int>>& edgeList,vector<int>query){
   /*
    DSU rep(n+1);

    for(auto it: edgeList){
        int x = rep.Find(it[0]);
        int y = rep.Find(it[1]);

        if(x != y && it[3] >= query[2]){
            if(rep.Find(query[1]) == rep.Find(query[0]))
                return true;
        }
        else
            return false;
        rep.Union(x,y);

    }

    return false;
    */
}

vector<bool> Solution::distanceLimitedPathsExist(int n, vector<vector<int>>& edgeList, vector<vector<int>>& queries){
    vector<bool>result(queries.size(),false);

    ///keep the original index to match with result
    for(int i = 0 ; i < queries.size() ; i++)
        queries[i].push_back(i);

    ///sort edges by weight
    sort(edgeList.begin(), edgeList.end(),
         [](vector<int> a, vector<int> b){
                return a[2] < b[2];
            });
    ///sort queries by weight for easier iteration
    sort(queries.begin(), queries.end(),
         [](vector<int> a, vector<int> b){
                return a[2] < b[2];
            });

    DSU rep(n+1);

    int index = 0;
    for(int i = 0 ; i < queries.size() ; i++){
        vector<int>query = queries[i];

        ///when there is an edge that weights more than the query
        while(index < edgeList.size() && edgeList[index][2] < query[2]){
            rep.Union(edgeList[index][0], edgeList[index][1]);
            index++;
        }
        ///we check if they got connected in the mean time
        if(rep.Find(query[0]) == rep.Find(query[1]))
            result[query[3]] = true;
    }

    return result;
}

int main(){
    Solution a;
    return 0;
}
