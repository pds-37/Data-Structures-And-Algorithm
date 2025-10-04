class Solution {
    static bool comp(vector<int>& a, vector<int>& b){
    return a[1]<b[1];
}

public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        int cnt=0;
        int end=INT_MIN;

        sort(intervals.begin(),intervals.end(),comp);

        for(int i=0; i<intervals.size(); i++){

            if(end<= intervals[i][0]){
                end=intervals[i][1];
            }
            
            else{
                cnt++;
            }
        }
        return cnt;
    }
};