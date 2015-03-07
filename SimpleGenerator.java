import java.util.ArrayList;
import java.util.Random;


public class SimpleGenerator {
	private static final String[] VAR_NAMES = {"a", "b", "c", "x", "y", "z", "Romeo", "Juliet", "Hoboman", 
												"Yeoman", "Blackman", "Chocoman", "Baldwin", "Machamp", 
												"x10", "x11", "x12", "eggs", "love", "is", "life", "zhao", "jin"};
	private static final String[] PROC_NAMES = {"ProcHobo", "ProcYolo", "ProcMongo", "ProcProc", "ProccorP", "CropporC", "SUPERLONG"};
	private static final char[] CHAR_SET = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789".toCharArray(); 
	private static final int INT_LIMIT = 1000;
	private static final int VAR_NAME_LIMIT = 5;
	private static final int MAX_ASS_SIZE = 5;
	private static final int NEST_LIMIT = 5;
	private static final int MAX_STMT_SIZE = 5;
	private static final int PROCEDURE_SIZE = 2;
	private static final int COM_LINE = 8;
	private static final int BASE_STMT_SIZE = 5;
	private static final int NUM_TAB = 13;
	private int lineNum = 1;
	
	ArrayList<Integer> usedProcs = new ArrayList<Integer>();
	ArrayList<String> procNames = new ArrayList<String>();
	ArrayList<String> varNames = new ArrayList<String> ();
	ArrayList<Integer> constVal = new ArrayList<Integer>();
	Random random = new Random();
	
	public static void main(String[] args) {
		ArrayList<String> s = new ArrayList<String>();
		SimpleGenerator sg = new SimpleGenerator();
		String all = "";
		
		for(int i = 0; i < PROCEDURE_SIZE; i++) {
			sg.procNames.add(sg.generateProcedureNames());
		}
		for(int i = 0; i < PROCEDURE_SIZE; i++) {
			s.addAll(sg.generateProcedure(BASE_STMT_SIZE, sg.procNames.get(i)));
		}
		for(int i = 0; i < s.size(); i++) {
			all += s.get(i);
			all += "\n";
		}
		System.out.println(all);
	}
	
	ArrayList<String> generateProcedure(int stmt, String proc) {
		int numLines = random.nextInt(stmt) + 1;
		ArrayList<String> statements = new ArrayList<String>();
		
		statements.add("procedure " + proc + " {");
		for(int i = 0; i < numLines; i++) {
			statements.addAll(generateStatement(1, NEST_LIMIT, proc));
		}
		statements.add("}");
		return statements;
	}
	
	ArrayList<String> generateStatement(int nest, int limit, String procName) {
		ArrayList<String> stmt = new ArrayList<String>();
		int rand = random.nextInt(4);
		if(rand == 0) {
			stmt.addAll(generateWhile(nest, limit, procName));
		} else if(rand == 1) {
			stmt.addAll(generateIf(nest, limit, procName));
		} else {
			stmt.add(generateAssigments(nest, procName));
		}
		return stmt;
	}
	
	ArrayList<String> generateWhile(int nest, int limit, String procName) {
		ArrayList<String> list = new ArrayList<String>();
		if(limit <= 0) {
			list.add(generateAssigments(nest, procName));
			return list;
		}
		String temp = "";
		for(int i = 0; i <nest; i++) temp += "\t";
		String foo = temp + "while " + generateVariables2() + " {";
		for(int i = 0; i <COM_LINE - nest; i++) foo += "\t";
		foo = addLineNumber(foo);
		list.add(foo);
		
		int rand = random.nextInt(MAX_STMT_SIZE) + 1;
		for(int i = 0; i < rand; i++) {
			ArrayList<String> tempo = generateStatement(nest+1, limit-1, procName);
			if(tempo.isEmpty()) {
				list.add(generateAssigments(nest, procName));
			} else {
				list.addAll(tempo);
			}
		}
		list.add(temp + "}");
		return list;
	}
	
