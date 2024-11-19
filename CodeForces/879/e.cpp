#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=unsigned long long;
static constexpr auto _infl=(lint)(1.2e9);
static constexpr auto maxvaild=(lint)(1.1e7);
class sparsetable{
private:
    static constexpr auto ups=21;
    vector<vector<lint>> ax;
    vector<int> lgx;
    auto init(vector<lint> a){
        const auto n=(int)(a.size());
        ax.resize(ups,vector<lint>(n));
        ax[0]=a;
        cir(c,1,ups) cir(i,0,n-(1<<c)+1){
            if(ax[c-1][i]==_infl||ax[c-1][i+(1<<(c-1))]==_infl) ax[c][i]=_infl;
            else ax[c][i]=min(lcm(ax[c-1][i],ax[c-1][i+(1<<(c-1))]),_infl);
        }
        lgx.resize(n+7);
        cir(i,2,n+1) lgx[i]=(lgx[i>>1]+1);
    }
public:
    auto query(int l,int r){
        const auto lg=lgx[r-l+1];
        const auto lx=ax[lg][l];
        const auto rx=ax[lg][r-(1<<lg)+1];
        if(lx==_infl||rx==_infl) return _infl;
        return min(lcm(lx,rx),_infl);
    }
    sparsetable(vector<lint> a){init(a);}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [](){
        int n;cin>>n;
        vector<lint> a(n);
        for(auto&i:a) cin>>i;
        sparsetable st(a);
        const auto maxans=n*50;
        vector<int> invaild(maxans);
        cir(i,0,n){
            auto nxt=i;
            auto cur=a[i];
            invaild[cur]=true;
            while(true){
                auto l=nxt+1,r=n-1,ans=-1;
                while(l-1<r){
                    const auto mid=midpoint(l,r);
                    const auto w=st.query(i,mid);
                    w>cur?((r=mid-1),(ans=mid)):(l=mid+1);
                }
                if(ans==-1) break;
                cur=st.query(i,ans);
                if(cur>maxans) break;
                invaild[cur]=true;
                nxt=ans;
            }
        }
        cir(i,0,maxans) if(!invaild[i]) return println("{}",i);
    }();
    return 0;
}
