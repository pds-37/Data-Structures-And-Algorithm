class Solution {
public:
    int canBeTypedWords(string text, string brokenLetters) {
        unordered_set<char> broken(brokenLetters.begin(), brokenLetters.end());
        
        int count = 0;   // number of words we can type
        bool canType = true;
        
        for (int i = 0; i <= text.size(); i++) {
            if (i == text.size() || text[i] == ' ') { 
                // end of a word
                if (canType) count++;
                canType = true;  // reset for next word
            } 
            else if (broken.count(text[i])) {
                canType = false; // word is invalid
            }
        }
        return count;
    }
};