#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int maxn=1e6+5;
struct BIT{
  int tr[maxn];
  void clear(){memset(tr,0,sizeof tr);}
  inline int lowbit(int x){return x&-x;}
  int query(int x){
    int ret(0);
    for(int i=x;i;i-=lowbit(i)) ret+=tr[i];
    return ret;
  }
  void add(int x,int val){
    for(int i=x;i<=1e6;i+=lowbit(i))
      tr[i]+=val;
  }
}T;
int n,k,a[maxn];
bool solve0(){
  int res=0;
  for(int i=1;i<=n;i++)
    T.add(a[i],1),res+=i-T.query(a[i]);
  if(res!=k)return 0;
  return cout<<0<<endl,1;
}
bool solve1(){
  T.clear();
  int res=0,ret=0;
  for(int i=1;i<=n;i++)
    T.add(a[i],1),res+=i-T.query(a[i]);
  res-=k;
  T.clear();
  for(int l=1,r=1;r<=n;r++){
    T.add(a[r],1),ret+=(r-l+1)-T.query(a[r]);
    while(ret>res&&l<=r)ret-=T.query(a[l])-1,T.add(a[l++],-1);
    if(ret==res)return cout<<1<<endl<<l<<' '<<r<<endl,1;
  }
  return 0;
}
int res[maxn];
bool solve2(){
  T.clear();
  for(int i=1;i<=n;i++)
    T.add(a[i],1),res[i]=i-T.query(a[i]);
  while(k>res[n])k-=res[n--];
  if(res[n]==k){
    cout<<1<<endl;
    cout<<1<<' '<<n-1<<endl;
    return 1;
  }
  cout<<2<<endl;
  cout<<1<<' '<<n-1<<endl;
  int cnt=0;sort(a+1,a+n);
  for(int i=1;i<=n;i++){
    if(a[i]>a[n])cnt++;
    if(cnt==k+1){
      cout<<i<<' '<<n<<endl;
      return 1;
    }
  }
  return 1;
}
signed main(){
  ios::sync_with_stdio(0);cin.tie(0);
  freopen("reverse.in","r",stdin);
  freopen("reverse.out","w",stdout);
  int subid;cin>>subid;
  cin>>n>>k;for(int i=1;i<=n;i++)cin>>a[i];
  if(solve0()) return 0;
  if(solve1()) return 0;
  if(solve2()) return 0;
  return 0;
}
