class Solution {
public:
    
    vector<int> getOrder(vector<vector<int>>& tasks) {
        vector<int> ans;
        int n=tasks.size();

        for(int i=0; i<n; i++){
            tasks[i].push_back(i);
        }

        //Sorting task on the basis of enqueue
        sort(tasks.begin(), tasks.end());
        

        long long timer= tasks[0][0];
        int  i=0;

        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>>pq;

         while (i < n || !pq.empty()) {
            // Push all tasks whose enqueueTime <= current timer
            while (i < n && tasks[i][0] <= timer) {
                pq.push({tasks[i][1], tasks[i][2]});
                i++;
            }

            if (pq.empty()) {
                // Jump time forward to next enqueueTime if no task is available
                timer = tasks[i][0];
            }

          else {
            ans.push_back(pq.top().second);
            timer+=pq.top().first;
            pq.pop();
        }
        }

        return ans;
    }
};