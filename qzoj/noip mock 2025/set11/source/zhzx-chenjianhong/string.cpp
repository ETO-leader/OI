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
constexpr int N=1e5+10;int __test_num=1,__task_id;using namespace std;void __init();

string s,t;int n,m;

bool __med;void __solve(int __test_id){
	cin>>s>>t;
	n=s.length(),m=t.length();s=" "+s,t=" "+t;
	if(__task_id==6){
		if(n>m||(m-n)%2!=0)cout<<"NO\n";
		else{
			for(int i=1;i<=m;){
				if(t[i]=='a')++i;
				else if(i==m){
					cout<<"NO\n";
					return;
				}
				else if(t[i]!=t[i+1]){
					cout<<"NO\n";
					return;
				}
				else i+=2;
			}
			int sum=0,cnta=0;
			for(int i=1;i<=m;++i){
				if(t[i]=='a')++cnta;
				else sum+=cnta%2,cnta=0;
			}
			sum+=cnta%2;
			if(sum>n)cout<<"NO\n";
			else cout<<"YES\n";
		}
	}
}
signed main(){
	__init();
	forUp(i,1,__test_num)__solve(i);
	return 0;
}
void __init(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	const string __file_name="string";freopen((__file_name+".in").c_str(),"r",stdin);freopen((__file_name+".out").c_str(),"w",stdout);
	//cerr<<((&__mst)-(&__med))/1024.0/1024.0<<"MB"<<endl;
	//scanf("%d",&__test_num);
	//cin>>__test_num;
	cin>>__test_num>>__task_id;
}
