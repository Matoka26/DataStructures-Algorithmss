#include <iostream>
#include <vector>
#include <queue>
#include <fstream>

#define INF 2147483647
using namespace std;



class MaxFlowGraph{
private:
    ///ATTRIBUTES
    vector<vector<int>>adjacency;
    vector<vector<int>>capacity;
    vector<vector<int>>flow;

    ///HELPERS
    int bfs(const int& s, const int& t, vector<int>& parent);
    void printMatrix(const vector<vector<int>> &m);

public:
    /// METHODS:

        /// Create graph with adjacency list and capacities
    MaxFlowGraph(const vector<vector<int>>& adjacency, const vector<vector<int>>& capacity);

        /// Edmonds-Karp Algorithm implementation
        /// Find MaxFlow value and get the values of the edges in 'flow' attribute
    int maxFlow(const int& s, const int& t);
        /// Returns a vector of visited nodes contained in the MaxFlow Graph
    vector<bool> minCut(const int& s);
        /// Returns a reference to the 'flow' matrix
    vector<vector<int>>& getFlow();

        /// Print attributes
    void printCapacity();
    void printAdjacency();
    void printFlow();

};

MaxFlowGraph::MaxFlowGraph(const vector<vector<int>>& adjacency, const vector<vector<int>>& capacity){
        this->adjacency = adjacency;
        this->capacity = capacity;
        this->flow = vector<vector<int>> (this->capacity.size(), vector<int>(this->capacity.size(),0));

}

void MaxFlowGraph::printMatrix(const vector<vector<int>> &m){
    for(int i = 0 ; i < m.size() ; i++){
        cout<<i<<':';
        for(int j = 0 ; j < m[i].size() ; j++)
            cout<<m[i][j]<<" ";
        cout<<'\n';
    }
}

void MaxFlowGraph::printAdjacency(){
    printMatrix(this->adjacency);
}

void MaxFlowGraph::printCapacity(){
    printMatrix(this->capacity);
}
void MaxFlowGraph::printFlow(){
    printMatrix(this->flow);
}

vector<vector<int>>& MaxFlowGraph::getFlow(){
    return this->flow;
}


int MaxFlowGraph::bfs(const int& s, const int& t, vector<int>& parent){
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;

    queue<pair<int,int>>q;
    q.push({s,INF});

    while(!q.empty()){
        int current = q.front().first;
        int flow = q.front().second;
        q.pop();

        for(int next : this->adjacency[current]){
            if(parent[next] == -1 && this->capacity[current][next] > this->flow[current][next]){
                parent[next] = current;
                int newFlow = min(flow, this->capacity[current][next] - this->flow[current][next]);
                if(next == t)
                    return newFlow;
                q.push({next, newFlow});
            }

        }
    }
    return 0;
}


int MaxFlowGraph::maxFlow(const int& s, const int& t){
    vector<int>parent(this->capacity.size());
    int flowFound = 0;

    while(1){
        int newFlow = bfs(s,t,parent);

        if(!newFlow)
            break;

        flowFound += newFlow;
        int current = t;
        while(current != s){
            int dad = parent[current];
            flow[current][dad] -= newFlow;
            flow[dad][current] += newFlow;
            current = dad;
        }
    }
    return flowFound;
}

vector<bool> MaxFlowGraph::minCut(const int& s){
    vector<bool>visited(this->capacity.size(), false);

    visited[s] = true;
    queue<int>q;
    q.push(s);
    while(!q.empty()){
        int current = q.front();
        q.pop();

        for(int next: this->adjacency[current]){
            if(!visited[next] && this->capacity[current][next] > this->flow[current][next]){
                visited[next] = true;
                q.push(next);
            }
        }
    }
    return visited;
}

