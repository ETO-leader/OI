#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream fcin("tree.in");
ofstream fcout("tree.out");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} set_fileio;
using lint=__int128;
using VI=vector<lint>;
istream&operator>>(istream&is,lint&v){
    string s;is>>s;v=0;
    for(auto c:s) (v*=10)+=(c-'0');
    return is;
}
ostream&operator<<(ostream&os,lint v){
    if(v<0) cout<<'-',v=-v;
    if(v>9) os<<v/10;
    return (os<<(int)(v%10));
}
static constexpr int MOD=1e9+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;fcin>>n;
    auto fact=[](int x){
        VI res(x,1);
        cir(i,1,x) (res[i]=res[i-1]*i)%=MOD;
        return res;
    }(n+1);
    auto rngsum=[](lint l,lint r){
        return ((l+r)*(r-l+1)/2)%MOD;
    };
    auto getans1=[fact,rngsum](int x){
        lint res=0,pw=1;
        cir(i,1,x+1){
            if(i&1){
                (res+=rngsum(x/2+1,x)%MOD*pw
                    %MOD*fact.at((x+1)/2-1)%MOD)%=MOD;
            }else{
                (res+=(i/2)*pw%MOD*
                    fact.at((x+1)/2)%MOD)%=MOD;
            }
            (pw*=(x+1))%=MOD;
        }
        return res;
    };
    if(n&1){
        fcout<<n/2<<' '<<(fact.at(n/2+1)+
            (fact.at(n/2+1)-fact.at(n/2)+MOD)*(n/2))%MOD
            <<' '<<[fact,getans1,rngsum](lint x){
                VI pref(x+1),suff(x+1),
                    pw(x,1),preq(x+1),sufq(x+1);
                cir(i,1,x) pw[i]=pw[i-1]*(x+1)%MOD;
                lint ans=getans1(x);
                cir(i,1,x+1){
                    pref[i]=(pref[i-1]+pw[i-1]*
                        (i/2)*(!(i&1)))%MOD;
                    preq[i]=(preq[i-1]+
                        pw[i-1]*(i&1))%MOD;
                }
                suff[x]=pw[x-1]*((x+1)/2)%MOD;
                for(int i=x-1;i;--i){
                    suff[i]=(suff[i+1]+pw[i-1]*
                        ((i+1)/2)*(i&1))%MOD;
                    sufq[i]=(sufq[i+1]+pw[i-1]*
                        (!(i&1)))%MOD;
                }
                cir(i,1,x) if(!(i&1)){
                    (ans+=((pref[i-1]+suff[i+1])*
                        (fact.at(x/2+1)-fact.at(x/2)+MOD)%MOD+
                        ((preq[i-1]+sufq[i])*
                        (rngsum(x/2+2,x)+(i/2))%MOD*
                        fact.at(x/2)%MOD)-
                        ((preq[i-1]+sufq[i+1])*
                        (rngsum(x/2+2,x))%MOD*
                        fact.at(x/2-1)%MOD+
                        (i/2)*pw[i-1]%MOD*
                        fact.at(x/2)%MOD)%MOD+MOD))%=MOD;
                }
                return ans;
            }(n)<<'\n';
    }else{
        fcout<<n/2<<' '<<fact.at(n/2)
            <<' '<<getans1(n)<<'\n';
    }
    return 0;
}
