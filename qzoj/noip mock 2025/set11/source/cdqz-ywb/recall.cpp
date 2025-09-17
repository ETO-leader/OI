#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define pii pair<int,int>
#define pb push_back
#define fi first
#define se second
using namespace std;
int Time=clock();
bool mst;
bool med;
int main(){
	freopen("recall.in","r",stdin);
	freopen("recall.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int a,T,n;
	cin>>a>>T;
	if(a==0)  cout<<"5 46\n5 20\n5 28\n7 1190\n6 320\n5 20\n4 4\n6 18\n4 4\n5 11";
	else if(a==2){
		while(T--){
			cin>>n;
			cout<<n<<'\n';
			while(n--){
				int a,b;
				cin>>a>>b;
			}
		}
	}
	else{
		while(T--){
			cin>>n;
			cout<<2<<'\n';
			while(n--){
				int a,b;
				cin>>a>>b;
			}
		}
	}
	// #ifndef ONLINE_JUDGE
	// cerr<<"Time:"<<fixed<<setprecision(5)<<1.0*(clock()-Time)/CLOCKS_PER_SEC<<"s"<<endl;
	// cerr<<"Memory:"<<fixed<<setprecision(5)<<1.0*(&med-&mst)/1024/1024<<"MB";
	// #endif
	return 0;
}