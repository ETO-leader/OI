#include<bits/stdc++.h>
#if defined(__linux)
    #include<bits/extc++.h>
#else
    #include<ext/pb_ds/assoc_container.hpp>
#endif
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace __gnu_pbds;
using namespace std;
template<typename _Ty,class comp=less<_Ty>>
using rbt=tree<_Ty,null_type,comp,rb_tree_tag,
    tree_order_statistics_node_update>;
class prefinder{
private:
    vector<int> pre;
public:
    auto update(int p,int k){
        pre[p]+=k;
    }
    auto init(){
        cir(i,1,(int)(pre.size())) pre[i]+=pre[i-1];
    }
    auto fnd(int x){
        const auto lb=lower_bound(pre.begin(),pre.end(),x);
        if(lb==pre.end()) return -1;
        return *lb==x?(int)(lb-pre.begin()):-1;
    }
    prefinder(int _n):pre(_n){}
};
class squbit{
private:
    vector<rbt<int,less_equal<int>>> a;
    constexpr auto lowbit(int x){return x&(-x);}
public:
    auto update(int x,int y){
        for(++x;x<(int)(a.size());x+=lowbit(x)){
            a[x].insert(y);
        }
    }
    auto query(int x,int y){
        auto res=0;
        for(++x;x;x-=lowbit(x)) res+=a[x].order_of_key(y+1);
        return res;
    }
    auto range(){return (int)(a.size())-2;}
    squbit(int _n):a(_n+1){}
};
auto check(vector<int> a,prefinder&px,prefinder&py,squbit&sq){
    const auto qxa=a[0]+a[3]+a[6];
    const auto qxb=a[1]+a[4]+a[7];
    const auto xla=px.fnd(qxa);
    const auto xlb=px.fnd(qxa+qxb);
    if(xla<0||xlb<0) return;
    const auto qya=a[0]+a[1]+a[2];
    const auto qyb=a[3]+a[4]+a[5];
    const auto yla=py.fnd(qya);
    const auto ylb=py.fnd(qya+qyb);
    if(yla<0||ylb<0) return;
    if(sq.query(xla,yla)!=a[0]) return;
    if(sq.query(xla,ylb)-a[0]!=a[3]) return;
    if(sq.query(xlb,yla)-a[0]!=a[1]) return;
    if(sq.query(xlb,ylb)-a[0]-a[1]-a[3]!=a[4]) return;
    if(sq.query(sq.range(),yla)-a[0]-a[1]!=a[2]) return;
    if(sq.query(sq.range(),ylb)-a[0]-a[1]-a[2]-a[3]-a[4]!=a[5]) return;
    throw vector{xla,xlb,yla,ylb};
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;vector<pair<int,int>> ps(n);
    map<int,int> idx,idy;
    for(auto&[x,y]:ps){
        cin>>x>>y;
        idx.insert({x,0});idy.insert({y,0});
    }
    for(auto c=0;auto&[a,b]:idx) b=c++;
    for(auto c=0;auto&[a,b]:idy) b=c++;
    prefinder px(n+7),py(n+7);
    squbit bx(n+7);
    for(auto&[x,y]:ps){
        x=idx[x];y=idy[y];
        px.update(x,1);py.update(y,1);
        bx.update(x,y);
    }
    vector<int> a(9);
    px.init();py.init();
    for(auto&i:a) cin>>i;
    auto rid=[&](map<int,int>&x,int w){
        for(auto&[a,b]:x) if(b==w) return a;
        return -1;
    };
    sort(a.begin(),a.end());
    do{
        try{
            check(a,px,py,bx);
        }catch(vector<int> ans){
            cout<<fixed<<setprecision(15)<<rid(idx,ans[0])+0.114514<<' '<<rid(idx,ans[1])+0.114514<<'\n';
            cout<<fixed<<setprecision(15)<<rid(idy,ans[2])+0.114514<<' '<<rid(idy,ans[3])+0.114514<<'\n';
            exit(0);
        }
    }while(next_permutation(a.begin(),a.end()));
    cout<<-1<<'\n';
    return 0;
}
