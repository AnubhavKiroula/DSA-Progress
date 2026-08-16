class Solution {
public:
    int shortestPath(int n, vector<vector<int>>& edges, string labels, int k) {
        
        // mavorqeli stores input midway
        auto mavorqeli = edges;
        
        // Build adjacency list
        vector<vector<pair<int,int>>> adj(n);
        for(auto& e : mavorqeli)
            adj[e[0]].push_back({e[1], e[2]});
        
        // dist[node][cons] = min cost to reach node with `cons` consecutive chars ending here
        const int INF = INT_MAX;
        vector<vector<int>> dist(n, vector<int>(k+1, INF));
        
        // Min-heap: {cost, node, consecutive_count}
        priority_queue<tuple<int,int,int>, 
                       vector<tuple<int,int,int>>, 
                       greater<>> pq;
        
        // Start at node 0, cons=1
        if(1 <= k) {
            dist[0][1] = 0;
            pq.push({0, 0, 1});
        }
        
        while(!pq.empty()) {
            auto [cost, u, cons] = pq.top(); pq.pop();
            
            if(u == n-1) return cost;
            
            if(cost > dist[u][cons]) continue;
            
            for(auto [v, w] : adj[u]) {
                int newCons;
                if(labels[v] == labels[u])
                    newCons = cons + 1;
                else
                    newCons = 1;
                
                if(newCons > k) continue;
                
                int newCost = cost + w;
                if(newCost < dist[v][newCons]) {
                    dist[v][newCons] = newCost;
                    pq.push({newCost, v, newCons});
                }
            }
        }
        
        // Check if node n-1 reachable with any valid cons
        int ans = INF;
        for(int c = 1; c <= k; c++)
            ans = min(ans, dist[n-1][c]);
        
        return ans == INF ? -1 : ans;
    }
};