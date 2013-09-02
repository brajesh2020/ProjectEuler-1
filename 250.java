import java.math.BigInteger;

public class Main {
	public static void main(String[] args) {
		initRemainders();
		solve();
	}
	
	private static void initRemainders() {
		BigInteger mod = BigInteger.valueOf(250);
		for (int i = 1; i <= 250250; i++) {
			BigInteger n = BigInteger.valueOf(i);
			remainders[i] = n.modPow(n, mod).intValue();
		}		
	}
	
	private static void solve() {
		BigInteger[] ways = new BigInteger[250];
		for (int i = 0; i < 250; i++) {
			ways[i] = BigInteger.ZERO;
		}

		BigInteger m = BigInteger.valueOf(10).pow(16);
		ways[0] = BigInteger.ONE;
		for (int i = 1; i <= 250250; i++) {
			BigInteger[] nextWays = new BigInteger[250];
			for (int j = 0; j < 250; j++) {
				nextWays[(j+remainders[i]) % 250] = ways[j];
			}
			for (int j = 0; j < 250; j++) {
				ways[j] = ways[j].add(nextWays[j]).mod(m);
			}
		}
		// Ignore empty set.
		System.out.println(ways[0].add(BigInteger.ONE.negate()));
	}
	
	private static int[] remainders = new int[250251];
}
