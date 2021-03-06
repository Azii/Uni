/**
 * 
 * @author Algorithm and Datastructures Team SS2016
 * @version 1.0  
 * 
 */
import java.lang.RuntimeException;
public class MyHashMap {
	
	/**
	 * Use this array to store the values
	 * DO NOT MODIFY OR REMOVE THIS Attribute. Our tests rely on it.
	 */
	Student[] array;
	
	/**
	 * Tries inserting a Student into the hash map.
	 * Throws RunTimeException, if the student is already in the table or the table is full.
	 */
	public void add(Student s){
		boolean added = false;
		for (int i = hashFunction(s); i < array.length; i++)
		{
			if (s.equals(array[i]))
				break;
			if (array[i] == null)
			{
				array[i] = s;
				added = true;
				break;
			}
		}
		
		if (!added)
		{
			throw new RuntimeException();
		}
	}
	
	/**
	 * Try removing a Student from the hash table.
	 * You should use the same implementation for remove discussed in the tutorial.
	 * You should NOT use the lazy deletion strategy (adding a special flag key indicating a deleted key)
	 * See https://en.wikipedia.org/wiki/Linear_probing#Deletion for more details about the algorithm!
	 * Throw RunTimeException if the hash table contained the Student
	 */
	public void remove(Student s){
		int hashVal = hashFunction(s);
		boolean containedStudent = contains(s);
		if (containedStudent)
		{
			array[hashVal] = null;
			for (int i = hashVal + 1; i < array.length; i++)
			{
				if (array[i] == null)
					break;
				if (hashFunction(array[i]) <= hashVal)
				{
					array[hashVal] = array[i];
					array[i] = null;
					break;
				}
			}
		}else
			throw new RuntimeException();
	}
	
	
	/**
	 * Returns true, if the hash table contains the given Student
	 */
	public boolean contains(Student s){
		
		for (int i = 0; i < array.length; i++)
		{
			if (s.equals(array[i]))
				return true;
		}
		return false;
	}
	
	/**
	 * @param h Hashvalue to search for
	 * @return Number of Student in the hash table that have the hashvalue h
	 */
	public int getNumberStudentsWithHashvalue(int h){
		int n = 0;
		System.out.println(h + " " + n);
		for (int i = 0; i < array.length; i++)
		{
			if (array[i] != null)
			{
				System.out.println("hash value: " + hashFunction(array[i]));
				if (h == hashFunction(array[i]))
					n++;
			}
		}
		return n;
	}
	
	/**
	 * Doubles the size of the hash table. Recomputes the position of all elements using the
	 * new function.
	 */
	public void resize(){
		Student [] arr = array;
		setArray(new Student[array.length * 2]);
		System.out.println(arr.length + ", " + array.length);
		for (int i = 0; i < arr.length; i++)
		{
			if (arr[i] != null)
				add(arr[i]);
		}
		System.out.println("new array length: " + array.length);
	}

	/**
	 * This method return the array in which the strings are stored.
	 * DO NOT MODIFY OR REMOVE THIS METHOD. Our tests rely on it.
	 */
	public Student[] getArray(){
		return array;
	}
	
	/**
	 * DO NOT MODIFY OR REMOVE THIS METHOD. Our tests rely on it.
	 */
	public void setArray(Student[] array){
		this.array = array;
	}

	/**
	 * Runs the hash function for Student s (dependent on the size of the hash table)
	 * DO NOT MODIFY OR REMOVE THIS METHOD. Our tests rely on it.
	 * @param s Student
	 * @return the hash value for a student. (The position where it would be saved given no collisions)
	 */
	public int hashFunction(Student s){
		int hashvalue = Math.abs(s.hashCode()) % array.length;
		return hashvalue;
	}
	
	/**
	 * Constructor to initialize the hash with a given capacity
	 * DO NOT MODIFY OR REMOVE THIS METHOD. Our tests rely on it.
	 */
	public MyHashMap(int capacity){
		array = new Student[capacity];	
	}

}

