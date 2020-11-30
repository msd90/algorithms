#include <bits/stdc++.h> 
using namespace std;

//To use the SCC.txt file used in main() download it from:  http://algorithmsilluminated.org/datasets/problem8.10.txt
//This program will return the top 5 strongly connected componments in descending order.

vector<int> sizes;
vector<int> buildGraph(unordered_map<int, vector<int>>& adjList, ifstream& file){
    string str;
    vector<int> nodes;
    while (getline(file, str)){
        istringstream iss(str);
        int node;
        while(iss >> node){
            nodes.push_back(node);
        }
    }

    for(int i=1; i<nodes.size();i+=2){
        adjList[nodes[i-1]].push_back(nodes[i]);
    }

    reverse(nodes.begin(), nodes.end());

    return nodes;

}


int DFS2(int valNode, unordered_map<int, bool>& visited, unordered_map<int, vector<int>>& adjList_rev, int& count){
    
    //cout << valNode << endl;
   

    visited[valNode] = true;

    for(auto& x: adjList_rev[valNode]){
       
        if(visited[x]==false){
            
            //cout << "DFS" << endl;
            count++;
            DFS2(x,visited, adjList_rev, count);
           

        }

    }

 
    
    return count;
 
    
    
}

void DFS1(int valNode, unordered_map<int, bool>& visited, stack<int>& nodeStack, unordered_map<int, vector<int>>& adjList){
    visited[valNode] = true;

    for(auto& x : adjList[valNode]){
        if(visited[x]==false){
            DFS1(x, visited, nodeStack, adjList);
        }
    }

    nodeStack.push(valNode);

}

void DFS(unordered_map<int, vector<int>>& adjList, unordered_map<int, bool>& visited,stack<int>& nodeStack){

    for(auto& node: adjList){

        if(visited[node.first]==false){
            DFS1(node.first, visited, nodeStack, adjList);
        }
    }


}

void reverseGraph(vector<int>& rev, unordered_map<int,vector<int>>& adjList_rev){

     for(int i=1; i<rev.size();i+=2){
        adjList_rev[rev[i-1]].push_back(rev[i]);
    }

}


int main(){

    unordered_map<int,vector<int>> adjList;
    unordered_map<int,vector<int>> adjList_rev;
    unordered_map<int,bool> visited;
    ifstream file("SCC.txt");
    stack<int> nodeStack;   
    
    vector<int> rev = buildGraph(adjList, file);
    
   


    //create visited adjList
    for(auto& node: adjList){
        visited[node.first] = false;
    }

    DFS(adjList, visited, nodeStack);
    reverseGraph(rev,adjList_rev);

    //reset node visited array to false
    for(auto& node: adjList){
        visited[node.first] = false;
    }

    while(!nodeStack.empty()){
        int curr = nodeStack.top();
        nodeStack.pop();
        if(visited[curr]==false){
          int count = 1;  
          sizes.push_back(DFS2(curr, visited, adjList_rev, count));
        }
        
    }

    sort(sizes.rbegin(), sizes.rend());

   int topFive = 0;
   for(auto nodes: sizes){
       if(topFive==5) break;
       cout << nodes << endl;
       topFive++;
   }
    

    

    return 0;
}
