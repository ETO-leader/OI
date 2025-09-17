#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=1000005;
int id,n,m,k,all,a[maxn],tree[maxn],cnt;
struct doing{
	int L,R;
}ans[maxn];
int read(){
	char ch=getchar();int ret=0,f=1;
	while(ch<'0'||ch>'9'){if(ch=='-') f=-f;ch=getchar();}
	while(ch>='0'&&ch<='9') ret=(ret<<3)+(ret<<1)+(ch&15),ch=getchar();
	return ret*f;
}
void add(int x,int v){
	for(;x<=n;x+=x&-x) tree[x]+=v;
}
int get(int x){
	int sum=0;
	for(;x;x-=x&-x) sum+=tree[x];
	return sum;
}
int ask(int L,int R){
	if(L>R) return 0;
	return get(R)-get(L-1);
}
signed main(){
	freopen("reverse.in","r",stdin);
	freopen("reverse.out","w",stdout);
	id=read(),n=read(),k=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=n;i++) all+=ask(a[i]+1,n),add(a[i],1);
	k=all-k;
	memset(tree,0,sizeof tree);
	while(k>0){
		int j=0,now=0,Max=0,MaxL=0,MaxR=0;
		for(int i=1;i<=n;i++){
			while(j<n&&now+ask(a[j+1]+1,n)<=k) j++,now+=ask(a[j]+1,n),add(a[j],1);
			if(now>Max) Max=now,MaxL=i,MaxR=j;
			add(a[i],-1);now-=ask(1,a[i]-1);
		}
		k-=Max;
		ans[++cnt]=(doing){MaxL,MaxR};
		sort(a+MaxL,a+MaxR+1);
	}
	printf("%lld\n",cnt);
	for(int i=1;i<=cnt;i++) printf("%lld %lld\n",ans[i].L,ans[i].R);
	return 0;
}