class Solution{
private:
    /// HELPERS
        ///NoPrimeSum()
    bool isPrimeSumOfTwo(const int& a, const int& b);
public:
    /// PROBLEMS
    // https://www.infoarena.ro/problema/senat
    void Senat();
    // https://www.infoarena.ro/problema/harta
    void Harta();
    // https://infoarena.ro/problema/negot
    void Negot();
    // https://www.infoarena.ro/problema/paznici
    void Paznici();
    // https://leetcode.com/problems/shortest-path-visiting-all-nodes/
    int shortestPathLength(vector<vector<int>>& graph);
    // https://csacademy.com/contest/archive/task/no-prime-sum/
    void NoPrimeSum();

        ///UNFINISHED
    // https://www.infoarena.ro/problema/cc
    void Cc();

};



/* PROBLEM:
 *       There are n senators and each one is part of a few teams
 *       There must be chosen senators such that each team has a leader
 *       out of the senators, a senator can not be the leader of more
 *       than 1 team.
 *       Find a configuration
 *
 */

/* IDEA:
 *       Build 2 sets, one containing the senators and the other
 *       the teams they are part of.
 *
 *       Connect each senator with the teams he's part of
 *       Connect each senator with a source 0
 *       Connect each team with a target nrOfSenators + nrOfTeams + 1
 *       Each connection having capacity 1
 *
 *       Apply Max Flow to get the configuration
 */
void Solution::Senat(){
    ifstream f("senat.in");
    ofstream g("senat.out");

    int n,m;
    f>>n>>m;

    vector<vector<int>> adjacency(n+m+2);
    vector<vector<int>> capacity(n+m+2, vector<int>(n+m+2, 0));

    string line;
    getline(f,line);


    ///connections between the 2 disjoint sets
    for(int i = 1 ; i <= m ; i++){
        getline(f,line);

        int nr = 0;
        for(int j = 0 ; j < line.size() ; j++){
            if(line[j] != ' ')
                nr = nr*10 + (line[j] - '0');
            else{
                adjacency[nr].push_back(n+i);
                adjacency[n+i].push_back(nr);
                capacity[nr][n+i] = 1;
                nr = 0;
            }
        }
        if(nr){
            adjacency[nr].push_back(n+i);
            adjacency[n+i].push_back(nr);
            capacity[nr][n+i] = 1;
        }
    }

    ///connect start to the first set
    for(int i = 1 ; i <= n ; i++){
        adjacency[0].push_back(i);
        adjacency[i].push_back(0);
        capacity[0][i] = 1;
    }

    ///connect second set to target
    for(int i = n + 1 ; i <= n + m ; i++){
        adjacency[i].push_back(n+m+1);
        adjacency[n+m+1].push_back(i);
        capacity[i][n+m+1] = 1;
    }


    MaxFlowGraph graph(adjacency,capacity);

    int flow = graph.maxFlow(0,n+m+1);

    if(flow != m)
        g<<0;

    else{
        for(int i = n+1 ; i <= n+m ; i++){
            for(int j = 1 ; j <= n + 1 ; j++)
                if(graph.getFlow()[j][i])
                    g<<j<<'\n';
        }
    }

    graph.printFlow();

    f.close();
    g.close();

}
/*PROBLEM:
        There are N cities, there are no multiple roads in between cities
        and no road leads back to the starting city, the roads are also
        bidirectional.

        For each city we know how many roads leave the city and how many
        enter the city.

        Find the coresponding edges.
 */

/* IDEA:
 *       Build 2 sets, both having all the cities.
 *
 *       Connect the first set with a source 0 having
 *       capacity = InDegree of the city
 *
 *       Connect the second set with a target n+n+2 having
 *       capacity = outDegree of the city
 *
 *       Connect each city from the first set with every
 *       city from the second set except for self with
 *       capacity = 1
 *
 *       Apply Max Flow Algorithm
 */
