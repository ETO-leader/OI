#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
vector<lint> M_Days{0,31,28,31,30,31,30,31,31,30,31,30,31};
const int LastJu=1582;
const int LastJuM=10,LastJuD=4;
bool IsLeap(int x){
	if(x<0) return !((-x-1)%4);
	if(x<LastJu) return !(x%4);
	return (!(x%400))||((!(x%4))&&x%100);
}
struct Date{
	lint J,Y,M,D;
	Date(lint _Y=0,lint _M=0,lint _D=0,lint _J=0):Y(_Y),M(_M),D(_D),J(_J){}
	Date&operator++(){
		++J,++D;
		if(M==LastJuM&&D-1==LastJuD&&Y==LastJu){
			D=15;goto res;
		}
		if(D-(M==2&&IsLeap(Y))>M_Days[M]){
			D=1;
			if((++M)>12) M=1,Y+=(1+(Y==-1));
		}
		res:return *this;
	}
};
ostream&operator<<(ostream&os,Date D){
	return (os<<D.D<<' '<<D.M<<' '<<abs(D.Y)<<(D.Y<0?" BC":""));
}
const int max_date=2.6e6+7;
lint J16,J20;
vector<Date> DT(max_date);
Date solve(lint Dx){
	if(Dx<J16) return DT[Dx];
	int Y400=J20-J16;
	auto ret=DT[J16+((Dx-J16)%Y400)];
	ret.Y+=((Dx-J16)/Y400)*400;
	return ret;
}
void init(){
	DT[0]=Date(-4713,1,1);
	cir(i,1,max_date){
		DT[i]=DT[i-1];++DT[i];
		if(DT[i].Y==1600&&(!J16)) J16=DT[i].J;
		if(DT[i].Y==2000&&(!J20)) J20=DT[i].J;
	}
}
int main(){
	ios::sync_with_stdio(false),cin.tie(0);
	init();lint T,x;cin>>T;
	while(T--) cin>>x,cout<<solve(x)<<endl;
	return 0;
}