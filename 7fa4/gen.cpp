#include<bits/stdc++.h>
using namespace std;
#define int long long
#define rep(i,a,b) for(int i=a;i<=b;i++)
mt19937_64 rnd(5466666);
int rdint(int x,int y){
    return (rnd())%(y-x+1)+x;
}
int tn;
signed main(){
    int n=100000ll;int m=100000ll;
    printf("%lld %lld\n",n,m);tn=n;
    rep(i,1,n)printf("%lld ",rdint(0ll,2000ll)-1000ll);
    puts("");
    rep(i,1,m){
        int op;
        if(rdint(1,10)<5)op=rdint(1,2);
        else if(rdint(1,10)>5)op=5;
        else{
            if(i<=m/2)op=3;
            else op=4;
        }
        if(op==3)op=rdint(1,3);
        int l,r;l=rdint(1ll,n);r=rdint(1ll,n);
        if(l>r)swap(l,r);
        if(op==3||op==4){
            r=min(l+rdint(1,1000000000),n);
        }
        if(n-(r-l+1)<10000ll)op=3;
        if(n<=10000ll){
            op=3;
        }
        if(tn>=9000000000000ll){
            op=5;
        }
        if(op==1){
            int x;x=rdint(0ll,2000ll)-1000ll;
            printf("%lld %lld %lld %lld\n",op,l,r,x);
        }else if(op==2){
            printf("%lld %lld %lld\n",op,l,r);
        }else if(op==3){
            int p;p=rdint(1ll,n);
            printf("%lld %lld %lld %lld\n",op,l,r,p);
            tn+=r-l+1;
            n+=r-l+1;
        }else if(op==4){
            printf("%lld %lld %lld\n",op,l,r);
            n-=r-l+1;
        }else if(op==5){
            printf("%lld %lld %lld\n",op,l,r);
        }
    }
    return 0;
}
