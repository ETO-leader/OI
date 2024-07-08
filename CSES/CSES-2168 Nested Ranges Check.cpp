#include<bits/stdc++.h>
#include<bits/extc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace __gnu_pbds;
using namespace std;
template<typename T,class comp=less<T>>
using rbt=tree<T,null_type,comp,rb_tree_tag,
    tree_order_statistics_node_update>;
struct nd{int u,id,tag;};
struct comp{
    bool operator()(const pair<int,int>&a,
        const pair<int,int>&b) const{
        return a.first==b.first?
            a.second<b.second:a.first>b.first;
    }
};
const int _inf=1e9+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,l,r,cnt=0;cin>>n;vector<nd> ix;
    vector<int> L(n);
    vector<pair<int,int>> Pi(n);
    cir(i,0,n) cin>>l>>r,ix.push_back({l,i,0}),
        ix.push_back({r,i,1}),L[i]=l,Pi[i]={l,r};
    sort(ix.begin(),ix.end(),[](nd&a,nd&b){
        return a.u==b.u?a.tag<b.tag:a.u<b.u;});
    vector<int> A1(n),A2(n);
    rbt<pair<int,int>> St;
    rbt<pair<int,int>,comp> Ed;//tree St:未结束的区间开头,Ed:结束了的区间开头
    vector<int> del;
    cir(i,0,ix.size()){
        int si=i;
        while(i!=ix.size()-1&&ix[i+1].u==ix[i].u
            &&ix[i+1].tag==ix[i].tag) ++i;
        if(!ix[i].tag){
            cir(j,si,i+1) St.insert({ix[i].u,++cnt});
        }else{
            cir(j,si,i+1) Ed.insert({L[ix[j].id],++cnt});
            cir(j,si,i+1) A1[ix[j].id]=Ed.order_of_key({L[ix[j].id],_inf})-1;
            cir(j,si,i+1) A2[ix[j].id]=St.order_of_key({L[ix[j].id],_inf})-1;
            cir(j,si,i+1) St.erase(St.lower_bound({L[ix[j].id],-1}));
        }
    }
    for(auto&i:A1) cout<<(bool)(i)<<' ';cout<<'\n';
    for(auto&i:A2) cout<<(bool)(i)<<' ';cout<<'\n';
    return 0;
}