//Problem: Neural Network country. https://codeforces.com/problemset/problem/852/B

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

ll mod=1e9+7;

ll modulo(ll a, ll b){
    return (a%b + b)%b;
}

struct Matrix{
    ll n;
    vector<vector<ll>> mat;
    Matrix(ll n): n(n){
        mat.assign(n, vector<ll>(n, 0));
    }
};

Matrix matMul(Matrix a, Matrix b){
    ll n = a.n;
    Matrix ans(n);

    for(ll i=0; i<n; i++){
        for(ll k=0; k<n; k++){
            if(a.mat[i][k]==0) continue;
            for(ll j=0; j<n; j++){
                ans.mat[i][j]+=modulo(a.mat[i][k], mod)*modulo(b.mat[k][j], mod);
                ans.mat[i][j] =modulo(ans.mat[i][j], mod);
            }
        }
    }

    return ans;
}

Matrix matPow(Matrix base, ll p){
    ll n = base.n;
    Matrix ans(n);
    for(ll i=0; i<n; i++){
        for(ll j=0; j<n; j++){
            ans.mat[i][j]=(i==j);
        }
    }

    while(p){
        if(p&1) ans = matMul(ans, base);
        base = matMul(base, base);
        p>>=1;
    }

    return ans;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    ll n, l, m; cin>>n>>l>>m;
    vector<ll> in(n), cost(n), out(n);
    vector<ll> num(m);
    vector<ll> ini(m);
    for(ll &x:in) {
        cin>>x; 
        ini[x]++;
    }
    for(ll &x:cost) {
        cin>>x; 
        num[x]++;
    }
    for(ll &x:out) cin>>x;
    Matrix transs(m);
    for(ll j=0; j<m; j++){
        for(ll i=0; i<m; i++){
            transs.mat[i][j] = num[modulo(j-i, m)];
        }
    }

    Matrix trans = matPow(transs, l-2);
    vector<ll> dp(m, 0);
    for(ll i=0; i<m; i++){
        for(ll j=0; j<m; j++){
            (dp[i]+=ini[j]*trans.mat[j][i])%=mod;
        }
    }
    ll res = 0;
    for(ll i=0; i<n; i++){
        (res+=dp[modulo(0-cost[i]-out[i], m)])%=mod;
    }

    cout<<res<<"\n";
}