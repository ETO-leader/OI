#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
#ifndef ONLINE_JUDGE
ifstream inf("dye.in");
ofstream ouf("dye.out");
class fileio{
public:
    ~fileio(){
        inf.close();ouf.close();
    }
} use_fileio;
#else
auto&inf=cin;
auto&ouf=cout;
#endif
using lint=long long;
static constexpr auto MOD=998244353;
class mathbase{
public:
    constexpr auto qpow(lint a,auto b) const{
        auto res=1ll;
        while(b){
            if(b&1) (res*=a)%=MOD;
            (a*=a)%=MOD;b>>=1;
        }
        return res;
    }
    constexpr auto inv(auto x) const{
        return qpow(x,MOD-2);
    }
} math;
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int n,op;lint k;inf>>n>>k>>op;
    if(op==1){
        vector<vector<int>> vis(n*2,vector<int>(n*2));
        auto check=[&](auto __self,int l,int r,vector<int>&a){
            if(l>r) return true;
            cir(i,l+1,r+1) if(a[i]==a[l]){
                if(__self(__self,l+1,i-1,a)&&__self(__self,i+1,r,a)) return true;
            }
            return false;
        };
        set<vector<int>> ok;
        auto rotate=[&](vector<int> a){
            a.emplace(a.begin(),a.back());
            a.pop_back();
            return a;
        };
        vector<int> cur;
        auto dfs=[&](auto __self,const int c){
            if((int)(cur.size())==n*2){
                if((int)(set<int>(cur.begin(),cur.end()).size())<c) return;
                vis=vector<vector<int>>(n*2,vector<int>(n*2));
                if(!check(check,0,n*2-1,cur)) return;
                auto ncur=cur;
                cir(i,0,n*2) if(ok.count(ncur=rotate(ncur))) return;
                ok.emplace(cur);
                return;
            }
            cir(w,0,c){
                cur.emplace_back(w);
                __self(__self,c);
                cur.pop_back();
            }
        };
        auto cntc=[&](const int c){
            ok.clear();
            dfs(dfs,c);
            return (int)(ok.size());
        };
        const auto ans=(
            cntc(3)*(lint)(k)%MOD*(lint)(k-1)%MOD*(lint)(k-2)%MOD*math.inv(6)%MOD+
            cntc(2)*(lint)(k)%MOD*(lint)(k-1)%MOD*math.inv(2)+
            cntc(1)*(lint)(k)%MOD
        )%MOD;
        ouf<<ans<<'\n';
    }else{
        vector<vector<lint>> f(n*2+1,vector<lint>(n+7));
        f[0][0]=1;
        cir(i,0,n*2) cir(j,0,n+1){
            if(j) (f[i+1][j-1]+=f[i][j])%=MOD;
            (f[i+1][j+1]+=f[i][j]*(k-(j>0)))%=MOD;
        }
        ouf<<f[n*2][0]<<'\n';
    }
    return 0;
}
