#include<bits/stdc++.h>
#include<bits/extc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace __gnu_pbds;
using namespace std;
using lint=long long;
template<typename _Ty,class comp>
using rbt=tree<_Ty,null_type,comp,rb_tree_tag,
    tree_order_statistics_node_update>;
class blocks{
private:
    vector<int> a,bid;
    vector<lint> pre,suf;
    vector<vector<lint>> f,blcc;
    vector<pair<int,int>> rng;
    vector<vector<pair<int,int>>> bx;
    auto w(int l,int r,int ql,int qr){
        const auto fl=bid[l],fr=bid[r];
        vector<pair<int,bool>> lx,rx;
        for(auto&[w,p]:bx[fl]) if(l-1<p&&p-1<r){
            lx.emplace_back(w,false);
        }
        for(auto&[w,p]:bx[fr]) if(ql-1<p&&p-1<qr){
            rx.emplace_back(w,true);
        }
        auto res=decltype(lx)(lx.size()+rx.size());
        ranges::merge(lx,rx,res.begin());
        auto resw=0ll;
        for(auto i=-1;auto&[a,b]:res) ++i,resw+=i*res[i].second;
        return resw;
    }
    auto init(){
        const auto n=(int)(a.size());
        const auto sqr=(int)(sqrt(n+1));
        for(auto i=0;i<n;i+=sqr){
            rng.emplace_back(i,i+sqr-1);
            cir(p,i,i+sqr) bid[p]=(int)(rng.size())-1;
            cir(p,i,i+sqr) bx[bid[p]].emplace_back(a[p],p);
        }
        for(auto&x:bx) ranges::sort(x);
        for(auto&[l,r]:rng){
            rbt<int,greater_equal<int>> prq;
            cir(i,l,r+1){
                pre[i]=prq.order_of_key(a[i]);
                prq.insert(a[i]);
            }
            rbt<int,less_equal<int>> sfq;
            for(auto i=r;i>l-1;--i){
                suf[i]=sfq.order_of_key(a[i]);
                sfq.insert(a[i]);
            }
        }
        const auto sqrln=(int)(rng.size());
        f.resize(sqrln,vector<lint>(sqrln));
        cir(i,0,sqrln) f[i][i]=pre[rng[i].second];
        cir(len,2,sqrln+1) cir(l,0,sqrln-len+1){
            const auto r=l+len-1;
            f[l][r]=f[l+1][r]+f[l][r-1]-f[l+1][r-1]+
                w(rng[l].first,rng[l].second,rng[r].first,rng[r].second);
        }
        blcc.resize(sqrln,vector<lint>(n));
        cir(i,0,n) ++blcc[bid[i]][a[i]-1];
        for(auto&x:blcc) cir(i,1,n) x[i]+=x[i-1];
        cir(i,1,sqrln) cir(j,0,n) blcc[i][j]+=blcc[i-1][j];
    }
public:
    auto query(int l,int r){
        
    }
};
