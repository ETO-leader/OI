#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream fcin("seq.in");
ofstream fcout("seq.out");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} use_fileio;
using lint=long long;
using VI=vector<lint>;
class math{
private:
    int MOD;
public:
    lint qpow(lint a,lint b){
        lint res=1;
        while(b){
            if(b&1) (res*=a)%=MOD;
            (a*=a)%=MOD;b>>=1;
        }
        return res;
    }
    auto inv(lint x){return qpow(x,MOD-2);}
    auto init(int n,int m){
        VI C(m);C[0]=1;
        cir(i,1,m){
            C[i]=C[i-1]*(n-i+1)%MOD*inv(i)%MOD;
        }
        return C;
    }
    math(int p):MOD(p){}
};
int main(){
    ios::sync_with_stdio(false),fcin.tie(0);
    int p,q;fcin>>p>>q;math mth(p);
    while(q--){
        int n,m;fcin>>n>>m;
        //Brute Force
        vector<VI> D(n+1,VI(m+1));
        D[0][0]=1;
        cir(i,1,n+1) cir(j,0,m+1){
            D[i][j]=D[i-1][j];
            if(j) (D[i][j]+=D[i][j-1])%=p;
        }
        cout<<[&](){
            lint ans=0;
            cir(i,1,m+1) (ans+=D[n][i])%=p;
            return ans;
        }()<<'\n';
    }
    return 0;
}
