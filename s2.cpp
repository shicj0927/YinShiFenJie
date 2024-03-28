#include<bits/stdc++.h>
using namespace std;
const int N=1000001;
//质数(素数)打表
const int su[75]={543892411,567498259,643448581,772660877,802279559,823153213,847485637,907170331,919507003,923425961,929812711,935151689,938910911,962946403,970870897,977946113,985116131,989743967,991308817,994793521,995403061,997310857,998623607,999049111,999860857,1000885111,1002002609,1002270383,1002326077,1002351107,1002642457,1002681557,1003013519,1004475841,1005879367,1006478441,1007120461,1007468677,1007576071,1008054149,1008640013,1008894637,1009316083,1009528721,1009862393,1010510329,1010915173,1011460739,1012072651,1012612079,1012668131,1012825181,1014091867,1014515053,1014904973,1015114333,1015944323,1016003431,1016121461,1017088367,1017307463,1017423811,1017620873,1018394743,1018932493,1019199101,1019208581,1019319187,1019376101,1019831203};
int n,m,cnt,tot1,tot2,b[70][85],p[N],q[N];
char s1[N],s2[N];
struct nod{
    int fz,fm,cs;
}ans[85];//分数,名字写的很明白了
//fz分子fm分母cs次数
bool cmp(const nod &u,const nod &v){
	return (long long)u.fz*v.fm>(long long)u.fm*v.fz;
}//分数排序交叉相乘 
struct gjd{//高精度
	int len,sgn,num[40];
	void tim(int ws,int fu){//压位乘
		int i,j; sgn=fu;
		for (i=ws; i>0; i-=9){
			len++;
			for (j=max(1,i-8); j<=i; j++) num[len]=num[len]*10+s2[j]-'0';
		}
	}
	int getmod(int x){//压位模
		int i,t=0;
		for (i=len; i; i--)
			t=((long long)t*1000000000+num[i])%x;
		return t;
	}
}a[85];
int ksm(int x,int y,int mod){
	int t=1; 
    for (; y; y>>=1,x=(long long)x*x%mod) if (y&1) t=(long long)t*x%mod;
	return t;
}
int gcd(int x,int y){return (y)?gcd(y,x%y):x;}//最大公约数 
bool pd(int x,int y){
	int i,j,t,mod,tmp;
	for (i=0; i<70; i++){
		mod=su[i]; t=(x+mod)%mod;
		t=(long long)t*ksm(y,mod-2,mod)%mod;
		for (j=n,tmp=0; j>=0; j--) tmp=((long long)tmp*t+b[i][j])%mod;
		if (tmp) return 0;
	}
	return 1;
}
void ys(int x,int y){
	int i,j,t,mod;
	for (i=0; i<70; i++){
		mod=su[i];
        t=(x+mod)%mod;
		t=(long long)t*ksm(y,mod-2,mod)%mod;
		for (j=n; j>=0; j--) b[i][j]=((long long)b[i][j+1]*t+b[i][j])%mod;
	}
}
int main(){
    ios_base::sync_with_stdio(false);
	scanf("%s",s1+1);//从1开始 
	int i=1,len=strlen(s1+1);//strlen一定要加个一,否则会RE 
	while (i<=len){
		int ws=0,fu=1,sh=0;
		if (s1[i]=='-') fu=-1;//负数 
		if (s1[i]=='+' || s1[i]=='-') i++;//符号 
		if (s1[i]=='x'){//'x' 
			s2[ws=1]='1'; i++;
			if (s1[i]=='^'){//次方 
				for (i++; s1[i]>='0' && s1[i]<='9'; i++)
					sh=sh*10+s1[i]-'0';
				a[sh].tim(ws,fu);
				if (!n) n=sh;
			} else a[1].tim(ws,fu);
		} else{//系数 
			for (; s1[i]>='0' && s1[i]<='9'; i++) s2[++ws]=s1[i];
			if (!s1[i]) a[0].tim(ws,fu); else{
				i++;
				if (s1[i]=='^'){
					for (i++; s1[i]>='0' && s1[i]<='9'; i++) sh=sh*10+s1[i]-'0';
					a[sh].tim(ws,fu);
					if (!n) n=sh;
				}
                else a[1].tim(ws,fu);
			}
		}
	}
	if (a[n].sgn<0) putchar('-');//负数 
	if (a[n].len>1 || a[n].num[1]>1){
		printf("%d",a[n].num[a[n].len]);
		for (i=a[n].len-1; i; i--) printf("%09d",a[n].num[i]);
	}
    //---分割线 
	int j,k;
	i=0;//初始化 
    while (!a[i].len) i++;
	if (i>0) ans[++cnt]=(nod){0,1,i};
	for (j=i; j<=n; j++) a[j-i]=a[j];
	n-=i;
	for (i=0; i<70; i++) for (j=0; j<=n; j++) b[i][j]=(a[j].getmod(su[i])*a[j].sgn+su[i])%su[i];
	for (i=1; i<=1000000; i++){
		if (!a[0].getmod(i)) p[++tot1]=i;//首项因数 
		if (!a[n].getmod(i)) q[++tot2]=i;//末项因数 
	}
	for (i=1; i<=tot1; i++) for (j=1; j<=tot2; j++) if (gcd(p[i],q[j])==1){//互质,减少次数 
		for (k=0; pd(p[i],q[j]); k++) ys(p[i],q[j]);
		if (k) ans[++cnt]=(nod){p[i],q[j],k};//分数 
		for (k=0; pd(-p[i],q[j]); k++) ys(-p[i],q[j]);
		if (k) ans[++cnt]=(nod){-p[i],q[j],k};//分数 
	}
	//---分割线 
	sort(ans+1,ans+cnt+1,cmp);
	for (i=1; i<=cnt; i++){
		if (!ans[i].fz) putchar('x'); 
        else if (ans[i].fm==1)
			if (ans[i].fz<0) printf("(x+%d)",-ans[i].fz);
			else printf("(x%d)",-ans[i].fz);
		else 
            if (ans[i].fz<0) printf("(x+%d/%d)",-ans[i].fz,ans[i].fm);
			else printf("(x%d/%d)",-ans[i].fz,ans[i].fm);
		if (ans[i].cs>1) printf("^%d",ans[i].cs);
	}
	printf("\n");
	system("pause");
	return 0; 
}