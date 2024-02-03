
import java.util.Scanner;
import java.util.InputMismatchException;


/**
 * Invalid Flight Exception class
 * 
 * @author Conner Yin
 */
@SuppressWarnings("serial")
class InvalidFlight extends Exception { // For exercise 5

	/**
	 * Returns "Invalid Flight" string if exception is thrown
	 * 
	 * @param flight
	 * @throws Exception 
	 */
	public InvalidFlight() {}

	public String toString() {
		return "Invalid Flight";
	}
}



/**
 * MissedFlight Exception class
 * 
 * @author Conner Yin
 */
@SuppressWarnings("serial")
class MissedFlight extends Exception { // For exercise 5
	private String flight;

	/**
	 * Returns flight data unless first 2 chars are non-alphabetic, then throws invalid flighMe
	 * 
	 * @param flight
	 * @throws Exception 
	 */
	public MissedFlight(String flight) throws Exception {
		// Check if the parameter flight starts with 2 or 3 letters
		// if not, throw an exception new Exception()
		// Write a statement to initialize the data member flight.
		
		if (Character.isAlphabetic(flight.charAt(0)) && Character.isAlphabetic(flight.charAt(1)))
			this.flight = flight;
		else
			throw new InvalidFlight();
		
	}

	public String toString() {
		return "Missed flight: " + flight;
	}
}

/**
 * Canceled Flight Exception class
 * 
 * @author	Conner Yin
 */
@SuppressWarnings("serial")
class CanceledFlight extends Exception { // For exercise 5
	private String flight;

	/**
	 * Returns flight data unless first 2 chars are non-alphabetic, then throws invalid flight
	 * 
	 * @param flight
	 * @throws Exception 
	 */
	public CanceledFlight(String flight) throws Exception {
		
		if (Character.isAlphabetic(flight.charAt(0)) && Character.isAlphabetic(flight.charAt(1)))
			this.flight = flight;
		else
			throw new InvalidFlight();
	}

	public String toString() {
		return "Canceled flight: " + flight;
	}
}

/**
 * LAB 4 EXERCISES: experimenting with different exceptions (ArithmeticException, InputMismatchException, Custom exceptions)
 * 
 * @author Conner Yin
 */
public class Lab4 {
	/**
	 *  EXERCISE 1: Divides by 0 but uses a try catch block to handle ArithmeticException
	 */
	public static void exer1() {
		int denominator, numerator;
		numerator = 4;
		denominator = 0;
		
		try {
			System.out.println("Result: " + numerator / denominator);
		} catch(ArithmeticException e){
			System.out.println("Threw ArithmeticException");
		}
		
		System.out.println("exer1 - end.");
	}

	/**
	 *  EXERCISE 3: Divides by 0 without having a way to handle ArithmeticException
	 *  Use try-catch block in main method to handle exception
	 */
	public static void exer1_2() {
		int denominator, numerator;
		numerator = 4;
		denominator = 0;
		
		System.out.println("Result: " + numerator / denominator);
		System.out.println("exer3 - end.");	
	}

	/**
	 * EXERCISE 2: Finds square of user input integer, catch InputMismatchException
	 */
	public static void exer2() {
		int num = 0;
		System.out.print("Enter an integer: ");
		Scanner scanner = new Scanner(System.in);
		
		try {
			num = scanner.nextInt();
			System.out.println("The square of " + num + " is " + num * num);
			
		} catch(InputMismatchException e){
			System.out.println("Must enter integer");
		}
		System.out.println("exer2 - end.");
		scanner.close();
	}

	/**
	 * EXERCISE 4: Finds square of user input integer, catch InputMismatchException
	 * Continue to ask user for more input until they input an integer
	 */
	public static void exer2_2() {
		int num = 0;
		Scanner scanner = new Scanner(System.in);
		
		boolean validInput = false;
		while(!validInput){
			
			try {
				System.out.print("Enter an integer: ");
				num = scanner.nextInt();
				System.out.println("The square of " + num + " is " + num * num);
				validInput = true;
				
			} catch(InputMismatchException e){
				System.out.println("Must enter integer");
				scanner.nextLine();
			}
		}
		
		System.out.println("exer4 - end.");
		scanner.close();
	}

	/**
	 * EXERCISE 5: Throws missed flight, cancelled flight, or arriving as planned depending on status
	 * 
	 * @param status
	 * @param flight
	 * @throws Exception 
	 */
	public static void exer5(int status, String flight) throws Exception {
		try {
			switch (status) {
			case 1:
				throw new MissedFlight(flight);
			case 2:
				throw new CanceledFlight(flight);
			default:
				System.out.println("Arriving as planned");
			}
		} catch (MissedFlight e) {
			System.out.println(e);
		} catch (CanceledFlight e) {
			System.out.println(e);
		} 
		  catch (InvalidFlight e){
			  System.out.println(e);
		  }
		  finally {
			System.out.println("Appointment moved to 11th March");
		}
		System.out.println("exer5 - done\n");
	}

	/**
	 * Runs Exercises 1-5
	 * 
	 * @param args
	 * @throws Exception 
	 */
	public static void main(String[] args) throws Exception {
		
		Lab4.exer1();			// Exercise 1
		Lab4.exer2();			// Exercise 2
		
		// Exercise 3
		try {
			Lab4.exer1_2();
		} catch(ArithmeticException e){
			System.out.println("Threw ArithmeticException");
			System.out.println("exer3 - end.");
		}
		
		Lab4.exer2_2();			// Exercise 4
		Lab4.exer5(3,"AA345");	// Exercise 5
	}
}