void Solution::Harta(){
    ifstream f("harta.in");
    ofstream g("harta.out");

    int n;
    f>>n;

    vector<vector<int>>adjacency(n+n+2);
    vector<vector<int>>capacity(n+n+2,vector<int>(n+n+2, 0));

    for(int i = 1 ; i <= n ; i++ ){
        int x,y;
        f>>x>>y;

        ///from start to first set
        adjacency[0].push_back(i);
        adjacency[i].push_back(0);
        capacity[0][i] = x;

        ///from second set to target
        adjacency[n+i].push_back(n+n+1);
        adjacency[n+n+1].push_back(n+i);
        capacity[n+i][n+n+1] = y;
    }

    ///connect the middle
    for(int i = 1; i <= n ; i++)
        for(int j = 1 ; j <= n ; j++)
            if(i != j){
                adjacency[i].push_back(j + n);
                adjacency[j+n].push_back(i);
                capacity[i][j+n] = 1;
            }

    MaxFlowGraph graph(adjacency,capacity);

    int maxflow = graph.maxFlow(0,n+n+1);

    graph.printFlow();
    g<<maxflow<<endl;

    for(int i = 1 ; i <= n ; i++)
        for(int j = n + 1 ; j <= n+n ; j++)
            if(graph.getFlow()[i][j])
                g<<i<<" "<<j-n<<endl;



    f.close();
    g.close();
}

/* PROBLEM:
 *       There are N producers and M shops and a number K
 *       representing the max number of shops a producer
 *       can provide for. And for each producer the shops
 *       it can provide to. Each shop can be provided by 1
 *       producer at a time.
 *
 *       Find the number of shops that will be provided by
 *       the producers.
 *
 */

 /*
    IDEA:
        Put the producers in a set and the shops in another.

        Connect the produces with a source 0 with capacity K.
        Connect the shops to a target nrOfProducers + nrOfShops + 1
        with a capacity 1.
        Connect the shops and the producers accordingly to the problem
        with capacity 1

        Apply Max Flow Algorithm and return the value
 */

///70p
void Solution::Negot() {
    ifstream f("negot.in");
    ofstream g("negot.out");

    int n, m, k;
    f>>n>>m>>k;

    vector<vector<int>> adjacency(n+m+2);
    vector<vector<int>> capacity(n+m+2, vector<int>(n+m+2, 0));

    ///connect the 2 sets
    int t, tl;
    for(int i = 1 ; i <= n ; i++){
        f>>t;
        for(int j = 0 ; j < t ; j++){
            f>>tl;
            adjacency[i].push_back(n+tl);
            adjacency[n+tl].push_back(i);
            capacity[i][n+tl] = 1;
        }
    }

    ///connect source to set 1
    for(int i = 1 ; i <= n ; i++){
        adjacency[0].push_back(i);
        adjacency[i].push_back(0);
        capacity[0][i] = k;
    }

    ///connect set 2 to target
    for(int i = n + 1 ; i <= n+m ; i++){
        adjacency[i].push_back(n+m+1);
        adjacency[n+m+1].push_back(i);
        capacity[i][n+m+1] = 1;
    }

    MaxFlowGraph graph(adjacency, capacity);
    int maxFlow = graph.maxFlow(0,n+m+1);

    //graph.printCapacity();
    g<<maxFlow;
    f.close();
    g.close();
}

/* PROBLEM:
 *        There is a matrix representing a filed, each
 *        cell representing a patch of something .
 *
 *        The rows and columns are indexed with letters,
 *        lowercase for columns and uppercase for rows.
 *
 *        A security guard can guard all the patches from a
 *        row/column at a time.
 *
 *        Find the positions of minimum number of guards
 *        required and their positions.
 */

/*
 *   IDEA:
 *       Make 2 sets, one with the rows and one with the columns.
 *
 *       Connect the first set to a source 0 with capacity 1.
 *       Connect the second set to a target nrOfRows + nrOfCols + 1
 *       with capacity 1.
 *       Connect the nodes from the 2 sets where exists a patch with
 *       capacity 1.
 *
 *       Apply Max Flow Algorithm and print the not visited nodes
 *       from the first set of the minCut resulted from the maxFlow
 *       and the visited nodes from the second set
 *
 */
