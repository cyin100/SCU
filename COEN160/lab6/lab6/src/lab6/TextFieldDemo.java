/*
 * Conner Yin
 * 10/30/2023
 * TextFieldDemo.java
 * Creates container with JTextFields for first, middle, and last names. When 
 * a JButton is pressed, convert into Last, First M. format and display in
 * separate "full name" JTextField
 */

package lab6;
import javax.swing.*;

import java.awt.*;
import java.awt.event.*;

public class TextFieldDemo extends JFrame implements ActionListener {

	//Class Declarations
	JTextField firstTF, middleTF, lastTF, fullTF;
	JButton fullNameButton;
	
	//Constructor
	public TextFieldDemo() {
		super("TextField  Demo");
		setLocationRelativeTo(null);
		Container container = getContentPane();
		container.setLayout(new BorderLayout());
		
		JPanel inputPanel = new JPanel();
		JPanel outputPanel = new JPanel();
		JPanel buttonPanel = new JPanel();
		
		firstTF = new JTextField(10);
		middleTF = new JTextField(10);
		lastTF = new JTextField(10);
		inputPanel.add(new JLabel("First Name"));
		inputPanel.add(firstTF);
		inputPanel.add(new JLabel("Middle"));
		inputPanel.add(middleTF);
		inputPanel.add(new JLabel("Last Name"));
		inputPanel.add(lastTF);
		
		fullTF = new JTextField(10);
		fullTF.setEditable(false);	
		outputPanel.add(new JLabel("Full Name"));
		outputPanel.add(fullTF);
		
		fullNameButton = new JButton("Full Name");
		buttonPanel.add(fullNameButton);
		
		container.add(inputPanel, BorderLayout.NORTH);
		container.add(outputPanel, BorderLayout.CENTER);
		container.add(buttonPanel, BorderLayout.SOUTH);
		
		fullNameButton.addActionListener(this);
		
		setSize(600, 150);
		setVisible(true);
	}

		public void actionPerformed(ActionEvent e) {
			
			if (e.getSource() == fullNameButton) {
				String input = lastTF.getText() + ", " + firstTF.getText() 
						+ " " + middleTF.getText().charAt(0) + ".";
				fullTF.setText(input.toUpperCase());
			}
	}
	//Main Program that starts Execution
	public static void main(String args[]) {
		TextFieldDemo test = new TextFieldDemo();
		test.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}
}


