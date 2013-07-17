import java.math.BigInteger;

public class Main {
	public static void main(String[] args) {
		initBaseCount();
		System.out.println(count(BigInteger.valueOf(1000000000-1)));
	}
	
	private static BigInteger count(BigInteger n) {
		BigInteger sum = BigInteger.ZERO;
		String rep = n.toString(7);
		BigInteger leftmost = BigInteger.ONE;
		for (int i = 0; i < rep.length(); i++) {
			int digit = rep.charAt(i) - '0';
			if (digit == 0) {
				continue;
			}
			BigInteger term = BigInteger.valueOf(28)
					.pow(rep.length() - 1 - i)
					.multiply(baseCount[digit-1]).multiply(leftmost);
			leftmost = leftmost.multiply(BigInteger.valueOf(digit + 1));
			sum = sum.add(term);
		}
		sum = sum.add(leftmost);
		return sum;
	}
	
	private static void initBaseCount() {
		baseCount[0] = BigInteger.ONE;
		for (int i = 1; i < 7; i++) {
			baseCount[i] = baseCount[i-1].add(BigInteger.valueOf(i+1));
		}
	}
	
	private static BigInteger[] baseCount = new BigInteger[7];
}
