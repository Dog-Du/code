#include <stdio.h>
#include <stdlib.h>
#define max(a,b) (a>b?a:b)
int main(int argc, char *argv[])
{
  typedef long long int LL;
  int n=0;
  scanf("%d",&n);
  LL dp[100005];
  LL sum=0;
  for(int i=1;i<=n;i++){
    LL k;
    scanf("%lld",&k);

    if(i%2==0){
      dp[i]=max(k+dp[i-2],sum);
    }
    else{
      dp[i]=max(k+dp[i-2],dp[i-1]);
      sum+=k;
    }
  }

  printf("%lld",dp[n]);
  return 0;
}
