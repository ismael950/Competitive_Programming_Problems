//Problem: Grouped Carriages. https://codeforces.com/problemset/problem/1866/G

#include <bits/stdc++.h>

using namespace std;

int n;
vector<int> a, d;
vector<vector<pair<int, int>>> seg;

bool can(int z){
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> s;
    for(int i=0; i<n; i++){
        for(auto x:seg[i]){
            s.push(x);
        }
        int sum=0;
        while(!s.empty()){
            auto j = s.top();
            s.pop();

            if(j.first<i) return false;

            sum+=j.second;
            if(sum>z){
                j.second = sum-z;
                s.push({j.first, j.second});
                break;
            }
        }
    }

    if(s.empty()) return true;
    else return false;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>n;
    a.assign(n, 0);
    d.assign(n, 0);
    for(int &x:a) cin>>x;
    for(int &x:d) cin>>x;
    seg.assign(n, vector<pair<int, int>>());
    for(int i=0; i<n; i++){
        seg[max(0, i-d[i])].push_back({min(n-1, i+d[i]), a[i]});
    }
    int l=0, r = *max_element(a.begin(), a.end());
    while(l<=r){
        int m = l + (r-l)/2;
        if(can(m)) r=m-1;
        else l = m+1;
    }

    cout<<l<<"\n";
}