import java.util.Scanner;

public class Fibonacci {
	
	public static int fibbI(int n) {
		
		if(n==0 || n==1) {
			return n;
		}
		int[] dp = new int[n+1];
		dp[0]=0;
		dp[1]=1;
		//n>2
		for(int i=2; i<=n; i++) {
			dp[i]=dp[i-1]+dp[i-2];
		}
		
		return dp[n];
	}
	
	public static int fibb(int n,int dp[]) {
		
		if(n==0 || n==1) {
			return n;
		}
		int ans1,ans2;
		
		if(dp[n-1]==-1) {
			ans1=fibb(n-1,dp);
			dp[n-1]=ans1;
		}
		else {
			ans1=dp[n-1];
		}
		
		if(dp[n-2]==-1) {
			ans2=fibb(n-2,dp);
			dp[n-2]=ans2;
		}
		else {
			ans2=dp[n-2];
		}
		
		
		int myAns= ans1+ans2;
		
		return myAns;
				
	}

	public static void main(String[] args) {
		
		
		Scanner s= new Scanner(System.in);
		int n=s.nextInt();
		int[] dp=new int[n+1];
		for(int i=0; i<dp.length; i++) {
			dp[i]=-1;
		}
		int ans= fibb(n,dp);
		dp[n]=ans;
		System.out.println(ans);

	}

}
