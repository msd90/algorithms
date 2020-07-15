#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

pair<vector<int>, long long> merge(vector<int> left, vector<int> right, long long n){
    int count = 0;
    int i = 0;
    int j = 0;
    vector<int> res;
    while( i < left.size() && j < right.size()){
       if(left[i] > right[j]){
            res.push_back(right[j]);
            j++;
            count+= left.size()-(i);
        }
        else{
            res.push_back(left[i]);
            i++;
        }

        
    }

    while(i < left.size()){
        res.push_back(left[i]);
        i++;
    }

     while(j < right.size()){
        res.push_back(right[j]);
        count+= left.size()-(i);
        j++;
    }

    
    return {res, count};
}




pair<vector<int>, long long> countInv(vector<int> array, int n){
    pair<vector<int>, long long> B, C, D;
    if(n==1){
        return {array, 0};
    }
    else{
        B = countInv(vector<int>(array.begin(), array.begin()+n/2), n/2);
        C = countInv(vector<int>(array.begin()+n/2,array.end()), n - n/2);
        D = merge(B.first,C.first,n);
    }

   

    return {D.first ,B.second + C.second + D.second};
}

int main(){

    ifstream file("IntegerArray.txt");
    string str;
    vector<int> arr;
    while (getline(file, str))
    {
        arr.push_back(stoi(str));
    }

    int n = arr.size();

    cout << countInv(arr, n).second << endl;

    return 0;
}