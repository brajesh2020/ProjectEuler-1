import java.math.BigInteger;

public class Main {
	public static void main(String[] args) {
		initPrimeTable();
		
		int count = 0;
		for (int i = 0; i < 664579; i++) {
			for (int j = 0; j < 664579; j++) {
				if (i == j) {
					continue;
				}
				BigInteger n = BigInteger.valueOf(primes[i]).pow(2)
						.multiply(BigInteger.valueOf(primes[j]).pow(3));
				if (n.compareTo(new BigInteger("229161792008")) > 0) {
					break;
				}
				if (n.toString().contains("200") && isPrimeProof(n)) {
					count++;
					System.out.printf("%s => %d\n", n.toString(), count);
				}
			}
		}		
	}	

	private static void initPrimeTable() {
		boolean[] visited = new boolean[10000000];
		int currPos = 0;
		for (int i = 2; i < 10000000; i++) {
			if (!visited[i]) {
				primes[currPos] = i;
				currPos++;
				for (int j = i + i; j < 10000000; j += i) {
					visited[j] = true;
				}
			}
		}
	}
	
	private static boolean isPrimeProof(BigInteger n) {
		String rep = n.toString();
		for (int i = 0; i < rep.length(); i++) {
			for (int j = 0; j < 10; j++) {
				if (j == rep.charAt(i) - '0') {
					continue;
				}
				BigInteger replaced = new BigInteger(rep.substring(0, i) + j + rep.substring(i + 1));
				if (replaced.isProbablePrime(4)) {
					return false;
				}
			}
		}
		return true;
	} 
	
	private static long[] primes = new long[664579];	
}
