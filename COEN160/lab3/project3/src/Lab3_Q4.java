public class Lab3_Q4 {
	public static void q4() {
		// Example
		char[] fromArray = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm' };
		char[] toArray = new char[10];

		System.arraycopy(fromArray, 2, toArray, 0, 10);
		System.out.println("Array unchanged = " + new String(toArray)+"\n"); // Prints cdefghijkl

		// Exercise 1 ************************************************************************
		char[] arr = new char[5];
		arr[0] = 'A';
		arr[1] = 'B';
		arr[2] = 'C';
		arr[3] = 'D';
		System.out.println("Array unchanged = " + new String(arr)); // Prints: "Array unchanged = ABCD"

		// Write code to insert 'X' in the middle of array, using arraycopy().
		System.out.println("Array   changed = " + new String(arr)); // Should print: "Array   changed = ABXCD"

		// Exercise 2 ************************************************************************
		char[] courseName = { 'C', 'O', 'E', 'N', '2', '1', '6', '0' };
		System.out.println("Array unchanged = " + new String(courseName)); // Prints: "Array unchanged = COEN2160"

		// Write code to remove '2' from courseName, using arraycopy().
		System.out.println("Array   changed = " + new String(courseName)); // Should print: "Array unchanged = COEN160"
	}
}