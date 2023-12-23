#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    bool mor = true;
    vector<char>culori;

    bool checkVecini(int nod , vector<int> vecini){
        for(int i = 0 ; i < vecini.size() ; i++){
            if(culori[nod] == culori[vecini[i]]) return false;
        }
    return true;
    }

    bool possibleBipartition(int n, vector<vector<int>>& dislikes){
        pos(n,dislikes,1);
        if(!mor) return false;
        else return true;
    }
    void pos(int n, vector<vector<int>>& dislikes,int start) {
       vector<vector<int>>adiacenta(n+1); //adiacenta[0] va fi gol
       for(int i = 0 ; i < dislikes.size() ; i++){
           adiacenta[dislikes[i][0]].push_back(dislikes[i][1]);
           adiacenta[dislikes[i][1]].push_back(dislikes[i][0]);
       }

        if(culori.empty())
            for(int i = 0 ; i <= n ; i++)
                culori.push_back('-');


        queue<int>q;
        culori[start] = 'R';
        q.push(start);

        while(!q.empty()){
            char nextCol;
            if(culori[q.front()] == 'R') nextCol = 'B';
            else nextCol = 'R';

            int nodCurent = q.front();
            ///cautam prin vecini
            for(int i = 0 ; i < adiacenta[nodCurent].size() ; i++){
                if(culori[adiacenta[nodCurent][i]] ==  culori[nodCurent]) mor =  false;
                else if(culori[adiacenta[nodCurent][i]] != '-'){}
                else if(culori[adiacenta[nodCurent][i]] == '-' ){
                        q.push(adiacenta[nodCurent][i]);
                        culori[adiacenta[nodCurent][i]] = nextCol;
                        }
                if(!checkVecini(nodCurent,adiacenta[nodCurent])) mor = false;

            }
            q.pop();
        }

        for(int i = start ; i <= n ; i++){
            if(culori[i] == '-'){
                pos(n,dislikes,i);
                break;
            }
        }
    }
};
int main(){
    int n = 4;
    vector<vector<int>>dislikes;
    dislikes.push_back({1,2});
    dislikes.push_back({1,3});
    dislikes.push_back({2,4});
    //dislikes.push_back({3,4});
    Solution rez;
    cout<<rez.possibleBipartition(n,dislikes)<<endl;
    return 0;

}
