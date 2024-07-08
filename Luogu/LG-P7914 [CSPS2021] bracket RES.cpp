#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
const int MOD=1e9+7;
typedef long long lint;
string s;
bool use(int w,char c){return s[w]==c||s[w]=='?';}
vector<vector<short>> cant;
vector<vector<vector<lint>>> D;
int N,K;
bool cks(int l,int r){
    auto&d=cant[l][r];
    if(d!=-1) return d;
    if(r-l>=K) return d=false;
    if(l>r) return d=true;
    return d=(use(l,'*')?cks(l+1,r):false);
}
lint dfs(int l,int r,int tag){
    auto&d=D[l][r][tag];
    if(d!=-1) return d;
    if(r<=l) return d=0;
    d=0;
    bool lr=use(l,'(')&&use(r,')');
    int gl=l+1,gr=r-1;
    if(!tag){
        if(!lr) return d;
        d=(cks(gl,gr)+dfs(gl,gr,0)+dfs(gl,gr,1)+dfs(gl,gr,2))%MOD;
        cir(i,l,r) (d+=(dfs(l,i,3)*dfs(i+1,r,0)+dfs(l,i,3)*dfs(i+1,r,1)))%=MOD;
    }else if(!(tag-1)){
        cir(i,l,r) (d+=dfs(i+1,r,0)*cks(l,i))%=MOD;
    }else if(!(tag-2)){
        cir(i,l,r) (d+=dfs(l,i,0)*cks(i+1,r))%=MOD;
    }else{
        if(!lr) return d;
        d=(cks(gl,gr)+dfs(gl,gr,0)+dfs(gl,gr,1)+dfs(gl,gr,2))%MOD;
    }
    return d;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    cin>>N>>K>>s;
    cant.assign(N,vector<short>(N,-1));
    D.assign(N,vector<vector<lint>>(N,vector<lint>(4,-1)));
    cout<<dfs(0,N-1,0)<<endl;
    return 0;
}