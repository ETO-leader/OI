#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define uint unsigned int
#define ull unsigned long long
#define lll __int128
#define db double
#define ld long double
#define fi first
#define se second
#define endl '\n'
#define ainline inline __attribute__((always_inline))
#define inf 0x3f3f3f3f
#define ninf 0xcfcfcfcf
#define infll 0x3f3f3f3f3f3f3f3f
#define ninfll 0xcfcfcfcfcfcfcfcf
#define start_mtest\
	int tcnt;\
	cin>>tcnt;\
	for(int tcase=1;tcase<=tcnt;tcase++)[&]\
	{
#define end_mtest\
	}();
constexpr int N=1000010;
int n;
ll m,sum;
int A[N];
vector<pair<int,int>>Opt;
struct bit
{
	int T[N];
	inline int lowbit(const int &x)
	{
		return x&-x;
	}
	void clear()
	{
		memset(T,0,sizeof(T));
	}
	void add(int x,int v)
	{
		for(int i=x;i<=n;i+=lowbit(i))T[i]+=v;
	}
	int sum(int x)
	{
		int res=0;
		for(int i=x;i;i-=lowbit(i))res+=T[i];
		return res;
	}
};
bit T;
ll calc(int l,int r)
{
	ll res=0;
	for(int i=l;i<=r;i++)
		for(int j=i+1;j<=r;j++)
			if(A[i]>A[j])
				res++;
	return res;
}
ll check(ll m)
{
	T.clear();
	ll tmp=0,max=0;
	int l=0,r=0;
	for(int i=1,j=0;i<=n&&j<=n;)
	{
//		cerr<<i<<' '<<j<<endl;
		if(tmp<m&&j<n)
		{
			if(tmp>max)max=tmp,l=i,r=j;
			j++;
			T.add(A[j],1);
			tmp+=(j-i)-T.sum(A[j]-1);
		}
		else if(tmp==m)return Opt.push_back({i,j}),sort(A+i,A+j+1),m;
		else if(tmp>m&&i<n)
		{
			T.add(A[i],-1);
			tmp-=T.sum(A[i]-1);
			i++;
		}
		else break;
	}
	Opt.push_back({l,r});
	sort(A+l,A+r+1);
	return max;
}
int main()
{
	freopen("reverse.in","r",stdin);
//	freopen("../../down/down/reverse/reverse3.in","r",stdin);
	freopen("reverse.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int testid;
	cin>>testid>>n>>m;
	for(int i=1;i<=n;i++)cin>>A[i];
	if(is_sorted(A+1,A+n+1))return cout<<0,0;
	for(int i=1;i<=n;i++)
	{
		T.add(A[i],1);
		sum+=i-1-T.sum(A[i]-1);
	}
	m=sum-m;
	while(m)m-=check(m);
	cout<<Opt.size()<<endl;
	for(pair<int,int>i:Opt)cout<<i.fi<<' '<<i.se<<endl;
	return 0;
}

