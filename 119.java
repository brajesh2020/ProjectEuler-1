import java.math.BigInteger;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Main {
	public static void main(String[] args) {
		List<BigInteger> digitPowerList = new ArrayList<BigInteger>();
		BigInteger upperBound = BigInteger.valueOf(10).pow(16);
		for (long i = 2; i < 10000; i++) {
			BigInteger a = BigInteger.valueOf(i);
			while (a.compareTo(upperBound) < 0) {
				a = a.multiply(BigInteger.valueOf(i));
				if (getDigitSum(a.toString()) == i) {
					digitPowerList.add(a);
				}
			}
		}		
		Collections.sort(digitPowerList);
		System.out.println(digitPowerList.get(29).toString());
	}	
	
	private static long getDigitSum(String n) {
		int sum = 0;
		int length = n.length();
		for (int i = 0; i < length; i++) {
			sum += n.charAt(i) - '0';
		}
		return sum;
	}
}
