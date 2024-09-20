#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
class sparsetable{
private:
    static constexpr auto ups=21;
    vector<vector<int>> a;
    auto init(vector<int> x){
        const auto n=(int)(x.size());
        a.resize(ups,vector<int>(n));
        a[0]=x;
        cir(i,1,ups) cir(p,0,n-(1<<i)+1){
            a[i][p]=gcd(a[i-1][p],a[i-1][p+(1<<(i-1))]);
        }
    }
public:
    auto query(int l,int r){
        const auto ql=(int)(log2(r-l+1));
        return gcd(a[ql][l],a[ql][r-(1<<ql)+1]);
    }
    sparsetable(vector<int> x){init(x);}
};
constexpr auto vaild(int x){
    return (x&(-x))==x;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--) [&](){
        int n;cin>>n;vector<int> a(n);
        for(auto&i:a) cin>>i;
        auto ans=0ll;
        cir(i,0,n){
            auto p=i;
            while(p+1<n&&a[p+1]==a[p]) ++p;
            ans+=1ll*(p-i+1)*(p-i+2)/2;
            i=p;
        }
        vector<int> b(n-1);
        cir(i,0,n-1) b[i]=abs(a[i+1]-a[i]);
        sparsetable st(b);
        auto r=0;
        cir(l,0,n-1){
            r=max(l,r);
            while(r<n-1&&((!vaild(st.query(l,r))||(!b[r])))) ++r;
            ans+=n-1-r;
        }
        println("{}",ans);
    }();
    return 0;
}
