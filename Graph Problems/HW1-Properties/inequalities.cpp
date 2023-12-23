#include <iostream>
#include <vector>
#include <strings.h>
#include <map>
using namespace std;



class Solution {
private:
    char searchRep(map<char,char> rep , char chr){
        ///if the eleemnt is it s own representant return it
        if( rep[chr] == chr) return chr;
        ///else look at who represents it's represenant
        return searchRep(rep , rep[chr]);
    }
public:
    bool equationsPossible(vector<string>& equations) {
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
};


int main(){
    vector<string> v = {"a==b","c==d","a==c","a!=d"};


    Solution sol;
    cout<<sol.equationsPossible(v);

    return 0;
}
