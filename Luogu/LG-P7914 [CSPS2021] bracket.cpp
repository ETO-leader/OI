#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
string s;vector<vector<int>> stc;
inline bool ckc(int&w,char c){return s[w]=='?'||s[w]==c;}
using lint=long long;
const int MOD=1e9+7;
int n,k;
vector<vector<vector<lint>>> D;
bool canp(int l,int r){
    auto&d=stc[l][r];
    if(r-l>=k) return d=false;
    if(d!=-1) return d;
    if(l>r) return d=true;
    if(ckc(l,'*')) return d=canp(l+1,r);
    return d=false;
}
lint dfs(int l,int r,int tp){
    auto&d=D[l][r][tp];
    if(l>=r) return d=0;
    if(d!=-1) return d;
    bool lrk=(ckc(l,'(')&ckc(r,')'));
    int gl=l+1,gr=r-1;d=0;
    if(!tp){
        if(!lrk) return d;
        d=(canp(gl,gr)+dfs(gl,gr,0)+dfs(gl,gr,1)+dfs(gl,gr,2))%MOD;
        cir(i,l,r) (d+=((dfs(l,i,3)*dfs(i+1,r,0))%MOD
            +(dfs(l,i,3)*dfs(i+1,r,1))%MOD))%=MOD;
    }else if(!(tp-1)){
        cir(i,l,r) (d+=dfs(i+1,r,0)*canp(l,i))%=MOD;
    }else if(!(tp-2)){
        cir(i,l,r) (d+=dfs(l,i,0)*canp(i+1,r))%=MOD;
    }else{
        if(!lrk) return d;
        d=(canp(gl,gr)+dfs(gl,gr,0)+dfs(gl,gr,1)+dfs(gl,gr,2))%MOD;
    }
    return d%=MOD;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    cin>>n>>k>>s;stc.assign(n,vector<int>(n,-1));
    D.assign(n,vector<vector<lint>>(n,vector<lint>(4,-1)));
    cout<<dfs(0,n-1,0)<<endl;
    return 0;
}