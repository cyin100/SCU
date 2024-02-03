// Exercise4.java


class RandomNumbers2 {
	
	public static void genRandNum(){
		
		// Create an instance of Random() and call the nextInt(range) method
		// to generate numbers in that range.
		
		Random randomGen = new Random();
		
		System.out.println(randomGen.nextInt(10)); // generates one number in 
												   // the range 0-10. 

		
		// Modify the program such that the method takes 2 parameters, namely,
		// the range and a count of how many numbers to generate in the method.
		// The method should generate and prints all the numbers in the range,
		// including all the numbers in the range. 
				
	}

}


public class Exercise4 {

    public static void tester () {
    	
    	// Generate 10 numbers in the range of 0-10
     	RandomNumbers2.genRandNum(50,10);
    		
    }
    
    
}