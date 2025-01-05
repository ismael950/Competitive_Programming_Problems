//Problem: Delivery bears. https://codeforces.com/contest/653/problem/D

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;

ll n, m, x, s, t; ll inf = 1e10;
vector<vector<ll>> capacity, ogcapacity, adj;

ll bfs(ll s, ll t, vector<ll>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<ll, ll>> q;
    q.push({s, inf});

    while (!q.empty()) {
        ll cur = q.front().first;
        ll flow = q.front().second;
        q.pop();

        for (ll next : adj[cur]) {
            if (parent[next] == -1 && capacity[cur][next]) {
                parent[next] = cur;
                ll new_flow = min(flow, capacity[cur][next]);
                if (next == t)
                    return new_flow;
                q.push({next, new_flow});
            }
        }
    }

    return 0;
}

ll maxflow(ll s, ll t) {
    ll flow = 0;
    vector<ll> parent(n);
    ll new_flow;

    while (new_flow = bfs(s, t, parent)) {
        flow += new_flow;
        ll cur = t;
        while (cur != s) {
            ll prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}

bool can(ld f){
    for(ll i=0; i<n; i++) for(ll j=0; j<n; j++){
        capacity[i][j]=static_cast<ll>(ogcapacity[i][j]/f);
    }

    ll F = maxflow(s, t);
    if(F>=x) return true;
    return false;
}

int main(){
    cin>>n>>m>>x;
    adj.assign(n, vector<ll>());
    capacity.assign(n, vector<ll>(n, 0));
    ogcapacity=capacity;
    s=0; t=n-1;
    for(ll i=0; i<m; i++){
        ll u, v, c; cin>>u>>v>>c; u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
        ogcapacity[u][v]+=c;
    }

    ld eps = 0.000000000001;
    ld l = 0, r = 100000000;
    while(l<=r){
        ld m = (l+r)/2;
        if(can(m)) l = m+eps;
        else r = m-eps;
    }

    ld ans = r*x;
    cout<<fixed<<setprecision(10)<<ans<<"\n";
}