void Solution::Paznici() {
    ifstream f("paznici.in");
    ofstream g("paznici.out");

    int n,m;
    f>>n>>m;
    vector<vector<int>>adjacency(n+m+2);
    vector<vector<int>>capacity(n+m+2, vector<int>(n+m+2, 0));

    string line;
    ///connect lines to columns
    for(int i = 1 ; i <= n ; i++){
        f>>line;
        for(int j = 1 ; j <= m ; j++) {
            if(line[j-1] == '1'){
                adjacency[i].push_back(n+j);
                adjacency[n+j].push_back(i);
                capacity[i][n+j] = 1;
            }
        }
    }

    ///connect source to lines
    for(int i = 1 ; i <= n ; i++){
        adjacency[0].push_back(i);
        adjacency[i].push_back(0);
        capacity[0][i] = 1;
    }
    ///connect columns to target
    for(int i = 1 ; i <= m ; i++){
        adjacency[n+i].push_back(n+m+1);
        adjacency[n+m+1].push_back(n+i);
        capacity[n+i][n+m+1] = 1;
    }

    MaxFlowGraph graph(adjacency, capacity);

    graph.maxFlow(0,n+m+1);


    vector<bool> result = graph.minCut(0);

    for(int i = 0 ; i < n ; i++)
        if(!result[i+1])
            g<<char('A'+ i);

    for(int i = n+1 ; i < n+m + 1 ; i++)
        if(result[i])
            g<<char('a' + i-n-1);

    f.close();
    g.close();
}


void Solution::Cc(){
    ifstream f("cc.in");
    ofstream g("cc.out");

    int n, cost;
    f>>n;

    vector<vector<int>>adjacency(n+n+2);
    vector<vector<int>>capacity(n+n+2, vector<int>(n+n+2, 0));

    ///connect the 2 sets
    for(int i = 1 ; i <= n ; i++){
        for(int j = 1 ; j <= n ; j++){
           f>>cost;
           adjacency[i].push_back(n+j);
           adjacency[n+j].push_back(i);
           capacity[i][j] = 1;
        }
    }

    ///connect set 1 to start
    for(int i = 1 ; i <= n ; i++){
        adjacency[0].push_back(i);
        adjacency[i].push_back(0);
        capacity[0][i] = 1;
    }

    for(int i = n+1 ; i <= n+n ; i++){
        adjacency[i].push_back(n+n+1);
        adjacency[n+n+1].push_back(i);
        capacity[i][n+n+1] = 1;
    }

    MaxFlowGraph graph(adjacency, capacity);
    graph.printAdjacency();

    f.close();
    g.close();
}


bool Solution::isPrimeSumOfTwo(const int& a, const int& b){
    int sum = a + b;

    if(sum == 0 || sum == 1)
        return false;

    for(int i = 2 ; i <= sum/2 ; i++)
        if(sum % i == 0)
            return false;

    return true;
}

/*
 * PROBLEM:
 *       Being given N numbers, determin how many and which
 *       of them should be removed so that no sum of 2 numbers
 *       is a prime number
 */

/*
 * IDEA:
 *        For 2 sets,one with even number and one with odd
 *
 *            even + even = even
 *            odd  + odd  = even
 *            even + odd  = odd
 *
 *        and the only prime even number is 2 so the rest must
 *        be a combination of even and odd.
 *
 *       Connect the first set to a source 0 with capacity 1
 *      Connect the second set to a target N + 2
 *       Connect elements of the 2 sets if their sum is NOT
 *       a prime number.
 *
 *       Apply MaxFlow Algorithm and check what numbers of the
 *       first set ARE NOT contained in the solution and what
 *       numbers of the first set ARE contained.
 */

