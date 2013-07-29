import java.math.BigInteger;
import java.util.Dictionary;
import java.util.Hashtable;

public class Main {
	public static void main(String[] args) {
		initWaysCount();
		BigInteger n = BigInteger.valueOf(10).pow(25);
		System.out.println(getWays(n));
	}
	
	private static void initWaysCount() {
		waysCount.put(BigInteger.ZERO, BigInteger.ONE);
		waysCount.put(BigInteger.ONE, BigInteger.ONE);
	}
	
	private static BigInteger getWays(BigInteger n) {
		if (waysCount.get(n) != null) {
			return (BigInteger) waysCount.get(n);
		}
		if (n.mod(BigInteger.valueOf(2)).compareTo(BigInteger.ZERO) == 0) {
			n = n.divide(BigInteger.valueOf(2));
			BigInteger a = n.add(BigInteger.valueOf(-1));
			BigInteger aWays = getWays(a);
			waysCount.put(a, aWays);
			BigInteger nWays = getWays(n);
			waysCount.put(n, nWays);
			return aWays.add(nWays);
		} else {
			BigInteger a = n.add(BigInteger.valueOf(-1))
					.divide(BigInteger.valueOf(2));
			BigInteger ways = getWays(a);
			waysCount.put(a, ways);
			return ways;
		}
	}

	private static Dictionary<BigInteger, BigInteger> waysCount = 
			new Hashtable<BigInteger, BigInteger>();
}
