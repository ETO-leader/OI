#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
#if not defined(__glibcxx_ranges)
namespace ranges{
    auto sort(auto&x,auto cmp){
        std::sort(x.begin(),x.end(),cmp);
    }
    auto max_element(auto&x){
        return std::max_element(x.begin(),x.end());
    }
}
#endif
constexpr auto sign(auto x){
    return (decltype(x))(x<0?-1:1);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,q;cin>>n>>q;vector<int> a(n);
    for(auto&i:a) cin>>i;
    struct qry{int l,r,id;};
    struct qrypos{int l,r,p,id;};
    vector<qry> qs(q);
    for(auto c=-1;auto&[l,r,id]:qs) cin>>l>>r,--l,--r,id=++c;
    const auto sqr=(int)(sqrt(n+7));
    vector<lint> grt(n);
    const auto maxa=*ranges::max_element(a);
    vector<vector<int>> fctr(maxa+7);
    auto at=[&](auto&a,int p){
        return p<0?0:a[p];
    };
    [&](){
        vector<int> cls(maxa+7),cgr(maxa+7);
        cir(i,0,n){
            if(fctr[a[i]].empty()){
                for(auto x=1;x*x<a[i]+1;++x) if(!(a[i]%x)){
                    fctr[a[i]].push_back(x);
                    grt[i]+=cgr[x];++cls[x];
                    if(x*x<a[i]) grt[i]+=cgr[a[i]/x],++cls[a[i]/x];
                }
            }else{
                for(auto&x:fctr[a[i]]){
                    grt[i]+=cgr[x];++cls[x];
                    if(x*x<a[i]) grt[i]+=cgr[a[i]/x],++cls[a[i]/x];
                }
            }
            grt[i]+=at(grt,i-1)+cls[a[i]];++cgr[a[i]];
        }
    }();
    ranges::sort(qs,[&](qry&a,qry&b){
        return a.l/sqr==b.l/sqr?a.r<b.r:a.l<b.l;
    });
    vector<lint> ans(q);
    vector<qrypos> qp;
    [&](){
        auto l=0,r=-1;
        for(auto&[ql,qr,id]:qs){
            auto delta=0ll;
            if(r<qr){
                delta+=at(grt,qr)-at(grt,r);
                qp.push_back({r+1,qr,l-1,-(id+1)});
                r=qr;
            }
            if(ql<l){
                delta-=at(grt,l-1)-at(grt,ql-1);
                qp.push_back({ql,l-1,r,id+1});
                l=ql;
            }
            if(r>qr){
                delta-=at(grt,r)-at(grt,qr);
                qp.push_back({qr+1,r,l-1,id+1});
                r=qr;
            }
            if(ql>l){
                delta+=at(grt,ql-1)-at(grt,l-1);
                qp.push_back({l,ql-1,r,-(id+1)});
                l=ql;
            }
            ans[id]=delta;
        }
    }();
    ranges::sort(qp,[&](auto&a,auto&b){
        return a.p<b.p;
    });
    const auto lim=min(114,maxa);
    [&](){
        vector<int> cx(maxa+7);auto px=-1;
        for(auto&[ql,qr,p,id]:qp){
            while(px<p){
                ++px;
                for(auto&x:fctr[a[px]]){
                    ++cx[x];
                    if(x*x<a[px]) ++cx[a[px]/x];
                }
                if(a[px]>lim){
                    for(auto x=a[px];x<maxa+7;x+=a[px]) ++cx[x];
                }
            }
            cir(i,ql,qr+1) ans[abs(id)-1]+=sign(id)*cx[a[i]];
        }
    }();
    [&](){
        cir(w,1,lim+1){
            vector<lint> pm(n),pf(n);
            cir(i,0,n){
                pm[i]+=at(pm,i-1)+(a[i]==w);
                pf[i]+=at(pf,i-1)+(!(a[i]%w));
            }
            for(auto&[ql,qr,p,id]:qp){
                ans[abs(id)-1]+=sign(id)*(at(pm,p)*(at(pf,qr)-at(pf,ql-1)));
            }
        }
    }();
    vector<int> rk;
    for(auto&[ql,qr,id]:qs) rk.push_back(id);
    cir(i,1,q) ans[rk[i]]+=ans[rk[i-1]];
    for(auto&i:ans) cout<<i<<'\n';
    return 0;
}
