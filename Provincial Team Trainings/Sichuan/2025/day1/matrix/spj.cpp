#include<bits/stdc++.h>
#include "testlib.h"
#define ll long long
using namespace std;
namespace Tybbs{
	int a[1005][1005],b[1005][1005];
	void main(){
		ll expt=ans.readLong(),res=ouf.readLong();
		if(expt!=res){
			quitf(_wa,"wrong answer");
		}
		int n=inf.readInt(),m=inf.readInt();
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				a[i][j]=inf.readInt();
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				b[i][j]=ouf.readInt();
				if(b[i][j]<0 || b[i][j]>1){
					quitf(_wa,"invalid construction");
				}
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				if(!b[i][j]) continue;
				if(b[i-1][j] || b[i][j-1] || b[i+1][j] || b[i][j+1]){
					quitf(_wa,"invalid construction");
				}
				if((i+j)%2==1){
					if(b[i-1][j-1] || b[i+1][j+1]){
						quitf(_wa,"invalid construction");
					}
				}
				else{
					if(b[i-1][j+1] || b[i+1][j-1]){
						quitf(_wa,"invalid construction");
					}
				}
			}
		}
		ll sum=0;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				sum+=a[i][j]*b[i][j];
			}
		}
		if(sum!=expt){
			quitf(_wa,"construction doesn't match answer");
		}
		quitf(_ok,"Accepted\n");		
	}


}

int main(int argc,char *argv[]){registerTestlibCmd(argc,argv);
/*
	inf 输入文件流
	ouf 选手输出流
	ans 标准答案流
*/
	Tybbs::main();
}
