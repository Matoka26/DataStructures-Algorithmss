#include <iostream>
using std::ostream;

class BadNode:public std::exception{
public:
    virtual const char* what() const throw(){
        return "Vertex or Node not contained in the graph";
    }

}badNode;

struct Edge{
    int from;
    int to;
    int weight = 0;
    Edge(int v , int w);
    Edge(int v , int w , int weight);
    bool operator==(const Edge& edg);
    bool operator<(const Edge& edg);
    friend ostream& operator<<(ostream& out ,const Edge& edg);
};
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
