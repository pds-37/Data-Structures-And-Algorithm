class Solution {
public:
    vector<string> spellchecker(vector<string>& wordlist, vector<string>& queries) {
        unordered_set<string> exact(wordlist.begin(), wordlist.end()); // Rule 1
        unordered_map<string, string> caseInsensitive;  // Rule 2
        unordered_map<string, string> vowelInsensitive; // Rule 3

        // Helper lambda: replace all vowels with '*'
        auto devowel = [](string w) {
            for (auto &c : w) {
                char x = tolower(c);
                if (x=='a' || x=='e' || x=='i' || x=='o' || x=='u') c = '*';
                else c = x; // lowercase all consonants
            }
            return w;
        };

        // Preprocess wordlist
        for (string w : wordlist) {
            string lower = w;
            transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
            string dv = devowel(lower);

            if (!caseInsensitive.count(lower)) caseInsensitive[lower] = w;
            if (!vowelInsensitive.count(dv)) vowelInsensitive[dv] = w;
        }

        vector<string> res;
        for (string q : queries) {
            if (exact.count(q)) {
                res.push_back(q); // Rule 1: exact match
                continue;
            }

            string lower = q;
            transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
            if (caseInsensitive.count(lower)) {
                res.push_back(caseInsensitive[lower]); // Rule 2: case-insensitive
                continue;
            }

            string dv = devowel(lower);
            if (vowelInsensitive.count(dv)) {
                res.push_back(vowelInsensitive[dv]); // Rule 3: vowel-error insensitive
                continue;
            }

            res.push_back(""); // No match
        }
        return res;
    }
};
