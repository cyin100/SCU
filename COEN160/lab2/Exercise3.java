// Exercise3.java

class RandomNumbers {
	
	public static void genRandNum(int range, int count){

		for(int i=0; i<count; i++)
			System.out.println((int)(range * Math.random()));
		
	}
}


public class Exercise3 {

    public static void tester () {
    	
    	// Generate 10 numbers in the range of 0-10
     	RandomNumbers.genRandNum(10,10);
    		
    }
    
    
}