	ArrayList<String> generateIf(int nest, int limit, String procName) {
		ArrayList<String> list = new ArrayList<String>();
		if(limit <= 0) {
			list.add(generateAssigments(nest, procName));
			return list;
		}
		String temp = "";
		for(int i = 0; i <nest; i++) temp += "\t";
		
		String foo = temp + "if " + generateVariables2() + " then {";
		for(int i = 0; i <COM_LINE - nest; i++) foo += "\t";
		foo = addLineNumber(foo);
		list.add(foo);
		int rand = random.nextInt(MAX_STMT_SIZE) + 1;
		for(int i = 0; i < rand; i++) {
			ArrayList<String> tempo = generateStatement(nest+1, limit-1, procName);
			if(tempo.isEmpty()) {
				list.add(generateAssigments(nest, procName));
			} else {
				list.addAll(tempo);
			}
		}
		
		list.add(temp + "}");
		String foob = temp + "else {";
		for(int i = 0; i <COM_LINE - nest; i++) foob += "\t";
		foob = addLineNumber(foob);
		list.add(foob);
		
		rand = random.nextInt(MAX_STMT_SIZE) + 1;
		for(int i = 0; i < rand; i++) {
			ArrayList<String> tempo = generateStatement(nest+1, limit-1, procName);
			if(tempo.isEmpty()) {
				list.add(generateAssigments(nest, procName));
			} else {
				list.addAll(tempo);
			}
		}
		list.add(temp + "}");
		return list;
	}
	

	
	String generateAssigments(int nest, String procName) {
		String ass = "";
		for(int i = 0; i < nest; i++) ass += "\t";
		int dice = random.nextInt(10);
		if(dice < 3 && procNames.size() > 1) {
			do {
				dice = random.nextInt(procNames.size());
			} while (procNames.get(dice).equals(procName));
			ass += "call " + procNames.get(dice) + ";";
			ass = addLineNumber(ass);
			return ass;
		} 
		
		ass += generateVariables2();
		ass += " = ";
		int rand = random.nextInt(2);
		ass += rand == 0 ? generateConstant() : generateVariables2();
		int length = random.nextInt(MAX_ASS_SIZE);
		for(int i = 0; i < length; i++) {
			int operator = random.nextInt(3);
			if(operator == 0) {
				ass += " + ";
			} else if(operator == 1) {
				ass += " - ";
			} else {
				ass += " * ";
			}
			rand = random.nextInt(2);
			ass += rand == 0 ? generateConstant() : generateVariables2();
		}
		ass += ";";
		
		for(int i = 0; i < COM_LINE - nest; i++) {
			ass += "\t";
		}
		ass = addLineNumber(ass);
		
		return ass;
	}
	
	String generateProcedureNames() {
		int i;
		while(usedProcs.contains(i = random.nextInt(PROC_NAMES.length)));
		String s = PROC_NAMES[i];
		usedProcs.add(i);
		return s;
		/*
		char first = CHAR_SET[random.nextInt(52)];
		int length = random.nextInt(VAR_NAME_LIMIT);
		String var = "";
		var += first;
		for(int i = 0; i < length; i++) {
			var += CHAR_SET[random.nextInt(52)];
		}
		procNames.add((var));
		return var;
		*/
	}
	
	String generateVariables2() {
		int rand = random.nextInt(VAR_NAMES.length);
		return VAR_NAMES[rand];
	}
	
	String generateVariables() {
		int getOld = varNames.size() == 0 ? -1 :random.nextInt(varNames.size() * 2);
		if(getOld != -1 && getOld < varNames.size()) {
			return varNames.get(getOld);
		} else {
			char first = CHAR_SET[random.nextInt(52)];
			int length = random.nextInt(VAR_NAME_LIMIT);
			String var = "";
			var += first;
			for(int i = 0; i < length; i++) {
				var += CHAR_SET[random.nextInt(62)];
			}
			varNames.add((var));
			return var;
		}
	}
	
	int generateConstant() {
		int getOld = constVal.size() == 0 ? -1 : random.nextInt(constVal.size() * 2);
		if(getOld!= -1 && getOld < varNames.size()) {
			return constVal.get(getOld);
		} else {
			return random.nextInt(INT_LIMIT);
		}
	}
	
	String addLineNumber(String s) {
		int length = 0;
		for(int i = 0; i < s.length(); i ++) {
			if(s.charAt(i) == '\t') {
				length += 8;
			} else {
				length++;
			}
		}
		length = length / 8;
		length = NUM_TAB - length;
		while(length > 0) {
			s += "\t";
			length--;
		}
		s = s + "\\\\" + lineNum++;
		return s;
	}
}
