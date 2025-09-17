#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define pb push_back
#define fi first
#define se second
#define endl '\n'
#define mid ((l+r)>>1)
using namespace std;
bool mtd;
const int N=1e6+6;
int sum[N],a[N];
int S,n,k;
int lb(int x){return x&(-x);}
void add(int x,int y){while(x<=n)sum[x]+=y,x+=lb(x);}
int query(int x){int ans=0;while(x)ans+=sum[x],x-=lb(x);return ans;}
bool mtt;
signed main(){
    freopen("reverse.in","r",stdin);
    freopen("reverse.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
    cin>>S>>n>>k;
    for(int i=1;i<=n;i++)cin>>a[i];
    int cnt=0;
    for(int i=1;i<=n;i++)cnt+=query(n)-query(a[i]),add(a[i],1);
    if(cnt==k)return cout<<0,0;
    int need=cnt-k,now=0,j=1;
    memset(sum,0,sizeof(sum));
    for(int i=1;i<=n;i++){
        now+=query(n)-query(a[i]);
        add(a[i],1);
        while(j<i&&now>need){
            now-=query(a[j]-1);
            add(a[j],-1);
            j++;
        }
        if(now==need)return cout<<1<<'\n'<<j<<' '<<i,0;
    }
    memset(sum,0,sizeof(sum));
    for(int i=1;i<=n;i++)add(a[i],1);
    for(int i=n;i>=1;i--){
        now=query(n)-query(a[i]);
        add(a[i],-1);
        if(k>now)k-=now;
        else{
            cout<<2<<'\n'<<1<<' '<<i-1<<'\n';
            sort(a+1,a+i);
            cnt=0;
            for(int j=1;j<i;j++){
                cnt+=(a[j]>a[i]);
                if(cnt==k)return cout<<j+1<<' '<<i<<'\n',0;
            }
            break;
        }
    }
	return 0;
}
