package com.ktereyp.utils;

public class Calculator {
	public static final String ERROR = "ERROR";

	private static class ExpressionTree {
		char OPRATOR = '\0';
		String number = null;
		ExpressionTree parent = null;
		ExpressionTree leftItem = null;
		ExpressionTree rightItem = null;

		public boolean isEmpty() {
			return OPRATOR == '\0' && number == null && parent == null && leftItem == null
					&& rightItem == null;
		}

		public boolean isBootom() {
			return leftItem == null && rightItem == null;
		}

		public boolean isOperator() {
			return OPRATOR != '\0';
		}
	}

	private static ExpressionTree buildTree(String s) {
		if (s == null || s.equals(""))
			return null;
		ExpressionTree tree = null;
		ExpressionTree current = new ExpressionTree();
		ExpressionTree subTree = null;
		int start = 0;
		int cursor = 0;
		for (; cursor < s.length();) {
			char c = s.charAt(cursor);

			// 小数点不能有两个
			if (c == '.') {
				String lastN = s.substring(start, cursor);
				int n = lastN.indexOf('.');
				if (n != -1)
					return null;
			}

			// 括号
			if (c == ')') {
				int i;
				for (i = cursor; i >= 0; i--) {
					if (s.charAt(cursor) == '(')
						break;
				}
				if (i < 0)
					return null;
			}

			if (c == '(') {
				int count = 1;
				cursor++;
				for (; cursor < s.length(); cursor++) {
					if (s.charAt(cursor) == '(')
						count++;
					if (s.charAt(cursor) == ')')
						count--;
					if (count == 0) {
						break;
					}
				}
				if (count != 0)
					return null;

				String subs = s.substring(start + 1, cursor);
				subTree = buildTree(subs);
				if (subTree == null)
					return null;

				cursor++;
				if (cursor == s.length()) {
					current = current.parent;
					current.rightItem = subTree;
					current.rightItem.parent = current;
					break;
				} else {
					c = s.charAt(cursor);
					if (!(c == '^' || c == '*' || c == '/' || c == '+' || c == '-'))
						return null;
				}
			}

			if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
				if (cursor == 0 && c != '-')
					return null;
				char c_a_1 = '\0';
				if (cursor + 1 < s.length()) {
					c_a_1 = s.charAt(cursor + 1);
					if (c_a_1 == '+' || c_a_1 == '*' || c_a_1 == '/' || c_a_1 == '^') {
						return null;
					}
				}

				if (current.parent == null) {
					current.OPRATOR = c;
					current.leftItem = new ExpressionTree();
					current.leftItem.parent = current;
					current.leftItem.number = s.substring(start, cursor);
					try {
						double test = Double.valueOf(current.leftItem.number);
					} catch (NumberFormatException e) {
						return null;
					}
					current.rightItem = new ExpressionTree();
					current.rightItem.parent = current;
					current = current.rightItem;

					start = cursor + 1;
					cursor++;
					if (c_a_1 == '-')
						cursor++;
					continue;
				}

				if (isHightPriority(current.parent.OPRATOR, c)) {
					ExpressionTree insert = getLessAndEqueralPriority(current.parent, c);
					if (subTree != null) {
						current = current.parent;
						current.rightItem = subTree;
						current.rightItem.parent = current;
						subTree = null;
					} else {
						current.number = s.substring(start, cursor);
						try {
							double test = Double.valueOf(current.number);
						} catch (NumberFormatException e) {
							return null;
						}
					}

					current = new ExpressionTree();
					if (insert.parent != null) {
						current.parent = insert.parent;
						current.parent.rightItem = current;
					}
					current.leftItem = insert;
					current.leftItem.parent = current;
					current.OPRATOR = c;
					current.rightItem = new ExpressionTree();
					current.rightItem.parent = current;
					current = current.rightItem;

				} else {
					current.OPRATOR = c;
					if (subTree != null) {
						current.leftItem = subTree;
						current.leftItem.parent = current;
						subTree = null;
					} else {
						current.leftItem = new ExpressionTree();
						current.leftItem.parent = current;
						current.leftItem.number = s.substring(start, cursor);
						try {
							double test = Double.valueOf(current.leftItem.number);
						} catch (NumberFormatException e) {
							return null;
						}
					}
					current.rightItem = new ExpressionTree();
					current.rightItem.parent = current;
					current = current.rightItem;
				}
				start = cursor + 1;
				cursor++;
				if (c_a_1 == '-')
					cursor++;

			} else {
				cursor++;
			}
			tree = getTop(current);
		}

		if (start != s.length()) {
			current.number = s.substring(start, cursor);
		}

		while (current.parent != null) {
			tree = current.parent;
			current = tree;
		}
		return tree;
	}

	private static ExpressionTree getTop(ExpressionTree tree) {
		while (tree.parent != null) {
			tree = tree.parent;
		}
		return tree;
	}

	private static ExpressionTree getLessAndEqueralPriority(ExpressionTree tree, char operator) {
		tree = tree.parent;
		while (tree != null) {
			if (!isHightPriority(tree.OPRATOR, operator))
				return tree.rightItem;
			tree = tree.parent;
		}
		return tree;
	}

	private static boolean isHightPriority(char f, char s) {
		if (f == '^') {
			if (s != '^')
				return true;
		}

		if (f == '*' || f == '/') {
			if (s == '+' || s == '-') {
				return true;
			}
		}

		return false;
	}

	private static void printExpressionTree(ExpressionTree tree) {
		if (tree == null || tree.isEmpty())
			return;
		if (tree.leftItem != null) {
			printExpressionTree(tree.leftItem);
			System.out.print(tree.OPRATOR);
		} else {
			System.out.print(tree.number);
			return;
		}

		if (tree.rightItem != null) {
			printExpressionTree(tree.rightItem);
		} else {
			if (tree.isOperator())
				System.out.println(tree.OPRATOR);
			else
				System.out.print(tree.number);
			return;
		}
	}

	private static String innerCalculate(ExpressionTree tree) {
		if (tree == null || tree.isEmpty())
			return null;
		String result_left = null;
		String result_right = null;

		if (tree.leftItem != null) {
			result_left = innerCalculate(tree.leftItem);
		} else {
			return tree.number;
		}

		if (tree.rightItem != null) {
			result_right = innerCalculate(tree.rightItem);
		} else {
			return tree.number;
		}

		if (result_left == null || result_right == null) {
			return null;
		}

		double left = Double.valueOf(result_left);
		double right = Double.valueOf(result_right);
		switch (tree.OPRATOR) {
			case '^': {
				return String.valueOf(Math.pow(left, right));
			}
			case '*': {
				return String.valueOf(left * right);
			}
			case '/': {
				if (right >= 0.0 && right < Double.MIN_VALUE)
					return null;
				return String.valueOf(left / right);
			}
			case '+': {
				return String.valueOf(left + right);
			}
			case '-': {
				return String.valueOf(left - right);
			}
		}
		return null;
	}

	public static String calculate(String s) {
		ExpressionTree tree = buildTree(s);
		String result = innerCalculate(tree);
		return result;
	}

	public static void main(String[] args) {
		// String s = "1+32^2*(2+4)+3";
		// ExpressionTree tree = buildTree(s);
		//
		// printExpressionTree(tree);
		// System.out.print(" = ");
		// System.out.print(calculator(tree) + ' ' + '\n');
		// System.out.println("finished");
	}
}
