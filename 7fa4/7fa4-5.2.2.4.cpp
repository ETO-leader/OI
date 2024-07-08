#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
struct cube{
    array<int,3> l,r;
    lint getsize(){
        lint res=1;
        cir(i,0,3) res*=(r[i]-l[i]);
        return res;
    }
    bool operator&(const cube c) const{
        cir(i,0,3) if(r[i]<c.l[i]+1||l[i]>c.r[i]-1)
            return false;
        return true;
    }
    cube(int x,int y,int z,int _r){
        l[0]=x-_r;l[1]=y-_r;l[2]=z-_r;
        r[0]=x+_r;r[1]=y+_r;r[2]=z+_r;
    }
};
vector<cube> cbs;
void cut(cube cx,cube c,int d){
    if(d>2) return;
    const int k1=max(cx.l[d],c.l[d]);
    const int k2=min(cx.r[d],c.r[d]);
    auto setc=[&](cube&cb){
        cir(i,0,d)
            cb.l[i]=c.l[i],cb.r[i]=c.r[i];
    };
    if(k1>cx.l[d]){
        cube psh=cx;setc(psh);psh.r[d]=k1;
        cbs.push_back(psh);
    }
    if(k2<cx.r[d]){
        cube psh=cx;setc(psh);psh.l[d]=k2;
        cbs.push_back(psh);
    }
    cube nxt=c;
    nxt.l[d]=k1;nxt.r[d]=k2;
    cut(cx,nxt,d+1);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;
    cir(i,0,n){
        int x,y,z,r;cin>>x>>y>>z>>r;
        const auto tcb=cube(x,y,z,r);
        cir(k,0,cbs.size()) if(tcb&cbs[k]){
            cut(cbs[k],tcb,0);
            cbs[k]=cbs.back();cbs.pop_back();
            --k;
        }
        cbs.push_back(tcb);
    }
    lint ans=0;
    for(auto&i:cbs) ans+=i.getsize();
    cout<<ans<<'\n';
    return 0;
}
