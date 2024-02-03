/*
 * Conner Yin
 * 10/30/2023
 * BorderWindow.java
 * Creates a Border Window demo that when commented, shows the different
 * BorderLayout regions (e.g. NORTH, CENTER, EAST)
 */

package lab6;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class BorderWindow extends JFrame {
     
    public BorderWindow() {
	
		setTitle("BorderLayout");
		Container contentPane = getContentPane();
		// 2a) Removes Button 1 in the North
        contentPane.add(new JButton("Button 1 (NORTH)"),
                        BorderLayout.NORTH);
        contentPane.add(new JButton("2 (CENTER)"),
                        BorderLayout.CENTER);
        // 2d) Removes Button 3 in the West 
        contentPane.add(new JButton("Button 3 (WEST)"),
                        BorderLayout.WEST);
        // 2b) Removes Button 4 in the South
        contentPane.add(new JButton("Long-Named Button 4 (SOUTH)"),
                        BorderLayout.SOUTH);
        // 2c) Removes Button 5 in the East
        contentPane.add(new JButton("Button 5 (EAST)"),
                        BorderLayout.EAST);

        setDefaultCloseOperation(EXIT_ON_CLOSE);
    
		pack();
		setVisible(true);
    }

    public static void main(String args[]) {
        BorderWindow window = new BorderWindow();
    }
}
