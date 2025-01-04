//Problem: Olympiad in Programming and Sports. https://codeforces.com/problemset/problem/730/I

#include <bits/stdc++.h>

using namespace std;
int N, P, S;
vector<vector<int>> adj, capacity, cost;

const int inf = 1e9;

void shortest_paths(int v0, vector<int>& d, vector<int>& p){
    int n = N+4; 
    d.assign(n, inf);
    d[v0] = 0;
    vector<bool> inq(n, false);
    queue<int> q;
    q.push(v0);
    p.assign(n, -1);

    while(!q.empty()){
        int u = q.front();
        q.pop();
        inq[u]=false;
        for(int v:adj[u]){
            if(capacity[u][v]>0 && d[v]>d[u] + cost[u][v]){
                d[v] = d[u]+cost[u][v];
                p[v]=u;
                if(!inq[v]){
                    inq[v]=true;
                    q.push(v);
                }
            }
        }
    }
}

int min_cost_flow(int s, int t, int K=inf){
    int flow=0;
    int cost=0;
    int n = N+4;
    vector<int> d, p;
    while(flow<K){
        shortest_paths(s, d, p);
        if(d[t]==inf) break;
        int f = K-flow;
        int cur = t;
        while(cur!=s){
            f=min(f, capacity[p[cur]][cur]);
            cur = p[cur];
        }
        flow+=f;
        cost+=f*d[t];
        cur=t;
        while(cur!=s){
            capacity[p[cur]][cur]-=f;
            capacity[cur][p[cur]]+=f;
            cur=p[cur];
        }
    }

    return cost;
}

int main(){
    cin>>N>>P>>S;
    capacity.assign(N+4, vector<int>(N+4, 0));
    adj.assign(N+4, vector<int>());
    cost.assign(N+4, vector<int>(N+4, 0));
    int s=0, t=N+3, prog=1, sport=2;
    adj[0].push_back(prog);
    adj[prog].push_back(0);
    capacity[0][prog]=P;
    adj[0].push_back(sport);
    adj[sport].push_back(0);
    capacity[0][sport]=S;

    for(int i=3; i<N+3; i++){
        int c; cin>>c; c*=(-1);
        adj[prog].push_back(i);
        adj[i].push_back(prog);
        capacity[prog][i]=1;
        cost[prog][i]=c;
        cost[i][prog]=-c;
    }

    for(int i=3; i<N+3; i++){
        int c; cin>>c; c*=(-1);
        adj[sport].push_back(i);
        adj[i].push_back(sport);
        capacity[sport][i]=1;
        cost[sport][i]=c;
        cost[i][sport]=-c;
    }

    for(int i=3; i<N+3; i++){
        adj[t].push_back(i);
        adj[i].push_back(t);
        capacity[i][t]=1;
    }

    int ans = min_cost_flow(s, t);
    vector<int> pteam, steam;
    for(int i=3; i<N+3; i++){
        if(capacity[prog][i]==0) pteam.push_back(i-2);
        if(capacity[sport][i]==0) steam.push_back(i-2);
    }

    cout<<-ans<<"\n";
    for(int x:pteam) cout<<x<<" "; cout<<"\n";
    for(int x:steam) cout<<x<<" "; cout<<"\n";
}