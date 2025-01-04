//Problem: The Doctor Meets Vader (Medium). https://codeforces.com/problemset/problem/1184/B2

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

ll n, m, S, B, K, H;
vector<vector<ll>> capacity, adj, d;
ll inf = 1e12;

struct ship{
    ll x, a, f;
    ship(ll x, ll a, ll f):x(x), a(a), f(f){}
};

struct base{
    ll x, d;
    base(ll x, ll d): x(x), d(d){}
};

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
    vector<ll> parent(S+B+2);
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

int main(){
    cin>>n>>m;
    d.assign(n, vector<ll>(n, inf));
    for(int i=0; i<n; i++) d[i][i]=0;
    for(int i=0; i<m; i++){
        ll u, v; cin>>u>>v;
        u--, v--;
        d[u][v]=d[v][u]=min(d[u][v], 1ll);
    }

    for(int k=0; k<n; k++){
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                if(d[i][k] < inf && d[k][j]<inf) d[i][j] = min(d[i][j], d[i][k]+d[k][j]);
            }
        }
    }

    cin>>S>>B>>K>>H;

    vector<ship> ships;
    vector<base> bases;

    ll s=0, t=S+B+1;
    adj.assign(S+B+2, vector<ll>());
    capacity.assign(S+B+2, vector<ll>(S+B+2, 0));

    for(ll i=0; i<S; i++){
        ll x, a, f; 
        cin>>x>>a>>f;
        ships.push_back(ship(x-1, a, f));
    }

    for(ll i=0; i<B; i++){
        ll x, dd; 
        cin>>x>>dd;
        bases.push_back(base(x-1, dd));
    }

    for(ll i=1; i<=S; i++){
        for(ll j=1; j<=B; j++){
            if(ships[i-1].a>=bases[j-1].d && d[ships[i-1].x][bases[j-1].x]<=ships[i-1].f){
                adj[i].push_back(j+S);
                adj[j+S].push_back(i);
                capacity[i][j+S]=1;
            }
        }
    }

    for(ll i=1; i<=S; i++){
        adj[0].push_back(i);
        adj[i].push_back(0);
        capacity[0][i]=1;
    }

    for(ll i=S+1; i<=S+B; i++){
        adj[i].push_back(t);
        adj[t].push_back(i);
        capacity[i][t]=1;
    }

    ll m = maxflow(s, t);
    ll ans = min(m*K, S*H);


    cout<<ans<<"\n";
}