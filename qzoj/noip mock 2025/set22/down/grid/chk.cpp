#include"testlib.h"
#include<bits/stdc++.h>
using namespace std;
int n,m;
vector<pair<int,int> >itv[300005];
bool valid(int i1,int i2){
	vector<pair<int,int> >vec;
	for(auto x:itv[i1])vec.push_back(x);
	for(auto x:itv[i2])vec.push_back(x);
	stable_sort(vec.begin(),vec.end());
	int sz=vec.size();
	for(int j=1;j<sz;j++){
		if(vec[j].first<=vec[j-1].second){
			return 1;
		}
	}
	return 0;
}
int check(InStream &ins,TResult rst){
	int k=ins.readInt();
	quitif(k<0||k>n,rst,"k is not in range [0,n]");
	vector<int> a(k),b;
	for(int i=0;i<k;i++){
		a[i]=ins.readInt();
		quitif(a[i]<1||a[i]>n,rst,"a_%d(=%d) is not in range [1,n]",i,a[i]);
	}
	stable_sort(a.begin(),a.end());
	for(int i=1;i<k;i++){
		quitif(a[i]==a[i-1],rst,"Deleted same line %d twice",a[i]);
	}
	for(int i=1,j=0;i<=n;i++){
		if(j<k&&i==a[j]){
			++j;
		}
		else{
			b.push_back(i);
		}
	}
	assert((int)b.size()==n-k);
	for(int i=1;i<n-k;i++){
		quitif(!valid(b[i-1],b[i]),rst,
			"Adjacent line %d and line %d have no common black column",b[i-1],b[i]);
	}
	return k;
}
int main(int argc,char*argv[]){
	registerTestlibCmd(argc,argv);
	n=inf.readInt(1,300000,"inf.N");
	m=inf.readInt(1,300000,"inf.M");
	for(int i=0;i<m;i++){
		int p,l,r;
		p=inf.readInt(1,n,"inf.p_i");
		l=inf.readInt(1,1000000000,"inf.l_i");
		r=inf.readInt(l,1000000000,"inf.r_i");
		itv[p].push_back(make_pair(l,r));
	}
	for(int i=1;i<=n;i++){
		if(!itv[i].size()){
			continue;
		}
		stable_sort(itv[i].begin(),itv[i].end());
		int t=0,sz=itv[i].size();
		for(int j=1;j<sz;j++){
			if(itv[i][j].first<=itv[i][t].second){
				itv[i][t].second=max(itv[i][t].second,itv[i][j].second);
			}
			else{
				itv[i][++t]=itv[i][j];
			}
		}
		if(t+1<sz){
			itv[i].erase(itv[i].begin()+t+1,itv[i].end());
		}
	}
	int aans=check(ans,_fail);
	int oans=check(ouf,_wa);
	quitif(oans>aans,_wa,"Out deleted too many lines");
	quitif(oans<aans,_fail,"Ans deleted too many lines");
	quitf(_ok,"ok");
	return 0;
}
