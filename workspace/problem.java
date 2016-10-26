import java.util.*;
import java.math.*;

public class problem {

	public static final int MAXN = 100;

	public static void main(String args[]) throws Exception {
		


		BigInteger dp[][] = new BigInteger[MAXN+1][MAXN+1];
		for(int i = 0; i <= MAXN; i++)
			dp[i][1] = BigInteger.ONE;
		for(int i = 0; i <= MAXN; i++)
			for(int j = 2; j <= MAXN; j++)
				for(int k = 0; k <= MAXN; k++)
					if (i-k <= MAXN && i-k >= 0) {
						if (dp[i][j] == null)
							dp[i][j] = BigInteger.ZERO;
						dp[i][j] = dp[i][j].add(dp[i-k][j-1]);
					}

		Scanner scanner = new Scanner(System.in);
		int TC = scanner.nextInt();
		while(TC-- != 0) {
			int k = scanner.nextInt();
			BigInteger ans = BigInteger.ZERO;
			int used[] = new int[101];
			for(int i = 0; i < 5; i++) {
				int n = scanner.nextInt();
				if (n > 100) throw new Exception();
				if (used[n] == 0)
					ans = ans.add(dp[n][k]);
				used[n] = 1;
			}

			System.out.println(ans);
		}
	}

}
