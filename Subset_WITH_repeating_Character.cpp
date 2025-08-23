#include<bits/stdc++.h>
using namespace std;


void getAllSubsets(vector<int> &arr, vector<int> &ans, int i, vector<vector<int>> &allSubsets){
    if(i==arr.size()){
        allSubsets.push_back(ans);
        return;
    }
    // include
    ans.push_back(arr[i]);
    getAllSubsets(arr, ans, i+1, allSubsets);
    
    while(i+1<arr.size() && arr[i]==arr[i+1]) i++;
    // exclude
    ans.pop_back(); 
    getAllSubsets(arr, ans, i+1, allSubsets);
}

int main() {

    vector<int> arr;
    for(int i=0;i<4;i++){
        int x; cin>>x;
        arr.push_back(x);
    }
    vector<int> ans;
    vector<vector<int>> allSubsets;

    sort(arr.begin(), arr.end());
    

    getAllSubsets(arr, ans, 0, allSubsets);

    for(auto x:allSubsets){
       cout << "{";
       for (int val : x) cout << val << " ";
       cout << "} ";

    }

    return 0;
}