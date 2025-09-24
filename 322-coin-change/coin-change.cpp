class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        if (amount == 0) return 0;
        
        queue<pair<int,int>> q; // {remaining amount, steps}
        vector<bool> visited(amount+1, false);
        
        q.push({amount, 0});
        visited[amount] = true;
        
        while (!q.empty()) {
            auto [curr, steps] = q.front(); q.pop();
            
            for (int coin : coins) {
                int next = curr - coin;
                if (next == 0) return steps + 1; // reached solution
                if (next > 0 && !visited[next]) {
                    visited[next] = true;
                    q.push({next, steps + 1});
                }
            }
        }
        return -1; // not possible
    }
};
