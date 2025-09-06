#include<bits/extc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream inf("sequence.in");
ofstream ouf("sequence.out");
using lint=long long;
namespace __gnu_pbds{
    template<typename _Ty,class comp>
    using rbt=tree<_Ty,null_type,comp,rb_tree_tag,
        tree_order_statistics_node_update>;
}
using __gnu_pbds::rbt;
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int T;inf>>T;
    while(T--) []{
        int n,l,k;inf>>n>>l>>k;
        vector<lint> a(n);
        for(auto&i:a) inf>>i;
        auto ansmx=0ll,ansmn=0ll;
        auto calc=[&](vector<int> b,int uk){
            auto res=0ll;
            rbt<int,less_equal<int>> tr;
            cir(i,0,l-1) tr.insert(b[i]*2);
            cir(i,0,n-l+1){
                if(i) tr.erase(tr.upper_bound(b[i-1]*2-1));
                tr.insert(b[i+l-1]*2);
                res+=(*tr.find_by_order(uk))/2;
            }
            return res;
        };
        sort(a.begin(),a.end(),greater<>());
        [&]{
            vector<int> na;
            auto lp=0,rp=n-1;
            cir(i,0,n) if(i%l<(l-k)){
                na.emplace_back(a[rp]);
                --rp;
            }else{
                na.emplace_back(a[lp]);
                ++lp;
            }
            ansmx=calc(na,l-k);
        }();
        const auto mx=*max_element(a.begin(),a.end());
        for(auto&x:a) x=mx-x;
        reverse(a.begin(),a.end());
        [&]{
            vector<int> na;
            auto lp=0,rp=n-1;
            cir(i,0,n) if(i%l<k-1){
                na.emplace_back(a[rp]);
                --rp;
            }else{
                na.emplace_back(a[lp]);
                ++lp;
            }
            ansmn=mx*(n-l+1)-calc(na,k-1);
        }();
        ouf<<ansmx<<' '<<ansmn<<'\n';
    }();
    return 0;
}
