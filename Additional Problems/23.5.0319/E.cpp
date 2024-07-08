#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
struct quary{
    int l,r,qid;
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;vector<int> v(n);
    unordered_map<int,int> apt;
    for(auto&i:v) cin>>i;
    int cnx=-1,q;cin>>q;vector<quary> vq(q);
    for(auto&[l,r,id]:vq) cin>>l>>r,--l,--r,id=++cnx;
    const int blc_sz=sqrt(n)+1;
    sort(vq.begin(),vq.end(),[&](quary&a,quary&b){
        return a.l/blc_sz==b.l/blc_sz?a.r<b.r:a.l<b.l;
    });
    int rl=0,rr=0,anx=0;apt[v[0]]=1;
    auto ers=[&](int vx){anx-=((--apt[vx])&1);};
    vector<int> ans(q);
    for(auto&[l,r,id]:vq){
        while(rl<l) ers(v[rl]),++rl;
        while(rr<r)
            ++rr,anx+=(apt[v[rr]]&1),apt[v[rr]]++;
        while(rl>l)
            --rl,anx+=(apt[v[rl]]&1),apt[v[rl]]++;
        while(rr>r) ers(v[rr]),--rr;
        ans[id]=anx;
    }
    for(auto&i:ans) cout<<i<<'\n';
    return 0;
}
