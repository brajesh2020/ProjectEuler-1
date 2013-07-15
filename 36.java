import java.math.BigInteger;

public class Main {
	public static void main(String[] args) {
		long sum = 0;
		for (long i = 1; i < 1000000; i++) {
			BigInteger n = BigInteger.valueOf(i);
			if (isPalindrome(n.toString(10)) && isPalindrome(n.toString(2))) {
				sum += i;
			}					
		}
		System.out.println(sum);
	}

	private static boolean isPalindrome(String word) {
		int length = word.length();
		for (int i = 0; i < length/2; i++) {
			if (word.charAt(i) != word.charAt(length-1-i)) {
				return false;
			}
		}
		return true;
	}
}
