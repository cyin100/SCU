/**
 *	Conner Yin
 *	DataDisplay.java
 * 	Displays values from DataManager.java on a GUI using Graphics2D
 */

import java.awt.*;
import java.awt.geom.*;
import java.awt.Graphics2D;
import java.util.Map;

import javax.swing.*;

//////////////////////////////////////////////////////////////////////////////////////////
class DataDisplay extends JFrame {
	  DataManager dm;
	  Map<String,Sales> data;
	  
	   public DataDisplay( String titleText, DataManager dm ) {
	      super( titleText );
	      this.dm = dm;
      
	      // Include statements to read data from file,C://data/sales.txt"  
	      dm.readDataFromFile("/home/chyin/COEN160/lab7/lab7/src/sales.txt");
	      data = dm.getData();
		  
	      setDefaultCloseOperation( JFrame.EXIT_ON_CLOSE );
	      DrawingPanel dp = new DrawingPanel();
	      getContentPane().add( dp, BorderLayout.CENTER );
	      setSize( 800, 500 );
	      setVisible( true );
	   }

	   class DrawingPanel extends JPanel {
	     
	      public DrawingPanel() {
	         setBackground( Color.white );
	         setBorder( BorderFactory.createTitledBorder(
	            "Data Display" ) );
	      }
	      /** Draws the text, lines, and shapes in the
	        * specified graphics context
	        * @param g the component's graphics context
	        */
	      public void paintComponent( Graphics gp ) {
	         
	         super.paintComponent(gp);
	         
	         // Cast the graphics objects to Graphics2D
	         Graphics2D g = (Graphics2D) gp;
	         
	         g.setRenderingHint(RenderingHints.KEY_ANTIALIASING,RenderingHints.VALUE_ANTIALIAS_ON);
	         g.setStroke(new BasicStroke(5.0f));
	         
	         Font newFont;
	         int startX, startY, endX, endY, amt;
	         Line2D line;
	         
	         startX = 100;
	         startY = 100;
	         g.setPaint(Color.black);  
	         newFont = new Font("Ariel",Font.BOLD,25);         
	         g.setFont(newFont);
	         g.drawString("Sales Data 2013-2015", startX, startY );  
	         
	         // EXERCISE 3B
	         newFont = new Font("Courier",Font.PLAIN,25);   
	         g.setFont(newFont);
	         g.setPaint(Color.blue); 
	         startX = 50;
	         startY = 200;
	          
	         g.drawString(data.get("2014-4").toString(), startX, startY );  
	         g.setPaint(Color.green);           
	         startX = 50;
	         startY = 300;
	         g.drawString(data.get("2014-2").toString(), startX, startY );  
	         
	         // EXERCISE 3C
	         newFont = new Font("Courier",Font.PLAIN,25);   
	         g.setFont(newFont);
	         g.setPaint(Color.blue);
	         amt = data.get("2014-4").salesInK;
	         startX = 50;
	         startY = 200;
	         endX = startX + amt;
	         endY = startY;
	         g.drawLine(startX, startY, endX, endY);
	         g.drawString("2014-4", endX + 10, startY );  
	         
	         g.setPaint(Color.green);
	         amt = data.get("2013-3").salesInK;
	         startX = 50;
	         startY = 250;
	         endX = startX + amt;
	         endY = startY;
	         g.drawLine(startX, startY, endX, endY);
	         g.drawString("2013-2", endX + 10, startY );  
	         
	         g.setPaint(Color.red);
	         amt = data.get("2014-2").salesInK;
	         startX = 50;
	         startY = 300;
	         endX = startX + amt;
	         endY = startY;
	         g.drawLine(startX, startY, endX, endY);
	         g.drawString("2014-2", endX + 10, startY );  
	      }
	   }
}
