#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class bit{
private:
    vector<int> a;
    constexpr auto lowbit(int x){return x&(-x);}
public:
    auto update(int u,int x){
        for(++u;u;u-=lowbit(u)) a[u]=max(a[u],x);
    }
    auto query(int u=0){
        auto res=0;
        for(++u;u<(int)(a.size());u+=lowbit(u)){
            res=max(res,a[u]);
        }
        return res;
    }
    bit(int _n):a(_n){}
};
struct qry{pair<long double,long double> x;int id;};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;long double a,b,c,d;char sp;
    cin>>n>>a>>sp>>b>>c>>sp>>d;
    auto getvector=[&](long double x,long double y){
        return pair(
            roundl(1.0l*(d*y-c*x)/(a*d-b*c)*10000000000ll),
            roundl(1.0l*(b*y-a*x)/(b*c-a*d)*10000000000ll)
        );
    };
    map<long double,int> idx;
    vector<qry> ar(n);
    for(auto c=-1;auto&i:ar){
        int x,y;cin>>x>>y;
        i.x=getvector(x,y);
        idx.insert({i.x.second,0.0l});
        i.x.second=-i.x.second;
        i.id=++c;
    }
    idx.insert({0.0l,0.0l});
    ++n;ar.push_back({pair(0.0l,0.0l),n-1});
    sort(ar.begin(),ar.end(),[](auto&a,auto&b){
        return a.x>b.x;
    });
    [&](){
        for(auto c=0;auto&[x,y]:idx) y=c++;
    }();
    bit bx(n+7);
    vector<int> fx(n);
    cir(i,0,n){
        const auto iy=idx[-ar[i].x.second];
        auto&f=fx[ar[i].id];f=bx.query(iy+1)+1;
        bx.update(iy,f);
    }
    cout<<fx[n-1]-1<<'\n';
    return 0;
}
