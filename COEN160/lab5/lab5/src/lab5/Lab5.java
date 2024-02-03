/**
 * @(#)Lab5.java
 * 
 * Exercise 1: Initialize an array and print the first value
 * Exercise 2: User inputs city name, use Arrays.sort() to print them sorted
 * Exercise 3: Shallow/deep copies with reference and Arrays.copy()
 * Exercise 4: Use for each loop with the Book class to find a book
 * 	matching user-inputted title and printing its price
 * Exercise 4: Create a 2D array of pawns called Board, initialize the
 * 	pawns with values, and then print out the board using nested loop
 */

package lab5;
import java.util.*; 
import java.util.Arrays; 

public class Lab5 {
/////////////////////////Exercise - 5//////////////////////////////

	public static Pawn [][] prepareBoard(){
		// Create a 3 x 2 array, call it board,  of Pawn objects with colors
		// of your choice.
		Pawn[][] board = new Pawn[3][2];
		board[0][0] = new Pawn("black");
		board[0][1] = new Pawn("white");
		board[1][0] = new Pawn("white");
		board[1][1] = new Pawn("black");
		board[2][0] = new Pawn("black");
		board[2][1] = new Pawn("white");
		
		return board;
	}
	public static void showBoard(Pawn [][] board){
		
		// Display board as a table showing pawn colors as
		//values of each cell
		
		for(int i=0; i<board.length; i++){
			for(int j=0; j<board[i].length; j++){
				System.out.print(board[i][j].color+" ");
			}
			System.out.println();
		}
	}
 
    public static void twoDimArray(){
    	
    	//Java treats 2d arrays as an array of arrays
    
    	// create the single reference vals 
    	int [][] vals;

    	// create the array of references 
		// when you declare a 2D array:
		// you must always specify the first dimension 
		// vals = new int[][]; // ILLEGAL - NEEDS 1ST DIMENSION
		// No need to specify the second dimension 
		// vals = new int[5][]; // OK
		// vals = new int[5][4]; // OK
    	
		vals = new int[5][];

		// Now, to create the second level of arrays,
		for (int i=0; i < vals.length ; i++){

   			vals[i] = new int[4]; // create arrays of integers
    	}
    	// load values
    	// vals[i][j] represents a single value
    	// vals[i] - represents a single row (1d array) in vals
    
    	vals[0][0] = 20;
    
    }
    
    ///////////////////Exercise-4//////////////////////////////////
    
 	public static Book checkPrice(Book [] bookList, String title)
 	{
 		for (Book b: bookList){
    		if(b.getTitle().equals(title)) return b;
    	}
 		return null;
 	}
 		
 	
    public static void forEachLoop(){
    	
    	 //for-each loop: The basic for loop was extended in Java 5 to make iteration 
    	 //over arrays and other collections more convenient. 
		 //The for-each loop is used to access each successive value 
		 //in a collection of values.
    	 //
    	
    	double [] numList = {-10.0, 20.0, 30.0, 40.0, 50.0};
    	double sum = 0;
    	for (double d: numList)
    	{
    		if(d > 0) sum += d;
    	}
    	System.out.println(sum);
    	   	
    }
    
    
    
    ////////////////////Exercise 3//////////////////////////////////
    
    public static void copyArrays()
    {
    	int [] array1 = {1,2,3,4,5,6};
    	
    	// Copy array1 into array 2
    	int [] array2 = array1;
    	
    	// Now, change the value in array1[0]
    	array1[0] = 99;
    	
    	// What is the value in array2[0]?
    	System.out.println(array2[0]);
    	
    	int [] array3 = Arrays.copyOf(array1,array1.length);
    	array1[0] = 222;
    	
    	// What is the value in array3[0]?
    	System.out.println(array3[0]);
    	
    	/* 
    	 * a) In the line above, is the copy a shallow copy of references? 
    	 * In other words, if you change the values in array1, 
    	 * are the changes visible in array2? 
    	 * 
    	 * Yes, it's a shallow copy since chances to array1 affect array2
    	 * 
    	 * b) Using Arrays.copyOf(), can you copy only a part of the array? 
    	 * Hint: You may want to check the reference given above.
    	 * 
    	 * It can copy the entire array (will truncate or pad with 0s if
    	 * different orders)
    	 */
    }
    
    ///////////////////////Exercise 2///////////////////////////////
    
    public static void displayCitiesInSortedOrder(String[] cities){
    	
    	// Display the cities in a sorted order
	   	 // Use Arrays.sort(the arrayName)to sort the 
	   	 // array.
	   	 // Ref: http://docs.oracle.com/javase/6/docs/api/java/util/Arrays.html
	   	 // Display the contents of the array 
    	
    	Arrays.sort(cities);
    	for(int i=0; i<cities.length; i++)
    		System.out.println(cities[i]);
    }
    
    public static void favoriteCities() {
    	
    	// Prompts the user to enter the number of 
    	// his/her favorite cities. And prompts to
    	// enter the city names, which are read into
    	// an array.
    	int howMany;
        String [] cities;

        System.out.print("Enter the number of your favorite cities: ");
        Scanner in = new Scanner(System.in);
        
        // Now create the cities object to accomodate the city names
        howMany = in.nextInt();
        cities = new String[howMany];
        
    	// Read in the cities

        for (int i = 0; i < cities.length; i++){
                System.out.print("Enter the city name: ");
                cities[i] = in.next();
        }

       // Call displayCities() and display the 
       // names in cities []
        displayCitiesInSortedOrder(cities);
    		
        in.close();
    }
    
   //////////////////////////////Exer1///////////////////////////
   
    public static void exer1() {
    	int [] scores = new int[10];

    	// Load a value ...
    	scores[2] = 85;

    	// Display the value of 
   		 System.out.println(scores[2]);	
    }
    
    /*
     * a) Arrays in Java are similar to arrays in C, static in nature. TRUE
     * b) Once you create an array in Java, you cannot resize it.	   TRUE
     */
    
    
    ///////////////////////////////////////////////////////////////
    public static void main(String [] args) {
    	exer1();
    	favoriteCities();
    	 copyArrays();
    	forEachLoop();
    	
    	Book[] books = {
    		new Book("harry potter", 5.15),
    		new Book("hunger games", 15.99),
    		new Book("diary wimpy kid", 20.24),
    		new Book("game of thrones", 13.99)
    	};
    	
    	Book book = checkPrice(books, "diary wimpy kid");
    	if(book == null) System.out.println("book not found");
    	else System.out.println(book.getPrice());
    	
    	showBoard(prepareBoard());
    	
    }
}
////////////////////////////////////////////////////////////////////

class Book {
    	private String title;
    	private double price;
    	
    	public Book(String title, double price)
    	{
    		this.title = title;
    		this.price = price;
    	}
    	
    	public String getTitle(){ return title; }
    	public double getPrice(){ return price; }
    	
    }


class Pawn 
 {
 	String color;
 	
 	public Pawn(String color)
 	{
 		this.color = color;
 	}
 }
