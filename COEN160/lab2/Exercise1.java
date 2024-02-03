// Exercise1.java
class CheckThings {
	public static boolean isItALeapYear(int year){

		// A leap year is a year that is divisible by 4 and not by hundred  OR
		// it is divisible by 400.
		return year % 400 == 0 || (year % 4 == 0 && year % 100 != 0);

	}
}

public class Exercise1 {
    public static void tester() {
        
        // Insert code to check, by calling the method you have written,
        // if the following years are leap years or not.
        // 1716,1989, 1992, 2000, 2010, 2012. 
        // Test your code with other years of your choice.
    	
    	int[] years = new int[1716, 1989, 1992, 2000, 2010, 2012];
    	
    	for(int i=0; i<=years.length(); i++)
    		System.out.println(years[i] + ": " + isItALeapYear(years[i]));
        
       
    }
	
}
