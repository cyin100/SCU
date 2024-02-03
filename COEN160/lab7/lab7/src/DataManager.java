/**
 *	Conner Yin
 *	DataManager.java
 *	Utilizes hashmaps to store values from a certain year-quarter's sales
 */

import java.io.*;
import java.util.*;
/////////////////////////////////////////////////////////////////////////////////////////
interface DataGetter {  
    public void readDataFromFile(String fileName);
}
class Sales{
	int quarter;
	int year;
	int salesInK;
	
	public Sales (int quarter, int year,int salesInK){
		this.quarter = quarter;
		this.year = year;
		this.salesInK = salesInK;
	}
	public int getAmount(){
		return salesInK;
	}
	public int getYear(){
		return year;
	}
	public int getQuarter(){
		return quarter;
	}
	public String toString(){
		
		return "Year: "+year +" Quarter: "+quarter +" Sales: "+salesInK;
	}	
}
public class DataManager implements DataGetter{	
	private Map<String, Sales> sales = new HashMap<String, Sales>();

    public void readDataFromFile(String fileName) 
    {
    	Sales saleByQ;
    	BufferedReader reader = null;
    	try {
    
    		File inFile  = new File(fileName);  
    		reader = new BufferedReader(new FileReader(inFile));
        	//Loop as long as there are input lines.
        	String line = null;
        	
        	try {      	
        		while ((line=reader.readLine()) != null) {
            			// split each line into tokens
            		String [] fields = line.split(":");           	    
      				// the String to int conversion 
      				int year = Integer.parseInt(fields[0].trim());
      				
					// Do the same for quarter and year
      				int quarter = Integer.parseInt(fields[1].trim());
      				int salesAmount = Integer.parseInt(fields[2].trim());
      			
      				// Create an instance of Sales
      				saleByQ = new Sales(quarter,year,salesAmount);   
					
      				// place the sale object in the hashmap, sales
		   		    sales.put(makeKey(saleByQ), saleByQ); 
    			} 		
    		}
    		finally{    		
        		reader.close(); 
			}
    	}
    	catch (IOException e) {
            System.err.println(e);
            System.exit(1);
        }
        catch (NumberFormatException e){
      			System.out.println("NumberFormatException: ");
      			System.exit(1);
    	}      	 		
    } 
    public Map<String, Sales> getData(){
    	return sales;
    }
    public String makeKey(Sales oneSale){
    	// Complete this method as follows
    	// Return the oneSale.year concatenated with "-" and oneSale.quarter
    	return oneSale.year + "-" + oneSale.quarter;
    	
    }   
    public static void main(String[] args){
		DataManager manager = new DataManager();
		manager.readDataFromFile("/home/chyin/COEN160/lab7/lab7/src/sales.txt");
		Map<String,Sales> data = manager.getData();
		
		System.out.println(data.get("2014-4"));	
		DataDisplay dd = new DataDisplay("Sales Data 2013-2015", manager);
		
	} 
}