#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream inf("ds.in");
ofstream ouf("ds.out");
using lint=long long;
class segment{
private:
    struct node{
        array<lint,2> valmx,valmn;
        array<int,2> lenmx,lenmn;
        lint tag;
        auto update(lint w){
            valmx[1]-=w;
            valmn[1]-=w;
            tag+=w;
        }
        node():valmx({0,0}),valmn({0,0}),lenmx({0,1}),lenmn({0,1}),tag(0){}
    };
    vector<node> tr;
    constexpr auto ls(auto u) const{return u*2;}
    constexpr auto rs(auto u) const{return u*2+1;}
    auto push_down(int u){
        tr[ls(u)].update(tr[u].tag);
        tr[rs(u)].update(tr[u].tag);
        tr[u].tag=0;
    }
    auto maintain(int u){
        // Update VALMX(0)
        [&]{
            const auto lw=tr[ls(u)].valmx[0]+tr[rs(u)].valmx[0];
            const auto rw=tr[ls(u)].valmx[1]-tr[rs(u)].valmn[1];
            const auto lc=tr[ls(u)].lenmx[0]+tr[rs(u)].lenmx[0];
            const auto rc=tr[ls(u)].lenmx[1]+tr[rs(u)].lenmn[1];
            if(lw>rw||(lw==rw&&lc<rc)) tr[u].valmx[0]=lw,tr[u].lenmx[0]=lc;
            else tr[u].valmx[0]=rw,tr[u].lenmx[0]=rc;
        }();
        // Update VALMX(1)
        [&]{
            const auto lw=tr[ls(u)].valmx[0]+tr[rs(u)].valmx[1];
            const auto rw=tr[ls(u)].valmx[1]-tr[rs(u)].valmn[0];
            const auto lc=tr[ls(u)].lenmx[0]+tr[rs(u)].lenmx[1];
            const auto rc=tr[ls(u)].lenmx[1]+tr[rs(u)].lenmn[0];
            if(lw>rw||(lw==rw&&lc<rc)) tr[u].valmx[1]=lw,tr[u].lenmx[1]=lc;
            else tr[u].valmx[1]=rw,tr[u].lenmx[1]=rc;
        }();
        // Update VALMN(0)
        [&]{
            const auto lw=tr[ls(u)].valmn[0]+tr[rs(u)].valmn[0];
            const auto rw=tr[ls(u)].valmn[1]-tr[rs(u)].valmx[1];
            const auto lc=tr[ls(u)].lenmn[0]+tr[rs(u)].lenmn[0];
            const auto rc=tr[ls(u)].lenmn[1]+tr[rs(u)].lenmx[1];
            if(lw<rw||(lw==rw&&lc<rc)) tr[u].valmn[0]=lw,tr[u].lenmn[0]=lc;
            else tr[u].valmn[0]=rw,tr[u].lenmn[0]=rc;
        }();
        // Update VALMN(1)
        [&]{
            const auto lw=tr[ls(u)].valmn[0]+tr[rs(u)].valmn[1];
            const auto rw=tr[ls(u)].valmn[1]-tr[rs(u)].valmx[0];
            const auto lc=tr[ls(u)].lenmn[0]+tr[rs(u)].lenmn[1];
            const auto rc=tr[ls(u)].lenmn[1]+tr[rs(u)].lenmx[0];
            if(lw<rw||(lw==rw&&lc<rc)) tr[u].valmn[1]=lw,tr[u].lenmn[1]=lc;
            else tr[u].valmn[1]=rw,tr[u].lenmn[1]=rc;
        }();
    }
    auto update(int u,int l,int r,int ql,int qr,auto w){
        if(r<ql||qr<l) return;
        if(ql-1<l&&r-1<qr) return tr[u].update(w);
        push_down(u);
        const auto mid=(l+r)/2;
        update(ls(u),l,mid,ql,qr,w);
        update(rs(u),mid+1,r,ql,qr,w);
        maintain(u);
    }
    const int n;
public:
    auto update(int l,int r,int d){
        update(1,0,n-1,l,r,d);
    }
    auto query(){
        return make_pair(tr[1].valmx[0],tr[1].lenmx[0]);
    }
    segment(int _n):tr(_n<<2),n(_n){}
};
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int T;inf>>T;
    while(T--) []{
        int n,q;inf>>n>>q;
        segment sg(n);
        cir(i,0,n){
            int w;inf>>w;
            sg.update(i,i,w);
        }
        cir(i,0,q){
            int op;inf>>op;
            if(!op){
                int l,r,d;inf>>l>>r>>d;--l;--r;
                sg.update(l,r,d);
            }else{
                const auto[v,l]=sg.query();
                ouf<<v<<' '<<l<<'\n';
            }
        }
    }();
    return 0;
}

