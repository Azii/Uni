import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;

import java.util.ArrayList;
import java.util.Arrays;

import org.junit.Before;
import org.junit.Test;


public class ArrayCheckTest {
	// NOTTODO DIESE ZEILE BITTE NICHT VERAENDERN!!
	// TODO Fuehrt eure Tests auf diesem ArrayCheck-Objekt aus!
	// Ansonsten kann eure Abgabe moeglicherweise nicht
	// gewertet werden.
	public ArrayCheck ArrayCheck = new ArrayCheck();
	public ArrayList<Integer> al = new ArrayList<Integer>();
	

	@Test(timeout = 1000)
	public void testAllDivisibleBy() {
		// TODO Schreibt verschiedene Testfaelle, die unterschiedliche Arrays
		// anlegen und an testAllDivisibleBy uebergeben.
		// Testet auch randfaelle wie z.B. leere arrays.
		al.clear();
		assertFalse(ArrayCheck.allDivisibleBy(al, 2));
		al.add(2);
		assertFalse(ArrayCheck.allDivisibleBy(al, 0));
		assertTrue(ArrayCheck.allDivisibleBy(al, 2));
		assertFalse(ArrayCheck.allDivisibleBy(al, 3));
		al.add(3);
		for (int i = 2; i < 20; i++)
		{
			assertFalse(ArrayCheck.allDivisibleBy(al, i));
		}
		assertTrue(ArrayCheck.allDivisibleBy(al, 1));
	}

	@Test(timeout = 1000)
	public void testIsFibonacci() {
		// TODO Schreibt verschiedene Testfaelle, fuer testIsFibonacci.
		al.clear();
		assertFalse(ArrayCheck.isFibonacci(al));
		al.add(0);
		assertFalse(ArrayCheck.isFibonacci(al));
		al.add(1);
		assertFalse(ArrayCheck.isFibonacci(al));
		al.add(1);
		assertTrue(ArrayCheck.isFibonacci(al));
		al.add(2);
		assertTrue(ArrayCheck.isFibonacci(al));
		al.add(4);
		assertFalse(ArrayCheck.isFibonacci(al));
		al.clear();
		al.add(2);
		assertFalse(ArrayCheck.isFibonacci(al));
		int [] a = {2,3,5,8,13,21};
		al.clear();
		for (int i = 0; i < a.length; i++)
		{
			al.add(a[i]);
		}
		assertTrue(ArrayCheck.isFibonacci(al));
		
	}


}

