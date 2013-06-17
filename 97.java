import java.math.BigInteger;

public class Main {
	public static void main(String[] args) {
		BigInteger m = BigInteger.valueOf(10).pow(10);
		
		BigInteger prime = BigInteger.valueOf(2)
				.modPow(BigInteger.valueOf(7830457), m)
				.multiply(BigInteger.valueOf(28433))
				.add(BigInteger.ONE)
				.mod(m);
		
		System.out.println(prime);
	}
}
