#include <vector>
using std::vector;

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