void Solution::NoPrimeSum() {
    int n,nr;
    cin>>n;
    vector<int> oddNumbers;
    vector<int> evenNumbers;

    vector<vector<int>>adjacency(n+3);
    vector<vector<int>>capacity(n+3, vector<int>(n+3, 0));

    /// Make 2 sets, even and odd numbers
    for(int i = 0 ; i < n ; i++){
        cin>>nr;
        if(nr & 1)
            oddNumbers.push_back(nr);
        else
            evenNumbers.push_back(nr);
    }

    /// Connect source to the first set
    for(int i = 1 ; i <= oddNumbers.size() ; i++){
        adjacency[0].push_back(i);
        adjacency[i].push_back(0);
        capacity[0][i] = 1;
    }

    /// Connect second set to the target
    for(int i = 1 ; i <= evenNumbers.size() ; i++){
        int u = i  + oddNumbers.size();
        int v = oddNumbers.size() + evenNumbers.size() + 1;
        adjacency[u].push_back(v);
        adjacency[v].push_back(u);
        capacity[u][v] = 1;
    }

    /// Connect the 2 sets
    for(int i = 0 ; i < oddNumbers.size() ; i++)
        for(int j = 0 ; j < evenNumbers.size() ; j++)
            /// If the combination of numbers is prime
            /// connect them with capacity 1
            if(isPrimeSumOfTwo(oddNumbers[i], evenNumbers[j])){
                int u = i + 1;
                int v = j + 1 + oddNumbers.size();
                adjacency[u].push_back(v);
                adjacency[v].push_back(u);
                capacity[u][v] = 1;
            }

    MaxFlowGraph graph(adjacency, capacity);
    graph.maxFlow(0, n+1);

    /// Get the nodes included in the flow
    vector<bool> visited = graph.minCut(0);
    vector<int> resultingNodes;

    /// Check for numbers in the first set
    for(int i = 0 ; i < oddNumbers.size() ; i++)
        if(!visited[i+1])
            resultingNodes.push_back(oddNumbers[i]);

    /// Check for numbers in the second set
    for(int i = 0 ; i < evenNumbers.size() ; i++)
        if(visited[i + oddNumbers.size() + 1])
            resultingNodes.push_back(evenNumbers[i]);

    cout<<resultingNodes.size()<<'\n';
    for(int i = 0 ; i < resultingNodes.size() ; i++){
        cout<<resultingNodes[i]<<" ";
    }
}


/*
 * PROBLEM:
 *       Having an undirected graph of N nodes, return
 *       the length of the shortest path that visit every node
 *       (an edge can be visited multiple times).
 */

 /*
  * IDEA:
  *      The length of the shortest path that visits every node
  *      is an NP problem so we must try out every possible path
  *      until we find a solution.
  *
  *      We'll represent each path with a bitmask, when we visit
  *      a new node we'll put a 1 in the position of the node
  *      and stop when we have a full array of 1's.
  *
  *      We'll keep a struct of {node, mask, step} as follows
  *          node -> the node we're on
  *          mask -> the path  we took there
  *          step -> the length of the path
  *      and we'll apply a bfs approach until we find a solution and
  *      return the step attribute.
  */

/// https://noahhsu.medium.com/leetcode-847-hard-shortest-path-visiting-all-nodes-5798c28aa55f
///inspiration
int Solution::shortestPathLength(vector<vector<int>>& graph){
   struct Triplet{
       int node;
       int mask;
       int step;
   };

    int n = graph.size();
    int target = (1<<n) - 1;
    vector<vector<bool>>status(n);

    queue<Triplet>q;
    for(int i = 0 ; i < n ; i++){
        q.push({i, 1<<i, 0});
        status[i] = vector<bool>(1<<n,false);
        status[i][1<<i] = true;
    }

    while(!q.empty()){
        int node = q.front().node;
        int mask = q.front().mask;
        int step = q.front().step;
        q.pop();

        if(mask  == target)
            return step;

        for(int next:graph[node]){
            int tempMask = mask | 1 << next;
            if(!status[next][tempMask]){
                status[next][tempMask] = true;
                q.push({next, tempMask, step+1});
            }
        }
    }
    return 0;
}

int main(){
    Solution sol;
    //sol.NoPrimeSum();

    return 0;
}
