class Solution {
public:
    bool doesAliceWin(string s) {
        for(auto& c : s) {
            if(c=='a' || c=='e' || c=='i' || c=='o' || c=='u') {
                return true;  // Alice can always win
            }
        }
        return false;
    }
};