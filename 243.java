import java.math.BigInteger;

public class Main {
	public static void main(String[] args) {
		initPrimeTable();
		
		BigInteger phi = BigInteger.ONE;
		BigInteger d = BigInteger.ONE;
		BigInteger a = BigInteger.valueOf(15499);
		BigInteger b = BigInteger.valueOf(94744);
		BigInteger minusOne = BigInteger.valueOf(-1);
		for (int i = 1; i < 9; i++) {
			phi = phi.multiply(BigInteger.valueOf(prime[i]-1));
			d = d.multiply(BigInteger.valueOf(prime[i]));
		}
		phi = phi.multiply(BigInteger.valueOf(4));
		d = d.multiply(BigInteger.valueOf(8));
		if (phi.multiply(b).compareTo(d.add(minusOne).multiply(a)) <= 0) {
			System.out.println("Found: " + phi.toString() + "/" + d.toString());
		}
	}	

	private static void initPrimeTable() {
		boolean[] visited = new boolean[30];
		int currPos = 0;
		for (int i = 2; i < 30; i++) {
			if (!visited[i]) {
				prime[currPos] = i;
				currPos++;
				for (int j = i + i; j < 30; j += i) {
					visited[j] = true;
				}
			}
		}
	}
	
	private static long[] prime = new long[10];	
}
