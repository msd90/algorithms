#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <sstream>  

using namespace std;

pair<int,int> randomEdge(unordered_map<int, vector<int>>& G){

    vector<int> arr;

    for(auto i: G){
        arr.push_back(i.first);
    }
       //srand((unsigned) time(0));

    int v1 = arr[rand() % G.size()];
    int v2 = G[v1][rand() % G[v1].size()];

    return {v1,v2};
}

void merge(pair<int, int> verts, unordered_map<int, vector<int>>& G){

    int v1 = verts.first;
    int v2 = verts.second;
    // 1. merge v2 to v1
    
    for(int i=0; i<G[v2].size();i++){
        if(G[v2][i]!=v1)
            G[v1].push_back(G[v2][i]);
    }

    // 2. delete v2 node
    G.erase(v2);
    
    //delete v2 in v1
    for(int i=0; i<G[v1].size();i++){
        if(G[v1][i]==v2){
            G[v1].erase(G[v1].begin()+i);
            i--;
        }
    }

    // for all v2's in map, replace with v1
    vector<int> arr;

    for(auto m: G){
        arr.push_back(m.first);
    }

    for(int i=0; i<arr.size();i++){

        for(int j=0; j<G[arr[i]].size();j++){
            if(G[arr[i]][j]==v2){
                G[arr[i]][j] = v1;
            }
        }
       
    }
}


int main(){

    int count = 0;
    //nodes vector is the output over 20 trials of Karger's algorithm
    vector<int> nodes;
    cout << "Compiling min cut..." << endl;
    while(count < 20){
        unordered_map<int, vector<int>> G;
        ifstream file("mincut.txt");
        string str;
        while (getline(file, str))
        {
            vector<int> res;
            istringstream iss(str);
            int n;

            while (iss >> n) {
                res.push_back(n);

        }
            vector<int> nodes(res.begin()+1, res.end());
            G[res[0]] = nodes;      
        }
    
        
    
        while(G.size() > 2){
            pair<int,int> verts = randomEdge(G);
            merge(verts, G);
        }
        
        //get min size of vector in G
        for(auto i: G){
            nodes.push_back(i.second.size());
            break;
        }

       
        count++;
    }

    
    cout << *min_element(nodes.begin(), nodes.end()) << endl;

    return 0;
}