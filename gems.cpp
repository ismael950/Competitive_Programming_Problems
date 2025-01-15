// Problem: Magic gems. https://codeforces.com/problemset/problem/1117/D
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
 
struct Matrix{
    ll mat[101][101];
};
 
Matrix matMul(Matrix a, Matrix b){
    Matrix ans;
    for(ll i=0; i<101; i++) for(ll j=0; j<101; j++) ans.mat[i][j]=0;
 
    for(ll i=0; i<101; i++){
        for(ll k=0; k<101; k++){
            if(a.mat[i][k]==0) continue;
            for(ll j=0; j<101; j++){
                ans.mat[i][j]+=modulo(a.mat[i][k], mod)*modulo(b.mat[k][j], mod);
                ans.mat[i][j] =modulo(ans.mat[i][j], mod);
            }
        }
    }
 
    return ans;
}
 
Matrix matPow(Matrix base, ll p){
    ll n = 101;
    Matrix ans;
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
    ll n, m; cin>>n>>m;
    if(m>n){
        cout<<"1\n";
        return 0;
    }

    Matrix trans;
    for(ll i=0; i<101; i++) for(ll j=0; j<101; j++) trans.mat[i][j]=0;
    for(ll i=0; i<m-1; i++) trans.mat[i+1][i] = 1;
    trans.mat[0][m-1]=trans.mat[m-1][m-1]=1;
    trans = matPow(trans, n-m+1);
    ll ans = 0;
    for(ll i=0; i<=m-1; i++) (ans+=trans.mat[i][m-1])%=mod;
    cout<<ans<<"\n";
}