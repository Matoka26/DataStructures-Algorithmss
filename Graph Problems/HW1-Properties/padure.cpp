#include<iostream>
#include<fstream>
#include<queue>
using namespace std;

ifstream f("padure.in");
ofstream g("padure.out");
/// m < 1000

int n,m,iStart,jStart,iFinish,jFinish;
int forest[1001][1001];
bool visited[1001][1001];

void afisare(){
    for(int i = 1 ; i <= n ; i++){
        for(int j = 1; j <= m ; j++)
            cout<<visited[i][j]<<" ";
        cout<<endl;
    }
}


void readData(){
    f>>n>>m>>iStart>>jStart>>iFinish>>jFinish;

    for(int i = 1 ; i <= n ; i++ )
        for(int j = 1 ; j <= m ; j++){
            f>>forest[i][j];
            visited[i][j] = false;
        }
}

void markType(pair<int,int>start,int cnt){
    int currentType = forest[start.first][start.second];

    int i = start.first;
    int j = start.second;

    if(i == iFinish && j == jFinish) cout<<cnt;

    if (i < 1 || i > n || j < 0 || j > m+1 || visited[i][j]) {
        return;
    }
        //dreapta
        if( j <= m -1 && j >= 1 && !visited[i][j+1] ){
            visited[i][j+1] = true;

            if(forest[i][j+1] == currentType){
                cout<<i<<','<<j+1<<endl;
                markType({i,j+1},cnt);
            }
            else
                markType({i,j+1},cnt+1);
        }
        //stanga
        if( j  > 1 && j < m && !visited[i][j-1] ){
            visited[i][j-1] = true;

            if(forest[i][j-1] == currentType){
                cout<<i<<','<<j-1<<endl;
                markType({i,j-1},cnt);
            }
            else
                markType({i,j-1},cnt+1);
        }
        //jos
        if( i <= n -1 && i >= 1 && !visited[i+1][j] ){
            visited[i+1][j] = true;

            if(forest[i+1][j] == currentType){
                cout<<i+1<<','<<j<<endl;
                markType({i+1,j},cnt);
            }
            else
                markType({i+1,j},cnt+1);
        }
        //sus
        if( i > 1 && i <= n && !visited[i-1][j] ){
            visited[i-1][j] = true;

            if(forest[i-1][j] == currentType){
                cout<<i-1<<','<<j<<endl;
                markType({i-1,j},cnt);
            }
            else
                markType({i-1,j},cnt+1);
        }
        return;

}




int main(){

    readData();
    //cout<<bfs();
    int cnt = 0;
    markType({iStart,jStart},cnt);
afisare();

    f.close();
    g.close();
    return 0;
}
