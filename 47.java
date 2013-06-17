public class Main {
	public static void main(String[] args) {
		final int kUpperBound = 1000001;
		int query[] = new int[kUpperBound];
		for (int i = 2; i < kUpperBound; i++) {
	        if (query[i] == 0) {
	            for (int j = i; j < kUpperBound; j += i) {
	                query[j]++;
	            }
	        }
	    }
		
		for (int i = 2; i < kUpperBound - 3; i++) {
			if (query[i] == 4 && query[i+1] == 4 && 
					query[i+2] == 4 && query[i+3] == 4) {
				System.out.println(i);
				break;
			}
		}
	}
}
