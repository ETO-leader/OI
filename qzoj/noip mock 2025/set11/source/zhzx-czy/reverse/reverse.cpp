#include<bits/stdc++.h>
using namespace std;
#define int long long 
int id,n,k;
int a[1001001];
int tr[1001001],tr2[1001001];
vector<pair<int,int> >ans;
int lowbit(int x){
    return x&(-x);
}
void push(int x,int y){
    for (;x<=n;x+=lowbit(x))tr[x]+=y;
}
int get(int x){
    int sum=0;
    for (;x;x-=lowbit(x))sum+=tr[x];
    return sum;
}
void push2(int x,int y){
    for (;x;x-=lowbit(x))tr2[x]+=y;
}
int get2(int x){
    int sum=0;
    for (;x<=n;x+=lowbit(x))sum+=tr2[x];
    return sum;
}
signed main(){
    freopen("reverse.in","r",stdin);
    freopen("reverse.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>id>>n>>k;
    int zong=0;
    for (int i=1;i<=n;i++)
    cin>>a[i],zong+=get2(a[i]),push2(a[i],1);
    k=zong-k;
    // cout<<zong<<"~~~"<<k<<"\n";
    while(k){
        int w=0,sum=0;
        for (int i=1;i<=n;i++)tr[i]=tr2[i]=0;
        int mx=0,pl=0,pr=0;
        for (int i=1;i<=n;i++){
            if(w<i)w++,push(a[w],1),push2(a[w],1);
            while(w<n&&get2(a[w+1])+sum<=k){
                w++;sum+=get2(a[w]);push(a[w],1);push2(a[w],1);
            }
            if(mx<sum)mx=sum,pl=i,pr=w;
            // cout<<i<<" "<<w<<" "<<sum<<"\n";
            push(a[i],-1),push2(a[i],-1);sum-=get(a[i]);
        }
        k-=mx;
        sort(a+pl,a+pr+1);
        ans.push_back({pl,pr});
    }
    cout<<ans.size()<<"\n";
    for (auto i:ans)cout<<i.first<<" "<<i.second<<"\n";
}