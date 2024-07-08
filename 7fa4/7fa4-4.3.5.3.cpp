#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using db=long double;
using VD=vector<db>;
void gauss(vector<VD>&a){
    const int n=a.size();
    cir(i,0,n){
        int r=i;
        cir(j,i+1,n){
            if(fabs(a[j][i])>fabs(a[r][i]))
                r=j;
        }
        if(i!=r) swap(a[i],a[r]);
        cir(j,0,n) if(i!=j){
            const auto w=a[j][i]/a[i][i];
            cir(k,i+1,n+1)
                a[j][k]-=a[i][k]*w;
        }
    }
}
void istreamflushline(istream&is){
    string none;
    getline(is,none);getline(is,none);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;
    vector<VD> a(n,VD(n+1));
    cir(i,0,n-1){
        a[i][i]=1-n;
        cir(j,0,n){
            db p;cin>>p;
            if(i!=j) a[i][j]=p,a[i][i]+=p;
        }
    }
    istreamflushline(cin);
    fill(a[n-1].begin(),a[n-1].end(),1);
    gauss(a);
    cir(i,0,m){
        db ans=0;
        string s;cin>>s;
        cir(i,0,n) if(s[i]-'0')
            ans+=a[i][n]/a[i][i];
        cout<<fixed<<setprecision(8)<<ans<<'\n';
    }
    return 0;
}
