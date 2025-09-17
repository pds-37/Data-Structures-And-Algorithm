class Solution {
public:
    string sortVowels(string s) {
        auto isVowel = [](char c) {
            c = tolower(c);
            return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
        };

        // Step 1: Extract vowels
        vector<char> vowels;
        for (char c : s) {
            if (isVowel(c)) vowels.push_back(c);
        }

        // Step 2: Sort vowels by ASCII
        sort(vowels.begin(), vowels.end());

        // Step 3: Place vowels back in sorted order
        int idx = 0;
        for (char &c : s) {
            if (isVowel(c)) {
                c = vowels[idx++];
            }
        }

        return s;
        

    }
};