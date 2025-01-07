//Probem: Diverse T-shirts. Latin America Regional. https://codeforces.com/gym/105505/problem/D

#include <bits/stdc++.h>
 
using namespace std;
vector<pair<int, int>> edges;
int N, inf = 1e9;
vector<vector<int>> capacity;
vector<set<int>> adj;
 
int bfs(int s, int t, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, inf});
 
    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();
 
        for (int next : adj[cur]) {
            if (parent[next] == -1 && capacity[cur][next]) {
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                if (next == t)
                    return new_flow;
                q.push({next, new_flow});
            }
        }
    }
 
    return 0;
}
 
int maxflow(int s, int t) {
    int flow = 0;
    vector<int> parent(N);
    int new_flow;
 
    while (new_flow = bfs(s, t, parent)) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }
 
    return flow;
}
 
int main(){
    int n; cin>>n;
    vector<string> gr(n);
    vector<vector<bool>> used(n, vector<bool>(n, false));
    vector<int> cnt(n, 0);
    for(auto &x:gr) cin>>x;
    for(int i=0; i<n; i++) for(int j=i+1; j<n; j++) if(gr[i][j]-'0') {
        edges.push_back({i, j});
        cnt[i]++, cnt[j]++;
    }
    vector<vector<int>> cliques(n, vector<int>());
    int cliqueid = 1;
    for(auto [u, v]:edges){
        if(used[u][v]) continue;
        bool con = false;
        for(int i :cliques[u]) for(int j:cliques[v]) if(i==j){
            used[u][v] = used[v][u] = true;
            con = true;
            break;
        }
        if(con) continue;
        used[u][v]=used[v][u]=1;
        cliques[u].push_back(cliqueid);
        cliques[v].push_back(cliqueid);
        for(int k=0; k<n; k++){
            if(gr[u][k]-'0' && gr[k][v]-'0' && !used[u][k] && !used[k][v]){
                cliques[k].push_back(cliqueid);
                used[u][k]=used[k][u]=used[k][v]=used[v][k]=true;
            }
        }
        cliqueid++;
    }
 
    for(auto &x:cliques) {
        while(x.size()<2) {
            x.push_back(cliqueid);
            cliqueid++;
        }
    }
 
    N = cliqueid + 1;
    capacity.assign(N, vector<int>(N, 0));
    adj.assign(N, set<int>());
    int s = 0, t = N-1;
    for(auto x:cliques){
        int u=x[0], v=x[1];
        adj[u].insert(v);
        adj[v].insert(u);
    }
 
    vector<int> visited(N, false);
    vector<int> color(N, -1);
    for(int i=1; i<N-1; i++){
        if(visited[i]) continue;
        visited[i]=true;
        color[i]=0;
        queue<int> q;
        q.push(i);
        while(!q.empty()){
            int s = q.front(); q.pop();
            for(int u:adj[s]){
                if(visited[u]) continue;
                visited[u] = true;
                color[u] = !color[s];
                q.push(u);
            }
        }
    }
 
    for(int i=1; i<N-1; i++){
        if(color[i]==0){
            adj[s].insert(i);
            adj[i].insert(s);
            capacity[s][i]=1;
        }
 
        else{
            adj[t].insert(i);
            adj[i].insert(t);
            capacity[i][t]=1;
        }
    }
 
    for(auto x:cliques){
        int u=x[0], v=x[1];
        if(color[u]==1) swap(u, v);
        capacity[u][v]=1;
    }
 
    int ans = maxflow(s, t);
    cout<<ans<<"\n";
}