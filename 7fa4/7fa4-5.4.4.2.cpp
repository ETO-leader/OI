#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
#define continue_with(code)\
    {cout<<(code)<<'\n';continue;}
using namespace std;
using lint=long long;
using VI=vector<lint>;
const lint MOD=20120427;
const int mxsiz=7e4+7;
unordered_map<lint,int> id;
array<array<lint,mxsiz>,20> D,C;
vector<VI> idi;
VI ls,lg;
void prepare(){
    lint p2=1,p3,p5,p7;
    const lint maxest=1e18+7;
    cir(i,0,62){
        if(p2>maxest) break;
        p3=1;
        cir(j,0,40){
            if(p2>maxest/p3) break;
            p5=1;
            cir(k,0,28){
                if(p2*p3>maxest/p5) break;
                p7=1;
                cir(x,0,23){
                    if(p2*p3*p5>maxest/p7) break;
                    id.insert({p2*p3*p5*p7,0});
                    p7*=7;
                }
                p5*=5;
            }
            p3*=3;
        }
        p2*=2;
    }
    int cnx=0;
    for(auto&[a,b]:id) b=cnx++,ls.push_back(a);
    idi.assign(ls.size(),VI(10));
    cir(i,0,ls.size()) cir(j,1,10){
        if(ls[i]%j) idi[i][j]=-1;
        else idi[i][j]=id[ls[i]/j];
    }
    for(auto&i:ls)
        lg.push_back(logf128(i)/logf128(7)-1);
}
VI arr,pow10;
pair<lint,lint> dfs(int p,int w,bool mxtag,bool al){
    if(!(~p)) return {0,ls[w]==1};
    if(p+1<lg[w]) return {0,0};
    const int idx=w;
    lint&d=((mxtag||al)?*(new lint(0)):D[p][idx]);
    lint&c=((mxtag||al)?*(new lint(0)):C[p][idx]);
    if((!al)&&(!mxtag)&&(~d)) return {d,c};
    const int mxi=mxtag?arr[p]+1:10;
    d=0;
    cir(i,1,mxi) if(idi[w][i]!=-1){
        auto [dx,cx]=dfs(p-1,idi[w][i]
            ,mxtag&&(i==mxi-1),false);
        c+=cx;
        d+=dx+i*pow10[p]*cx;
    }
    if(al) d+=dfs(p-1,w,mxtag&&(!arr[p]),true).first;
    return {d%=MOD,c%=MOD};
}
lint slv(lint x,lint k){
    auto str=to_string(x);
    for(auto&i:str) i-='0';
    reverse(str.begin(),str.end());
    arr.clear();
    for(auto&i:str) arr.push_back(i);
    memset(D.begin(),-1,sizeof(D));
    memset(C.begin(),0,sizeof(C));
    pow10.clear();pow10.resize(1,1);
    cir(i,1,114) pow10.push_back(pow10.back()*10%MOD);
    return dfs(str.size()-1,id[k],true,true).first;
}
pair<lint,lint> _type0(int p,int w,
    bool up=true,bool al=true){
    if(!(~p)) return {0,1};
    if(up&&arr[p]==0) return {0,0};
    if((!up)&&(~D[p][w])) return {D[p][w],C[p][w]};
    lint&d=((up)?*(new lint(0)):D[p][w]);
    lint&c=((up)?*(new lint(0)):C[p][w]);
    d=0;
    cir(i,1,(up?arr[p]+1:10)){
        auto [dx,cx]=_type0(p-1,i,(up&&(i==arr[p])),false);
        c+=cx;
        d+=dx+cx*i*pow10[p];
    }
    if(al){
        auto [dx,cx]=_type0(p-1,0,false,true);
        d+=dx;c+=cx;
    }
    return {d%=MOD,c%=MOD};
}
lint type0(lint x){
    arr.clear();
    while(x) arr.push_back(x%10),x/=10;
    pow10.clear();pow10.resize(1,1);
    cir(i,1,114) pow10.push_back(pow10.back()*10%MOD);
    memset(D.begin(),-1,sizeof(D));
    memset(C.begin(),0,sizeof(C));
    return _type0(arr.size()-1,0).first;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int q;cin>>q;prepare();
    cir(i,0,q){
        lint a,b,k;cin>>a>>b>>k;
        if(!k) continue_with([&]{
            __int128 r=(a+b);r*=(b-a+1);r/=2;
            r%=MOD;
            return (lint)(r-(type0(b)-type0(a-1))+MOD*8)%MOD;
        }());
        if(!id.count(k)) continue_with(0);
        cout<<(slv(b,k)-slv(a-1,k)+MOD)%MOD<<'\n';
    }
    return 0;
}