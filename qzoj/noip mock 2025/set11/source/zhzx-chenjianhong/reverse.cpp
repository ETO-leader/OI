#include<bits/stdc++.h>
#define forUp(i,a,b) for(int i=(a);i<=(b);++i)
#define forUP(i,a,b) for(int i=(a);i<(b);++i)
#define forDown(i,a,b) for(int i=(a);i>=(b);--i)
#define forG(u,v) for(int __i=head[u],v=to[__i];__i;__i=nxt[__i],v=to[__i])
#define forWG(u,v,c) for(int __i=head[u],v=to[__i],c=w[__i];__i;__i=nxt[__i],v=to[__i],c=w[__i])
#define pb push_back
bool __mst;using ll=long long;using ull=unsigned long long;using uint=unsigned int;using db=double;using ld=long db;using pii=std::pair<int,int>;using pdi=std::pair<db,int>;using vl=__int128;using uvl=unsigned __int128;
constexpr int INF=0x3f3f3f3f,MINF=0xcfcfcfcf;constexpr long long INFLL=0x3f3f3f3f3f3f3f3f,MINFLL=0xcfcfcfcfcfcfcfcf;constexpr double INFDB=1e50,eps=1e-4;
template<class _Tp>void chkMax(_Tp &x,const _Tp &y){x<y?x=y:0;}template<class _Tp>void chkMin(_Tp &x,const _Tp &y){x>y?x=y:0;}
constexpr int N=1e6+10;int __test_num=1,__task_id;using namespace std;void __init();

int n,A[N];ll inv,todo;

int sum[N];vector<array<int,2>> ans;

bool __med;void __solve(int __test_id){
	cin>>__task_id>>n>>todo;forUp(i,1,n)cin>>A[i];
	forUp(i,1,n){
		for(int pos=A[i]-1;pos;pos-=pos&-pos)inv-=sum[pos];
		inv+=i-1;
		for(int pos=A[i];pos<=n;pos+=pos&-pos)++sum[pos];
	}
	todo=inv-todo;int cnt=0;
	while(todo){
		int ansl=-1,ansr=-1;ll now=0,delta=0;
		forUp(i,1,n)sum[i]=0;
		for(int l=1,r=1;r<=n;++r){
			for(int pos=A[r];pos;pos-=pos&-pos)now-=sum[pos];
			now+=r-l;
			for(int pos=A[r];pos<=n;pos+=pos&-pos)++sum[pos];
			while(now>todo){
				for(int pos=A[l];pos;pos-=pos&-pos)now-=sum[pos];++now;
				for(int pos=A[l];pos<=n;pos+=pos&-pos)--sum[pos];
				++l;
			}
			if(now>delta)delta=now,ansl=l,ansr=r;
		}
		++cnt,todo-=delta;ans.pb({ansl,ansr});
		sort(A+ansl+1,A+ansr+1);
	}
	cout<<cnt<<'\n';
	for(const array<int,2> &arr:ans)cout<<arr[0]<<" "<<arr[1]<<'\n';
}
signed main(){
	__init();
	forUp(i,1,__test_num)__solve(i);
	return 0;
}
void __init(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	const string __file_name="reverse";freopen((__file_name+".in").c_str(),"r",stdin);freopen((__file_name+".out").c_str(),"w",stdout);
	//cerr<<((&__mst)-(&__med))/1024.0/1024.0<<"MB"<<endl;
	//scanf("%d",&__test_num);
	//cin>>__test_num;
}
