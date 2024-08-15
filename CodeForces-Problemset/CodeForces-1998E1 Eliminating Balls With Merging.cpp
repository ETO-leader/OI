#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
template<typename _Ty>
class sparsetable{
private:
    vector<vector<_Ty>> a;
    auto init(vector<_Ty> arr){
        const auto n=(int)(arr.size());
        const auto lgx=(int)(log2(n)+2);
        a.resize(lgx,vector<_Ty>(n));
        a[0]=arr;
        cir(i,1,lgx) cir(p,0,n-(1<<i)+1){
            a[i][p]=max(a[i-1][p],a[i-1][p+(1<<(i-1))]);
        }
    }
public:
    auto query(int l,int r){
        const auto lgx=(int)(log2(r-l+1));
        return max(a[lgx][l],a[lgx][r-(1<<lgx)+1]);
    }
    sparsetable(vector<_Ty> arr){init(arr);}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--) [&](){
        int n,x;cin>>n>>x;vector<int64_t> a(n);
        for(auto&i:a) cin>>i;
        sparsetable st([&](){
            vector<pair<int,int>> qst;
            cir(i,0,n) qst.push_back({a[i],i});
            return qst;
        }());
        vector nok(n+1,(int)(false));auto pre=a;
        cir(i,1,n) pre[i]+=pre[i-1];
        auto divide=[&](auto __self,int l,int r)->void {
            if(l>r-1) return;
            const auto mid=st.query(l,r).second;
            __self(__self,l,mid-1);
            __self(__self,mid+1,r);
            const auto lw=(mid?pre[mid-1]:0)-(l?pre[l-1]:0);
            const auto rw=pre[r]-pre[mid];
            if(a[mid]>lw) ++nok[l],--nok[mid];
            if(a[mid]>rw) ++nok[mid+1],--nok[r+1];
        };
        divide(divide,0,n-1);
        cir(i,1,n) nok[i]+=nok[i-1];
        nok.pop_back();
        cout<<ranges::count(nok,false)<<'\n';
    }();
    return 0;
}
