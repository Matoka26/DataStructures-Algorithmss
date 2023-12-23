#include<iostream>
#include<vector>
#include<queue>
using namespace std;

class Solution {
public:
    vector<int> findOrder(int numCourses,vector<vector<int>>& prerequisites){
        vector<int>rezultat;
        vector<vector<int>>adiacenta(numCourses);
        vector<int>grdIn(numCourses,0);
        queue<int>q;
        ///facem liste de adiacenta
        for(int i = 0 ; i < prerequisites.size() ; i++)
            adiacenta[prerequisites[i][1]].push_back(prerequisites[i][0]);

        ///gradu de intrare in fiecare nod
        for(int i = 0 ; i < prerequisites.size() ; i++)
            //for(int j = 0 ; j < prerequisites[i].size() ; j++)
                grdIn[prerequisites[i][0]] += 1;

        for(int i = 0 ; i < numCourses ; i++)
            if(!grdIn[i])
                q.push(i);

        while(!q.empty()){
            int nodNou = q.front();
            q.pop();
            rezultat.push_back(nodNou);
            for(int i = 0 ; i < adiacenta[nodNou].size() ; i++){
                grdIn[adiacenta[nodNou][i]]--;
                if(!grdIn[adiacenta[nodNou][i]])
                    q.push(adiacenta[nodNou][i]);
            }
        }
        if(rezultat.size() == numCourses)
            return rezultat;
        return vector<int>();

    }


};

int main(){
Solution sol;
int numCourses = 4;
vector<vector<int>> prerequisites = {{1,0},{2,0},{3,1},{3,2}};


vector<int>s = sol.findOrder(numCourses,prerequisites);
for(int i = 0 ;i < numCourses ; i++) cout<<s[i];

///verifica daca are ciclii....

return 0;
}
