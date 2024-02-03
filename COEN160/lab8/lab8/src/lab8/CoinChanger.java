/**
 * 	Conner Yin
 * 	CoinChanger.java
 * 	GUI interface for getting change for specific amount (input TextField)
 * 	to coin amounts (dollars, quarters, etc.)
 */


package lab8;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

class CoinChanger extends JFrame implements ActionListener {
	private JButton getChangeButton;
	private JTextField amountField, dollarsField, quartersField, dimesField,
		nickelsField, penniesField;
	private JLabel amountLabel, dollarsLabel, quartersLabel, dimesLabel,
		nickelsLabel, penniesLabel;
	
	public CoinChanger() {
		super( "CoinChanger" );
		
		// get content pane
		Container container = getContentPane();
		container.setLayout(new GridLayout(0,2));
		
		// create labels
		amountLabel = new JLabel("Amount");
		dollarsLabel = new JLabel("Dollars");
		quartersLabel = new JLabel("Quarters");
		dimesLabel = new JLabel("Dimes");
		nickelsLabel = new JLabel("Nickels");
		penniesLabel = new JLabel("Pennies");
		
		// createFields
		amountField = new JTextField();
		dollarsField = new JTextField();
		quartersField = new JTextField();
		dimesField = new JTextField();
		nickelsField = new JTextField();
		penniesField = new JTextField();
		
		dollarsField.setEditable(false);
		quartersField.setEditable(false);
		nickelsField.setEditable(false);
		dimesField.setEditable(false);
		penniesField.setEditable(false);
		
		// create button
		getChangeButton = new JButton("Get Change");
		
		// add them all to the container
		container.add(amountLabel);
		container.add(amountField);
		container.add(dollarsLabel);
		container.add(dollarsField);
		container.add(quartersLabel);
		container.add(quartersField);
		container.add(dimesLabel);
		container.add(dimesField);
		container.add(nickelsLabel);
		container.add(nickelsField);
		container.add(penniesLabel);
		container.add(penniesField);
		container.add(getChangeButton);
		
		// add event handlers
		getChangeButton.addActionListener(this);
		
		pack();
		setSize(400,400);
		setLocationRelativeTo(null);
		setVisible( true );
	}
	
	public void actionPerformed( ActionEvent event ){
		// Complete the event handler
		int amount = Integer.parseInt(amountField.getText());
		
		int dollars = amount / 100;
		amount -= 100 * dollars;
		int quarters = amount / 25;
		amount -= 25 * quarters;
		int dimes = amount / 10;
		amount -= 10 * dimes;
		int nickels = amount / 5;
		amount -= 5 * nickels;
		int pennies = amount;
		
		dollarsField.setText(String.valueOf(dollars));
		quartersField.setText(String.valueOf(quarters));
		dimesField.setText(String.valueOf(dimes));
		nickelsField.setText(String.valueOf(nickels));
		penniesField.setText(String.valueOf(pennies));
	}
	
	public static void main( String [] args ){
		CoinChanger application = new CoinChanger();
		application.setDefaultCloseOperation(
		JFrame.EXIT_ON_CLOSE );
	}
}