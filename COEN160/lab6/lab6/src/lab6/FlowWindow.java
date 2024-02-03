/*
 * Conner Yin
 * 10/30/2023
 * FlowWindow.java
 * Creates a Flow Window with several buttons that when clicked, prompt
 * the dialogue box to display which button was pressed
 */

package lab6;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class FlowWindow extends JFrame implements ActionListener {
    
	JButton b1, b2, b3, b4, b5;
	
    public FlowWindow() {
    	
    	/*
    	 * 	1a) adding this line changes the start location of the
    	 * 		GUI window to the center of the screen rather than
    	 * 		top left of the screen
    	 */
    	setLocationRelativeTo(null);
    	
    	setTitle("FlowLayout");
    	
        Container contentPane = getContentPane();
        
        /*
         *	// FlowLayout (int align, int hgap, int vgap);
         * 	1b) Changing the vgap parameter to 30 increases the size
         * 		of the vertical gap, adding more space above and below the buttons
         */
   		contentPane.setLayout(new FlowLayout(FlowLayout.RIGHT, 5, 30));
        
   		/*
   		 * 	1c)	Default layout for JPanel i FlowLayout, default for
   		 * 		JFrame is BorderLayout
   		 */
   		JPanel panel = new JPanel();
   		b1 = new JButton("Button 1");
   		b2 = new JButton("BT2");
   		b3 = new JButton("Button 3");
   		b4 = new JButton("Long-Named Button 4");
   		b5 = new JButton("Button 5");
   		
		panel.add(b1);
		panel.add(b2);
        panel.add(b3);
        panel.add(b4);
        panel.add(b5);
        
        b1.addActionListener(this);
        b2.addActionListener(this);
        b3.addActionListener(this);
        b4.addActionListener(this);
        b5.addActionListener(this);
        
        contentPane.add(panel);

		setDefaultCloseOperation(EXIT_ON_CLOSE);
		pack();
		setVisible(true);
    }
     public void actionPerformed( ActionEvent event ){
         JOptionPane.showMessageDialog( null,
            "You pressed: " + event.getActionCommand() );
    }
    public static void main(String args[]) {
        FlowWindow window = new FlowWindow();
      
    }
}
