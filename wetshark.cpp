// Problem: Wet Shark and Blocks. https://codeforces.com/problemset/problem/621/E

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

ll mod=1e9+7;
 
ll modulo(ll a, ll b){
    return (a%b + b)%b;
}
 
ll inv(ll a, ll b){
 return 1<a ? b - inv(b%a,a)*b/a : 1;
}

const ll maxn = 100;
 
struct Matrix{
    ll mat[maxn][maxn];
};
 
Matrix matMul(Matrix a, Matrix b){
    Matrix ans;
    for(ll i=0; i<maxn; i++) for(ll j=0; j<maxn; j++) ans.mat[i][j]=0;
 
    for(ll i=0; i<maxn; i++){
        for(ll k=0; k<maxn; k++){
            if(a.mat[i][k]==0) continue;
            for(ll j=0; j<maxn; j++){
                ans.mat[i][j]+=modulo(a.mat[i][k], mod)*modulo(b.mat[k][j], mod);
                ans.mat[i][j] =modulo(ans.mat[i][j], mod);
            }
        }
    }
 
    return ans;
}
 
Matrix matPow(Matrix base, ll p){
    Matrix ans;
    for(ll i=0; i<maxn; i++){
        for(ll j=0; j<maxn; j++){
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
    ll n, b, k, x; cin>>n>>b>>k>>x;
    vector<ll> ocur(10);
    for(ll i=0; i<n; i++){
        ll num; cin>>num;
        ocur[num]++;
    }

    Matrix trans;
    for(ll j=0; j<x; j++){
        for(ll i=0; i<10; i++){
            trans.mat[j][(10*j+i)%x]+= ocur[i];
        }
    }

    trans = matPow(trans, b);
    ll ans = trans.mat[0][k]+0;
    cout<<ans<<"\n";
}