import java.math.BigDecimal;
import java.math.RoundingMode;

public class Main {
	public static void main(String[] args) {
		System.out.println(getDelta(new BigDecimal("1.0023221086328761")));
		System.out.println(getDelta(new BigDecimal("1.0023221086328762")));
	}	
	
	private static BigDecimal getDelta(BigDecimal r) {
		System.out.print(r + " => ");
		BigDecimal d = BigDecimal.ONE.add(r.negate());
		BigDecimal first = BigDecimal.valueOf(900)
				.multiply(BigDecimal.ONE.add(r.pow(5000).negate())) 
				.divide(d, 2, RoundingMode.HALF_UP);
		BigDecimal second = BigDecimal.valueOf(3)
				.multiply(BigDecimal.ONE
					.add(BigDecimal.valueOf(5001)
							.multiply(r.pow(5000)).negate())
					.add(BigDecimal.valueOf(5000)
							.multiply(r.pow(5001))))
				.divide(d.pow(2), 2, RoundingMode.HALF_UP);
		
		return first.add(second.negate()).add(new BigDecimal("600000000000"));
	}
}
