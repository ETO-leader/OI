#include<bits/stdc++.h>
#include<bits/extc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream fcin("subsequence.in");
ofstream fcout("subsequence.out");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} use_fileio;
using lint=long long;
using VI=vector<lint>;
static constexpr int MOD=1e9+7;
class bit2d{
private:
    vector<VI> a;
    constexpr auto lowbit(int x){return x&(-x);}
    auto __insert(int r,int p,lint x){
        for(++p;p<a[r].size();p+=lowbit(p)){
            (a[r][p]+=x)%=MOD;
        }
    }
    auto __query(int r,int p){
        lint res=0;
        for(++p;p;p-=lowbit(p))
            (res+=a[r][p])%=MOD;
        return res;
    }
public:
    auto insert(int r,int c,lint x){
        for(++r;r<a.size();r+=lowbit(r)){
            __insert(r,c,x);
        }
    }
    auto query(int r,int c){
        lint res=0;
        for(++r;r;r-=lowbit(r))
            (res+=__query(r,c))%=MOD;
        return res;
    }
    bit2d(int _n,int _m):a(_n+1,VI(_m+1)){}
};
class hashvec{
public:
    auto operator()(const VI&a) const{
        size_t res=0;
        for(auto&i:a) ((res%=998244353)<<=7)^=(unsigned)(i);
        return res;
    }
};
int main(){
    ios::sync_with_stdio(false),fcin.tie(0);
    int T;fcin>>T;
    while(T--){
        int n;fcin>>n;VI a(n);
        for(auto&i:a) fcin>>i,--i;
        vector<VI> st(n,VI(n));
        for(auto&i:st) for(auto&x:i){
            char c;fcin>>c;x=c-'0';
        }
        if(n<25){
            __gnu_pbds::gp_hash_table<size_t,int> ax;
            cir(s,1,(1<<n)) [&](){
                VI ak;
                cir(i,0,n) if(s&(1<<i)) ak.push_back(a[i]);
                cir(i,1,(int)(ak.size())){
                    if(!st[ak[i-1]][ak[i]]) return;
                }
                ++ax[hashvec()(ak)];
            }();
            lint ans=0;
            for(auto&[ak,bk]:ax) (ans+=bk*bk%MOD*bk)%=MOD;
            fcout<<ans<<'\n';
            continue;
        }
        vector<vector<VI>> D(n,vector<VI>(n,VI(n)));
        //                 pos1         pos2  pos3
        //pos1 ≥ pos3 ≥ pos2
        vector<bit2d> stx(n,bit2d(n,n));
        vector<VI> posx(n),fath(n);
        cir(i,0,n) posx[a[i]].push_back(i);
        cir(i,0,n) fath[i].push_back(n);
        cir(i,0,n) cir(j,0,n) if(st[j][i])
            fath[i].push_back(j);
        cir(i,0,n){
            for(auto&x:posx[a[i]]){
                for(auto&y:posx[a[i]]) if(x<y+1&&x<i+1&&y<i+1){
                    const auto xwx=(i==x&&i==y?1:(i==x||i==y||x==y?2:6));
                    for(auto&p:fath[a[i]]){
                        D[i][x][y]+=(p==n?1:stx[p].query(x-1,y-1))*xwx;
                    }
                    clog<<i<<' '<<x<<' '<<y<<":"<<D[i][x][y]<<' '<<xwx<<'\n';
                }
            }
            for(auto&x:posx[a[i]]){
                for(auto&y:posx[a[i]]) if(x<y+1&&x<i+1){
                    stx[a[i]].insert(x,y,D[i][x][y]);
                }
            }
        }
        lint ans=0;
        cir(i,0,n) cir(x,0,n) cir(y,0,n)
            (ans+=D[i][x][y])%=MOD;
        fcout<<ans<<'\n';
    }
    return 0;
}
