import java.math.BigInteger;

public class Main {
	public static void main(String[] args) {
		long max = 1;
		for (int a = 1; a < 100; a++) {
			for (int b = 1; b < 100; b++) {
				String n = BigInteger.valueOf(a).pow(b).toString();
				long sum = getDigitSum(n);
				if (sum > max) {
					max = sum;
				}
			}
		}
		System.out.println(max);
	}
	
	private static long getDigitSum(String n) {
		long sum = 0;
		for (int i = 0; i < n.length(); i++) {
			sum += (n.charAt(i) - '0');
		}
		return sum;
	}
}
