import java.util.Scanner;
public class ScannerDemo{

	public static void main(String[] args) {

	    // Declarations

	    Scanner in = new Scanner(System.in);

	    int anInteger;

	    double aDoubleNumber;

	       // Prompts

	    System.out.println("Enter an integer");
	    anInteger = in.nextInt();
	 
	    
	    System.out.println("Enter a double");
	    aDoubleNumber = in.nextDouble();
	    // Output the user input
	       
	    System.out.println("Here is what you entered: ");
	    System.out.println(anInteger);
	    System.out.println(aDoubleNumber);
	   

	  }	  

	}