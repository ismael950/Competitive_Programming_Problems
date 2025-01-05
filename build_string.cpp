//Problem: build string. https://codeforces.com/contest/237/problem/E

#include <bits/stdc++.h>

using namespace std;

int n, inf = 1e9;
vector<vector<int>> adj, capacity, cost;

void shortest_paths(int v0, vector<int>& d, vector<int>& p){ 
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

    if(flow<K) return -1;
    return cost;
}

int main(){
    string T; cin>>T;
    int N; cin>>N;
    int am=0;
    vector<string> st(N); vector<int> a(N);
    for(int i=0; i<N; i++){
        cin>>st[i]>>a[i];
        am+=st[i].size();
    }

    n = T.size()+am+N+2;
    int s = 0, t = T.size()+am+N+1;
    adj.assign(n, vector<int>());
    capacity.assign(n, vector<int>(n, 0));
    cost.assign(n, vector<int>(n, 0));
    for(int i=1; i<=T.size(); i++){
        adj[s].push_back(i);
        adj[i].push_back(s);
        capacity[s][i]=1;
    }

    int letcount=T.size()+1, limcount = T.size()+am+1;

    for(string ac_string:st){
        for(auto c:ac_string){
            for(int i=1; i<=T.size(); i++){
                if(T[i-1]==c){
                    adj[i].push_back(letcount);
                    adj[letcount].push_back(i);
                    capacity[i][letcount]=1;
                    cost[i][letcount]=limcount-T.size()-am;
                    cost[letcount][i]=-cost[i][letcount];
                }
            }

            adj[letcount].push_back(limcount);
            adj[limcount].push_back(letcount);
            capacity[letcount][limcount]=1;
            letcount++;
        }

        adj[limcount].push_back(t);
        adj[t].push_back(limcount);
        capacity[limcount][t] = a[limcount-T.size()-am-1];
        limcount++;
    }

    int ans = min_cost_flow(s, t, T.size());
    cout<<ans<<"\n";
}