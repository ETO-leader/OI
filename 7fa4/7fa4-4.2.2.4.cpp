#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using db=double;
struct point{db x,y;};
//A line: y=ax+b
struct line{
    db a,b;
    point intersect(line l){
        if(a==l.a) abort();
        const int rx=(l.b-b)/(a-l.a);
        return {rx,a*rx+b};
    }
};
line initline(lint px,lint py){
    line res;res.a=-1;res.b=py+px;
    return res;
}
struct triangle{
    point p;line yl,cl;
    bool siz0tag;
    triangle&merge(const triangle&tr){
        if(siz0tag||tr.siz0tag){
            siz0tag=true;return*this;
        }
        line rl=(cl.b<tr.cl.b?cl:tr.cl);
        p.x=max(p.x,tr.p.x);p.y=max(p.y,tr.p.y);
        if(initline(p.x,p.y).b>rl.b){
            siz0tag=true;return*this;
        }
        yl={0,p.y};cl=rl;
        return*this;
    }
    lint size(){
        if(siz0tag) return 0;
        const lint el=cl.intersect(yl).x-p.x;
        return el*el;
    }
    triangle(lint x,lint y,lint l):siz0tag(false){
        yl={0,(db)(y)};cl=initline(x,y+l);
        p={(db)(x),(db)(y)};
    }
};
const triangle maxtr(-1,-1,(lint)(1e9+7));
lint calci(int state,vector<triangle>&tr){
    triangle res(maxtr);
    cir(i,0,tr.size()) if(state&(1<<i))
        res.merge(tr[i]);
    return res.size()*
        (__builtin_popcount(state)&1?1:-1);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;vector<triangle> tr(n,maxtr);
    for(auto&i:tr){
        lint x,y,l;cin>>x>>y>>l;
        i=triangle(x,y,l);
    }
    lint ans=0;
    cir(i,1,1<<n) ans+=calci(i,tr);
    cout<<ans<<'\n';
    return 0;
}
