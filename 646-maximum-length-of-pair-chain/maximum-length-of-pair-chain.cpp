

class Solution {
    static bool comp(vector<int>& a, vector<int>& b){
    return a[1]<b[1];
}

public:
    int findLongestChain(vector<vector<int>>& pairs) {
        sort(pairs.begin(), pairs.end(), comp);

        int totallength=0;
        int ending=INT_MIN;

        for(int i=0; i<pairs.size(); i++){
            if(pairs[i][0]>ending){
                totallength++;
                ending=pairs[i][1];
            }

        }
        return totallength;
    }
};