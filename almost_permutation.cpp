// Problem: Almost permutation. https://codeforces.com/contest/863/problem/F

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll N;
ll inf = 1e10;

vector<set<ll>> adj;
vector<vector<vector<ll>>> capacity, cost, edges;

void shortest_paths(ll v0, vector<ll>& d, vector<pair<ll, ll>>& p){ 
    d.assign(N, inf);
    d[v0] = 0;
    vector<bool> inq(N, false);
    queue<ll> q;
    q.push(v0);
    p.assign(N, {-1, -1});

    while(!q.empty()){
        ll u = q.front();
        q.pop();
        inq[u]=false;
        for(int v:adj[u]){
            for(int id:edges[u][v]){ 
                if(capacity[u][v][id]>0 && d[v]>d[u] + cost[u][v][id]){
                    d[v] = d[u]+cost[u][v][id];
                    p[v]={u, id};
                    if(!inq[v]){
                        inq[v]=true;
                        q.push(v);
                    }
                }
            }
        }
    }
}

ll min_cost_flow(ll s, ll t, ll K=inf){
    ll flow=0;
    ll cost=0;
    vector<ll> d;
    vector<pair<ll, ll>> p;
    while(flow<K){
        shortest_paths(s, d, p);
        if(d[t]==inf) break;
        ll f = K-flow;
        pair<ll, ll> cur = {t, -1};
        while(cur.first!=s){
            f=min(f, capacity[p[cur.first].first][cur.first][p[cur.first].second]);
            cur = p[cur.first];
        }
        flow+=f;
        cost+=f*d[t];
        cur={t, -1};
        while(cur.first!=s){
            capacity[p[cur.first].first][cur.first][p[cur.first].second]-=f;
            capacity[cur.first][p[cur.first].first][p[cur.first].second]+=f;
            cur=p[cur.first];
        }
    }

    return cost;
}

int main(){
    ll n, q; cin>>n>>q;
    vector<ll> leq(n, n), geq(n, 1);
    for(ll i=0; i<q; i++){
        ll t, l, r, v; cin>>t>>l>>r>>v;
        if(t==1){
            for(ll j=l-1; j<r; j++){
                geq[j]=max(geq[j], v);
            }
        }

        else{
            for(ll j=l-1; j<r; j++){
                leq[j]=min(leq[j], v);
            }
        }
    }

    N=2*n+2;
    ll s=0, t = 2*n+1;
    capacity.assign(N, vector<vector<ll>>(N, vector<ll>(N, 0)));
    cost.assign(N, vector<vector<ll>>(N, vector<ll>(N, 0)));
    edges.assign(N, vector<vector<ll>>(N, vector<ll>()));
    adj.assign(N, set<ll>());

    for(ll i=1; i<=n; i++){
        adj[s].insert(i);
        adj[i].insert(s);
        for(ll j=1; j<=n; j++){
            ll id = edges[s][i].size();
            edges[s][i].push_back(id);
            edges[i][s].push_back(id);
            capacity[s][i][id]=1;
            cost[s][i][id]=2*j-1;
            cost[i][s][id]=-cost[s][i][j];
        }
    }

    for(ll i=0; i<n; i++){
        if(leq[i]<geq[i]){
            cout<<"-1\n";
            return 0;
        }

        for(ll j=geq[i]; j<=leq[i]; j++){
            adj[i+1+n].insert(j);
            adj[j].insert(i+1+n);
            edges[i+n+1][j].push_back(0);
            edges[j][i+1+n].push_back(0);
            capacity[j][i+1+n][0]=1;
        }
    }

    for(ll i=n+1; i<=2*n; i++){
        adj[i].insert(t);
        adj[t].insert(i);
        edges[i][t].push_back(0);
        edges[t][i].push_back(0);
        capacity[i][t][0]=1;
    }

    ll costt = min_cost_flow(s, t);
    cout<<costt<<"\n";
}