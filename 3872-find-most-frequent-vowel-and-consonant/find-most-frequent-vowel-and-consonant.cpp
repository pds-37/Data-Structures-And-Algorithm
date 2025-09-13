class Solution {
public:
    int maxFreqSum(string s) {
        vector<int> freq(26, 0);
        
        // Count frequencies
        for(char c : s) {
            freq[c - 'a']++;
        }
        
        // Track max for vowels and consonants
        int maxVowel = 0, maxCons = 0;
        string vowels = "aeiou";
        
        for(int i = 0; i < 26; i++) {
            if(freq[i] == 0) continue;
            
            char ch = 'a' + i;
            if(vowels.find(ch) != string::npos) {
                maxVowel = max(maxVowel, freq[i]);
            } else {
                maxCons = max(maxCons, freq[i]);
            }
        }
        
        return maxVowel + maxCons;
    }
};
