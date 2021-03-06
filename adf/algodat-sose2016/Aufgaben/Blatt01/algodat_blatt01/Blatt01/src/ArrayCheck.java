import java.util.ArrayList;
import java.util.ListIterator;


/**
 * This class implements three methods. These test an array on a few
 * characteristics.
 *
 * @author AlgoDat-Tutoren
 *
 */
public class ArrayCheck {
	/**
	 * Tests all elements of the given array,
     * if they are divisible by the given divisor.
     *
     * @param arr
     *            array to be tested
     * @param divisor
     * 				number by which all elements of the given array should be divisible
     * @return true if all elements are divisible by divisor
     */
    public boolean allDivisibleBy(ArrayList<Integer> arr, int divisor) {
    	if (arr == null)
    		return false;
    	if (arr.isEmpty())
    		return false;
        if (divisor == 0)
        	return false;
    	
    	for (Integer i : arr)
    	{
    		if (!(i % divisor == 0))
    			return false;
    	}
    	
    	return true;
    }

    /**
     * Tests if the given array is a part of
     * the fibonacci sequence.
     *
     * @param arr
     *            array to be tested
     * @return true if the elements are part of
     *         the fibonacci sequence
     */
    public boolean isFibonacci(ArrayList<Integer> arr) {
        
    	if (arr == null)
    		return false;
    	if (arr.size() < 3)
    		return false;
    	
    	int fibonacciElement = 0;
    	
    	while(true)
    	{
    		if (nthFibonacci(fibonacciElement) == arr.get(0))
    			break;
    		if (nthFibonacci(fibonacciElement) > arr.get(0))
    			return false;
    		//System.out.println(nthFibonacci(currentFibonacciElement));
    		fibonacciElement++;
    	}
    	
    	for (Integer i : arr)
    	{
    		if (!(i == ArrayCheck.nthFibonacci(fibonacciElement)))
    			return false;
    		fibonacciElement++;
    	}
    	
        return true;
    }
    
    private static int nthFibonacci(int n)
    {	
    	if (n <= 1)
    		return n;
    	return nthFibonacci(n - 1) + nthFibonacci(n - 2);
    }

}

