import java.math.BigInteger;

public class Main {
	public static void main(String[] args) {
		BigInteger n = BigInteger.valueOf(1777);
		long exponent = 1855;
		BigInteger modulo = BigInteger.valueOf(10).pow(8);
		System.out.println(modTetration(n, exponent, modulo));
	}
	
	private static BigInteger modTetration(
			BigInteger n, long exponent, BigInteger modulo) {
		if (exponent == 1) {
			return n.mod(modulo);
		}
		BigInteger exponentModulo = getOrder(n, modulo);
		BigInteger curr = n;
		for (long i = 1; i < exponent - 1; i++) {
			curr = n.modPow(curr, exponentModulo);
		}
		return n.modPow(curr, modulo);
	}
	
	private static BigInteger getOrder(BigInteger n, BigInteger modulo) {
		BigInteger power = n;
		long order = 1;		
		while (power.compareTo(BigInteger.ONE) != 0) {
			power = power.multiply(n).mod(modulo);
			order++;
		}
		return BigInteger.valueOf(order);
	}
}
