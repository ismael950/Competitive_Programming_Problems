//Problem: Paired Payment. https://codeforces.com/problemset/problem/1486/E

#include <bits/stdc++.h>

using namespace std;

int inf = 1e9;
vector<vector<pair<int, int>>> adj;
vector<int> d;


int main(){
    int n, m; cin>>n>>m;
    adj.assign(51*n, vector<pair<int, int>>());
    
    for(int j=0; j<m; j++){
        int u, v, w; cin>>u>>v>>w; u--, v--;
        adj[u*51].push_back({v*51 + w, 0});
        for(int was=1; was<=50; was++){
            adj[u * 51 + was].push_back({v * 51, (was + w) * (was + w) });
        }
        adj[v*51].push_back({u*51 + w, 0});
        for(int was=1; was<=50; was++){
            adj[v * 51 + was].push_back({u * 51, (was + w) * (was + w) });
        }
    }


    d.assign(51*n, inf);
    vector<int> p(51*n, -1);
    set<pair<int, int>> q;
    q.insert({0, 0});
    d[0]=0;
    while(!q.empty()){
        int v = q.begin()->second;
        q.erase(q.begin());
        for(auto edge:adj[v]){
            int to = edge.first, len = edge.second;
            if(d[v]+len<d[to]){
                q.erase({d[to], to});
                d[to]=d[v]+len;
                p[to]=v;
                q.insert({d[to], to});
            }
        }
    }

    for(int i=0; i<n; i++){
        if(d[i*51]<inf) cout<<d[i*51]<<" ";
        else cout<<"-1 ";
    }

    cout<<"\n";
}