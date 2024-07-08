#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto _inf=(int)(1e9+7);
class chtholly{
private:
    struct node{
        int l,r,w,id;
        auto operator<(const node&u) const{
            return l<u.l;
        }
        node(int _l=0,int _r=0,int _w=0,int _id=0):
            l(_l),r(_r),w(_w),id(_id){}
    };
    set<node> ch;
    auto split(int p){
        auto fd=prev(ch.upper_bound(node(p)));
        if(fd->l==p) return fd;
        const auto nl=fd->l,nr=fd->r,nw=fd->w,nid=fd->id;
        ch.erase(fd);
        ch.insert(node(nl,p-1,nw,nid));
        return ch.insert(node(p,nr,nw,nid)).first;
    }
    auto range(int l,int r){
        const auto ir=split(r+1),il=split(l);
        return pair(il,ir);
    }
public:
    auto assign(int l,int r,int w,int id){
        const auto[il,ir]=range(l,r);
        //cerr<<distance(il,ir)<<'\n';
        vector res(il,ir);
        ch.erase(il,ir);
        ch.insert(node(l,r,w,id));
        return res;
    }
    chtholly(int _sz){ch.insert(node(-_sz,_sz,-1,0));}
};
struct panel{int l,r,h;};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,mxh;cin>>n>>mxh;vector<panel> a(n);
    for(auto&[l,r,h]:a) cin>>h>>l>>r,--r;
    a.push_back({-_inf+7,_inf-7,mxh+7});
    sort(a.begin(),a.end(),[](auto&a,auto&b){
        return a.h<b.h;
    });
    chtholly cht(_inf);
    vector<int> f(n+2);f[0]=_inf*2;
    for(auto c=0;auto&[nl,nr,nh]:a){
        ++c;
        const auto chg=cht.assign(nl,nr,nh,c);
        auto mxh=-1;
        for(auto&[l,r,h,id]:chg) if(((!id)&&chg.size()==1)||(id&&l==max(a[id-1].l,nl)&&r==min(a[id-1].r,nr))){
            f[c]=max(f[c],min(f[id],min(nr,r)-max(nl,l)+1));
        }
    }
    cout<<f[n+1]<<'\n';
    return 0;
}
