#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
struct query{lint w,l,r,qt;};
void input(vector<query>&vx,int x,int y){
    lint px=0,py=0;
    vector<query> vw(x),vp(y);
    for(auto&[w,l,r,qt]:vw){
        cin>>w>>l;lint lx=l;
        l=px;r=(px+=lx);qt=0;
    }
    for(auto&[w,l,r,qt]:vp){
        cin>>w>>l;lint lx=l;
        l=py;r=(py+=lx);qt=1;
    }
    for(auto&i:vw) vx.push_back(i);
    for(auto&i:vp) vx.push_back(i);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    lint n,x,y;cin>>n>>x>>y;
    vector<query> vx;vx.reserve(x+y);
    input(vx,x,y);
    vx.push_back({-114514,n+1,n+1,0});
    vx.push_back({-1919810,n+1,n+1,0});
    sort(vx.begin(),vx.end(),
        [](query&a,query&b){return a.l<b.l;});
    vector<lint> px(2),pr(2),wx{-114514,-1919810};
    lint ans=0;
    for(auto&[w,l,r,qt]:vx){
        px[qt]=l;wx[qt]=w;pr[qt]=r;
        if(wx[qt]==wx[qt^1])
            ans+=min(r,pr[qt^1])-max(px[qt^1],l);
    }
    cout<<ans<<'\n';
    return 0;
}
