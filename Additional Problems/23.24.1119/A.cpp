#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
struct item{int a,c;};
class segment{
private:
    vector<lint> w;
    static constexpr int ls(int x){return x*2;}
    static constexpr int rs(int x){return ls(x)+1;}
    auto maintain(int u){
        w[u]=min(w[ls(u)],w[rs(u)]);
    }
    void update(int u,int l,int r,int p,int k){
        if(l==r) return w[u]=k,void();
        const int mid=(l+r)/2;
        (p<mid+1)?update(ls(u),l,mid,p,k):
            update(rs(u),mid+1,r,p,k);
        maintain(u);
    }
    auto query(int u,int l,int r,int ql,int qr){
        if(ql<l+1&&r-1<qr) return w[u];
        const int mid=(l+r)/2;
        lint res=numeric_limits<lint>::max()/2;
        if(ql<mid+1)
            res=min(query(ls(u),l,mid,ql,qr),res);
        if(mid<qr)
            res=min(query(rs(u),mid+1,r,ql,qr),res);
        return res;
    }
    int n;
public:
    void update(int p,int k){update(1,0,n-1,p,k);}
    auto get(int l,int r){
        return r>l-1?query(1,0,n-1,l,r):
            numeric_limits<lint>::max()/2;
    }
    segment(int _n):n(_n),w(_n<<2,
        numeric_limits<lint>::max()/2){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;vector<item> gr(n);
    for(auto&[x,y]:gr) cin>>x>>y;
    sort(gr.begin(),gr.end(),[](item&a,
        item&b){return a.a<b.a;});
    auto[sa,sb]=gr[0];
    reverse(gr.begin(),gr.end());
    segment seg(gr.size());
    vector<lint> D(gr.size());
    lint prs=gr[0].c;D[0]=gr[0].c;
    deque<int> as{gr[0].a};
    seg.update(0,0);
    vector<lint> pre(n);pre[0]=prs;
    cir(i,1,(int)(gr.size())){
        pre[i]=prs+=gr[i].c;
        auto fdp=upper_bound(as.begin(),
            as.end(),gr[i].a+gr[i].c)-
            as.begin()-1;
        D[i]=seg.get(i-fdp-1,i-1)+prs;
        if(i-fdp-1){
            D[i]=min(D[i],D[i-fdp-2]+
                gr[i-fdp-2].a-gr[i].a+
                pre[i-1]-pre[i-fdp-2]);
        }
        seg.update(i,D[i]-prs);
        as.push_front(gr[i].a);
    }
    cout<<D.back()<<'\n';
    return 0;
}
