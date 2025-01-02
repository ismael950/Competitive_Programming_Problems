// Problem: Koxia and Game. https://codeforces.com/contest/1770/problem/D 

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

ll mod = 998244353;

vector<vector<ll>> adj;
vector<ll> visited;
ll v, e, sel;

void dfs(ll x){
    if(visited[x]) return; 
    visited[x]=true;
    v++;
    for(ll v:adj[x]){
        e++;
        dfs(v);
        if(v==x) sel++;
    }
}

void solve(){
    ll n; cin>>n;
    vector<ll> a(n), b(n);
    for(ll &x:a) cin>>x; for(ll &x:b) cin>>x;
    adj.assign(n, vector<ll>());
    visited.assign(n, false);
    for(int i=0; i<n; i++){
        a[i]--, b[i]--;
        adj[a[i]].push_back(b[i]);
        adj[b[i]].push_back(a[i]);
    }

    ll ans = 1;

    for(int i=0; i<n; i++) if(!visited[i]){
        v=e=sel=0;
        dfs(i);
        if(e!=2*v) ans=0;
        else if (sel) (ans*=n)%=mod;
        else (ans*=2)%=mod;
    }

    cout<<ans<<"\n";
}

int main(){
    ll t; cin>>t; while(t--) solve();
}