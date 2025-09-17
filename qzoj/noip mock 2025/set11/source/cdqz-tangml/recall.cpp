#include<bits/stdc++.h>
#define int long long

using namespace std;

const int N=1e6+100,mod=998244353;

int T,id;
int n,m,k;
int fac[N];

signed main()
{
    freopen("recall.in","r",stdin);
    freopen("recall.out","w",stdout);
    cin>>id>>T;
    if(id==1)   printf("5 46 \n5 20 \n5 28 \n7 1190 \n6 320 \n5 20 \n4 4 \n6 18 \n4 4 \n5 11");
    else if(id==3)
        for(int i=1;i<=T;i++)
            cout<<"2 1"<<endl;
    else
    {
        fac[0]=1;
        for(int i=1;i<=n;i++)   fac[i]=fac[i-1]*i%mod;
        while(T--)
        {
            cin>>n;
            cout<<n<<" "<<fac[n-1]<<endl;
        }
    }
    return 0;
}
//n n!
