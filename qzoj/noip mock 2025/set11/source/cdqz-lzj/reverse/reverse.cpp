// 你考虑排序过后的修改
// 选择最长的最接近k的区间，然后排序，然后再做一遍，调整
// 检测到超时：返回逆序对数量-K
// 我猜测，是不是数据再大两次也可以完成
// 我猜测，这个结论是正确的
// 你发现你没必要求出整个
// 你考虑排序两次怎么做
// 首先尺取法只能选一段
#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define int LL
#define pii pair<int,int>
#define rint register int
#define il inline
#define fi first
#define se second
#define fastio ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
const int N=1e6+5;
mt19937_64 engine(time(0));
int _,n,m,K,a[N],b[N],rev[N],tot,cnt;
pii ans[N];
unordered_map<int,int>cvt;
void EI(){
	// 如果没有rand=0，请让我过这道题
	LL lucky = engine()%998244353;
	if(lucky==0)exit(51);
	return ;
}
struct BIT{
	int A[N];
	il int lowbit(int x){return x&-x;}
	il void add(int x,int k){
		while(x<=n)A[x]+=k,x+=lowbit(x);return;
	}
	il int query(int x){
		int r=0;while(x)r+=A[x],x-=lowbit(x);return r;
	}
	il void clear(){
		memset(A,0,sizeof A);return;
	}
}bit;
il int getrev(int *arr){
	bit.clear();int res=0;
	for(rint i=1;i<=n;i++){
		rev[i]=(i-1)-bit.query(a[i]);
		bit.add(a[i],1);
		res+=rev[i];
	}
	return res;
}
il void bf(){
	int rst=tot-K;
	if(!rst){
		puts("0");
		return;
	}
	// 寻找尺取法当中最大的失败的位置，排序最大的那个，然后剩下的就考虑找到最大的那个位置，然后p~i排序
	// 让i归位置
	bit.clear();
	for(rint lb=1,rb=1,res=0;rb<=n;rb++){
		res+=(rb-lb)-bit.query(a[rb]);bit.add(a[rb],1);
		while(res>rst&&lb<rb)res-=bit.query(a[lb]-1),bit.add(a[lb],-1),lb++;  // 保证可以删除rb
		if(res==rst){
			printf("1\n%lld %lld\n",lb,rb);
			return;
		}
	}
	// 两次怎么做
	for(int i=n;i>=1;i--){
		if(rev[i]<=K){K-=rev[i];continue;}  // 正着选
		else{
			int more = rev[i]-K;
			printf("2\n%lld %lld\n",1,i-1);  // 你考虑我对[l,r]这一段排序，是不会影响[1,L-1]ans[R+1,n]答案的
			sort(a+1,a+i);
			for(int j=i-1;j>=1;j--){
				if(a[j]>a[i])more--;
				if(!more){
					printf("%lld %lld\n",j,i);
					return;
				}
			}
			exit(51);
		}
	}
	return;
}
signed main(){
	fastio;
	freopen("reverse.in","r",stdin);
	freopen("reverse.out","w",stdout);
	
	cin>>_>>n>>K;for(rint i=1;i<=n;i++)cin>>a[i],b[i]=a[i];
	sort(b+1,b+n+1),m=unique(b+1,b+n+1)-b-1;
	for(rint i=1;i<=n;i++)cvt[b[i]]=i;
	for(rint i=1;i<=n;i++)a[i]=cvt[a[i]];
	tot=getrev(a);
	bf();
	return 0;
}
