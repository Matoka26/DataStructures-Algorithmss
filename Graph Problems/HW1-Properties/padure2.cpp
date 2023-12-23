///cu comentarii***

#include<iostream>
#include<fstream>
#include<deque>
using namespace std;

ifstream f("padure.in");
ofstream g("padure.out");
/// m <= 1000

int n,m,iStart,jStart,iFinish,jFinish;
int forest[1001][1001];
int diamonds[1001][1001];
int dirI[4] = {-1 , 1 , 0 , 0};
int dirJ[4] = {0 , 0 , -1 , 1};
            //left ,right, up , down

bool inMat(int i , int j){
    return i >= 1 && j >= 1 && i <= n && j <= m;
}

void afisare(int forest[1001][1001]){
    for(int i = 1 ; i <= n ; i++){
        for(int j = 1; j <= m ; j++)
            cout<<forest[i][j]<<" ";
        cout<<endl;
    }
}


void readData(){
    f>>n>>m>>iStart>>jStart>>iFinish>>jFinish;

    for(int i = 1 ; i <= n ; i++ )
        for(int j = 1 ; j <= m ; j++){
            f>>forest[i][j];
            ///give them all an unobtainably high cost
            diamonds[i][j] = 3000;
        }
}

void lee(int iStart ,int jStart){
    deque<pair<int,int>>q;

    ///start
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
            if(inMat(iNew,jNew) && diamonds[iNew][jNew] > diamonds[iOld][jOld]){
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

int main(){

    readData();
    lee(iStart , jStart);
//afisare(diamonds);

g<<diamonds[iFinish][jFinish];
    f.close();
    g.close();
    return 0;
}
///n o merit p asta...
