class Solution {
public:
    int maxBottlesDrunk(int numBottles, int numExchange) {
         int drank = 0, full = numBottles, empty = 0;
        
        while (full > 0) {
            // Drink all full bottles
            drank += full;
            empty += full;
            full = 0;

            // Try to exchange
            if (empty >= numExchange) {
                empty -= numExchange;
                full += 1;
                numExchange++;
            }
        }
        
        return drank;
    }
};