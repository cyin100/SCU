/**
 * @(#)Stack.java
 */
class Array {
	private int[] itemList;
	private int maxLength = 10;

	public Array(int length) {
		maxLength = length;
		itemList = new int[maxLength];
	}

	public Array() {
		itemList = new int[maxLength];
	}

	public void add(int index, int element) {
		if (index < maxLength && index >= 0) {
			itemList[index] = element;
		}
	}

	public int remove(int index) throws Exception {
		if (index < maxLength && index >= 0) {
			return itemList[index];
		} else {
			throw new Exception("Invalid index");
		}
	}

	public void show() {
		System.out.print("CurrentElements=");
		for (int i = 0; i < itemList.length; ++i)
			System.out.print(itemList[i] + " ");
		System.out.println();
	}
}

class Stack {
	public Stack(int length) {
		// ToDo: Implement me
	}

	public void push(int value) {
		// ToDo: Implement me
	}

	public int pop() {
		// ToDo: Implement me
		return -1;
	}

	public void showStack() {
		// ToDo: Show the elements in the order of LIFO
	}
}

public class Lab3_Q1 {
	public static void q1() {
		Stack myStack = new Stack(30);

		myStack.push(10);
		myStack.push(20);
		myStack.push(30);
		myStack.push(40);

		System.out.println("pop()=" + myStack.pop());

		myStack.showStack();
	}
}