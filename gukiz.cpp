// Problem: GukiZ and Binary Operations. https://codeforces.com/problemset/problem/551/D
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

ll mod;
 
ll modulo(ll a, ll b){
    return (a%b + b)%b;
}
 
ll inv(ll a, ll b){
 return 1<a ? b - inv(b%a,a)*b/a : 1;
}
 
struct Matrix{
    ll mat[4][4];
};
 
Matrix matMul(Matrix a, Matrix b){
    Matrix ans;
    for(ll i=0; i<4; i++) for(ll j=0; j<4; j++) ans.mat[i][j]=0;
 
    for(ll i=0; i<4; i++){
        for(ll k=0; k<4; k++){
            if(a.mat[i][k]==0) continue;
            for(ll j=0; j<4; j++){
                ans.mat[i][j]+=modulo(a.mat[i][k], mod)*modulo(b.mat[k][j], mod);
                ans.mat[i][j] =modulo(ans.mat[i][j], mod);
            }
        }
    }
 
    return ans;
}
 
Matrix matPow(Matrix base, ll p){
    ll n = 4;
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
    ll n, k, l; cin>>n>>k>>l>>mod;
    ll bits;
    if(k>0) bits = (ll)log2(k)+1;
    else bits = 0;
    if(bits>l){
        cout<<"0\n";
        return 0;
    }

    Matrix ini, trans;
    for(ll i=0; i<4; i++) for(ll j=0; j<4; j++) {ini.mat[i][j]=0; trans.mat[i][j]=0;}
    ini.mat[0][0]=2; ini.mat[0][1]=ini.mat[0][2]=1;
    trans.mat[0][0]=trans.mat[1][0] = trans.mat[0][1] = trans.mat[2][2] = trans.mat[3][2] = trans.mat[1][3] = trans.mat[2][3] = trans.mat[3][3] = 1;
    ll pot = n-2;
    Matrix pow = matPow(trans, pot);
    Matrix ways = matMul(ini, pow);
    ll cero = (ways.mat[0][0] + ways.mat[0][1])%mod;
    ll ones = (ways.mat[0][2] + ways.mat[0][3])%mod;
    ll ans = 1;
    for(ll i=0; i<l; i++){
        if(k & (1ll<<i)){
            (ans*=ones)%=mod;
            continue;
        }
        (ans*=cero)%=mod;
    }
    cout<<ans%mod<<"\n";
}