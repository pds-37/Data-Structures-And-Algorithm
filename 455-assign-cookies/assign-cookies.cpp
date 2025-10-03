class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {

        sort(g.begin(), g.end());
        sort(s.begin(), s.end());

        int total_children=0;
        int i=0, j=0;

        while(i<g.size() && j<s.size()){

            if(g[i]<=s[j]){
                total_children+=1;
                i++;
                j++;

            }

            else{
                j++;
            }
        }
        return  total_children;

    }
};