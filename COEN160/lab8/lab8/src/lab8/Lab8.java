/**
 *	Conner Yin
 *	Lab8.java
 *	fileCopy() copies from input.txt to output.txt
 * 	wordCount() counts word in each line from input.txt to output.txt
 */

package lab8;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;

class FileProcessor {
	public static void fileCopy(String inputFileName, String outputFileName) throws IOException {
		// Copy text from an input file to an output file
		Scanner in = null;
		PrintWriter out = null;
		String line = null;
		int n;
		in = new Scanner(new File(inputFileName));
		out = new PrintWriter(new FileWriter(outputFileName));
		// Line delimiter is a new line
		in.useDelimiter("\n");
		while (in.hasNext()) {
			line = in.nextLine();
			out.println(line);
		}
		in.close();
		out.close();
	}
	
	public static void wordCount(String inputFileName, String outputFileName) throws IOException {
		// Write line numbers and the number of words per line in the input file, to the output file
		Scanner in = null;
		PrintWriter out = null;
		String line = null;
		String[] tokens;
		int lineNumber = 0;
		in = new Scanner(new File(inputFileName));
		out = new PrintWriter(new FileWriter(outputFileName));
		// Line delimiter is a new line
		in.useDelimiter("\n");
		while (in.hasNext()) {
			line = in.nextLine();
			// split and tokenize the line
			tokens = line.split("\\s+");
			// split line
			// around white space
			lineNumber++;
			out.println("Line " + lineNumber + " No. of words: " + tokens.length);
		}
		in.close();
		out.close();
	}
}

public class Lab8 {
	// Names of input and output files are passed as command 
	// line arguments
	
	public static void main(String[] args) {
		// Make sure that 2 command line arguments are provided
		// First arg args[0]: input file name
		// Second arg: args[1] output file name
		if (args.length < 2) {
			System.out.println("Usage: fileCopy infile outfile");
			System.exit(1);
		}
		String inputFile = args[0];
		String outputFile = args[1];
		try {
			FileProcessor.fileCopy(inputFile, outputFile);
		} catch (IOException e) {
			System.out.println(e);
		}
		
		try {
			FileProcessor.wordCount(inputFile, outputFile);
		} catch (IOException e) {
			System.out.println(e);
		}
	}
}