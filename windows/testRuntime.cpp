//  test runtime class

#include "objRuntime.h"
#include "objStatement.h"
#include "objStatementList.h"
#include "objVariables.h"

#include <string.h>
#include <stdio.h>
#include <assert.h>

int main() {
objRuntime runtime;
objStatementList codeList;
char buff[100];
int n;
bool ok;

//  setup

printf("Testing runtime\n");

runtime.begin();
codeList.begin();

//  test find token methods
//  simple test

printf("Testing find tokens method - print a\n");
n = runtime.findTokens("PRINT A");
assert(runtime.count == 2);
assert(strcmp(runtime.tokens[0], "PRINT") == 0);
assert(strcmp(runtime.tokens[1], "A") == 0);
assert (n == 2);

//  test get tokens with commas

printf("Testing get token method with commas\n");
n = runtime.findTokens("PRINT A, B");
assert(runtime.count == 4);
assert(strcmp(runtime.tokens[0], "PRINT") == 0);
assert(strcmp(runtime.tokens[1], "A") == 0);
assert(strcmp(runtime.tokens[2], ",") == 0);
assert(strcmp(runtime.tokens[3], "B") == 0);

//  test more complex expression

printf("Testing get token method with parenthesis\n");
n = runtime.findTokens("LET A = B * (C + D)");
assert(runtime.count == 10);
assert(strcmp(runtime.tokens[0], "LET") == 0);
assert(strcmp(runtime.tokens[1], "A") == 0);
assert(strcmp(runtime.tokens[2], "=") == 0);
assert(strcmp(runtime.tokens[3], "B") == 0);
assert(strcmp(runtime.tokens[4], "*") == 0);
assert(strcmp(runtime.tokens[5], "(") == 0);
assert(strcmp(runtime.tokens[6], "C") == 0);
assert(strcmp(runtime.tokens[7], "+") == 0);
assert(strcmp(runtime.tokens[8], "D") == 0);
assert(strcmp(runtime.tokens[9], ")") == 0);

//  test find tokens with function

printf("Testing get token method with function\n");
n = runtime.findTokens("LET A = ABS(X)"); 
assert(runtime.count == 7);
assert(strcmp(runtime.tokens[0], "LET") == 0);
assert(strcmp(runtime.tokens[1], "A") == 0);
assert(strcmp(runtime.tokens[2], "=") == 0);
assert(strcmp(runtime.tokens[3], "ABS") == 0);
assert(strcmp(runtime.tokens[4], "(") == 0);
assert(strcmp(runtime.tokens[5], "X") == 0);
assert(strcmp(runtime.tokens[6], ")") == 0);

//  test is valid number\n

printf("Testing is valid number\n");
assert(runtime.isValidNumber("123") == true);
assert(runtime.isValidNumber("-123.45") == true);
assert (runtime.isValidNumber("BAD") == false);

//  test print function

printf("Testing print with one number\n");
n = runtime.findTokens("PRINT 5");
assert(n == 2);
ok = runtime.runPrint(buff);
assert(ok == true);
assert (strcmp(buff, "5.000000\n") == 0);

printf("Testing print with one literal\n");
n = runtime.findTokens("PRINT \"This is a test\"");
assert(n == 2);
ok = runtime.runPrint(buff);
assert(ok == true);
assert (strcmp(buff, "This is a test\n") == 0);

printf("Testing print with one expression\n");
n = runtime.findTokens("PRINT 2 + 2");
ok = runtime.runPrint(buff);
assert(ok == true);
assert(strcmp(buff, "4.000000\n") == 0);

printf("Testing print with two numbers\n");
n = runtime.findTokens("PRINT 2, 3");
ok = runtime.runPrint(buff);
assert(ok == true);
assert(strcmp(buff, "2.000000  3.000000\n") == 0);

printf("Testing print with two expressions\n");
n = runtime.findTokens("PRINT 2 + 3, 2 * 3");
ok = runtime.runPrint(buff);
assert(ok == true);
assert(strcmp(buff, "5.000000  6.000000\n") == 0);

printf("Testing print with literal and expression\n");
n = runtime.findTokens("PRINT \"3 + 4 = \", 3 + 4");
ok = runtime.runPrint(buff);
assert(ok == true);
assert(strcmp(buff, "3 + 4 =   7.000000\n") == 0);

//  test let

printf ("Testing basic let statement\n");
n = runtime.findTokens("LET A = 1");
assert(n == 4);
ok = runtime.runLet();
assert(ok == true);
assert (runtime.varList.getVariable('A') == 1);

//  test more complex let statement\n

printf ("Testing longer let statement\n");
n = runtime.findTokens("LET B = 2 * (3 + 4)");
ok = runtime.runLet();
assert(ok == true);
assert(runtime.varList.getVariable('B') == 14);

//  test let with variables

printf ("Testing  let statement with variables\n");
n = runtime.findTokens("LET C = A + B");
ok = runtime.runLet();
assert(ok == true);
assert(runtime.varList.getVariable('C') == 15);

//  test let with abs function

printf ("Testing  let statement with function\n");
n = runtime.findTokens("LET C = ABS(5 - 7)");
ok = runtime.runLet();
assert(ok == true);
assert(runtime.varList.getVariable('C') == 2);


printf ("Testing  let statement with calculations and function\n");
n = runtime.findTokens("LET C = 3 + ABS(5 - 7) * 2");
ok = runtime.runLet();
assert(ok == true);
assert(runtime.varList.getVariable('C') == 7);

//  test let with pi 
//  test let with pi 
//  test let with pi function

printf ("Testing  let statement with pi function\n");
float pi = 3.14159;
n = runtime.findTokens("LET C = PI()");
ok = runtime.runLet();
assert(ok == true);
assert(runtime.varList.getVariable('C') == pi);

//  test let with error

printf ("Testing  let statement with error\n");
n = runtime.findTokens("LET C = A +");
ok = runtime.runLet();
assert(ok == false);
assert(strcmp(runtime.msg, "Bad expression") == 0);


printf ("Testing  let statement with another error\n");
n = runtime.findTokens("LET = A + B");
ok = runtime.runLet();
assert(ok == false);
assert(strcmp(runtime.msg, "Bad statement") == 0);

//  test go to_char_type

printf("Testing go to\n");
n = runtime.findTokens("GOTO 50");
ok = runtime.runGoto();
assert(ok == true);
assert(runtime.nextAddress == 50);

//  test if statement

printf("Testing runIf method \n");
n = runtime.findTokens("IF 4 <= 2 THEN 30");
runtime.nextAddress = 20;
ok = runtime.runIf();
assert(ok == true);
assert(runtime.nextAddress == 20);

n = runtime.findTokens("IF 4 >= 2 THEN 30");
ok = runtime.runIf();
assert(ok == true);
assert(runtime.nextAddress == 30);

//  test longer if

printf("Testing longer runIf method \n");
n = runtime.findTokens("IF 1.5 >= 0.001 THEN 150");
assert(runtime.count == 6);
runtime.nextAddress = 20;
ok = runtime.runIf();
assert(ok == true);
assert(runtime.nextAddress == 150);

//  test gosub / return

printf("Testing gosub statement \n");
n = runtime.findTokens("GOSUB 100");
runtime.nextAddress = 20;
runtime.goCount = 0;
ok = runtime.runGosub();
assert(ok == true);
assert(runtime.nextAddress == 100);
assert(runtime.goCount = 1);
assert(runtime.goStack[0] == 20);

n = runtime.findTokens("RETURN");
ok = runtime.runReturn();
assert(ok == true);
assert(runtime.nextAddress == 20);
assert(runtime.goCount == 0);
assert(runtime.goStack[0] == 0);

//  test gosub stack overflow

printf("Testing gosub statement with stack overflow \n");
n = runtime.findTokens("GOSUB 100");
runtime.nextAddress = 20;
runtime.goCount = 7;
ok = runtime.runGosub();
assert(ok == false);
assert(strcmp(runtime.msg, "Stack overflow") == 0);

//  test return with empty stack

printf("Testing return  statement with empty stack \n");
n = runtime.findTokens("RETURN");
runtime.nextAddress = 20;
runtime.goCount = 0;
ok = runtime.runReturn();
assert(ok == false);
assert(strcmp(runtime.msg, "Stack underflow") == 0);

//  test stop statement

printf("Testing stop statement \n");
n = runtime.findTokens("STOP");
runtime.nextAddress = 20;
ok = runtime.runStop();
assert(ok == true);
assert(runtime.nextAddress == -1);

//  test basic run method

printf("Testing basic run method\n");
codeList.clear();
codeList.add(new objStatement("10 LET A = 1"));
codeList.add(new objStatement("20 LET B = 2"));
codeList.add(new objStatement("30 LET C = A + B"));
ok = runtime.run(codeList);
assert(ok == true);
assert(runtime.varList.getVariable('A') == 1);
assert(runtime.varList.getVariable('B') == 2);
assert(runtime.varList.getVariable('C') == 3);

//  test run with gosub

printf("Testing  run method with gosub\n");
codeList.clear();
codeList.add(new objStatement("10 LET A = 1"));
codeList.add(new objStatement("20 GOSUB 50"));
codeList.add(new objStatement("30 STOP"));
codeList.add(new objStatement("50 LET A = 2"));
codeList.add(new objStatement("60 RETURN"));
ok = runtime.run(codeList);
assert(ok == true);
assert(runtime.varList.getVariable('A') == 2);

//  test run with nested gosubs

printf("Testing  run method with nested gosubs\n");
codeList.clear();
codeList.add(new objStatement("10 LET A = 1"));
codeList.add(new objStatement("20 GOSUB 50"));
codeList.add(new objStatement("30 STOP"));
codeList.add(new objStatement("50 LET A = 2"));
codeList.add(new objStatement("60 GOSUB 100"));
codeList.add(new objStatement("70 RETURN"));
codeList.add(new objStatement("100 LET A = 3"));
codeList.add(new objStatement("110 RETURN"));
ok = runtime.run(codeList);
assert(ok == true);
assert(runtime.varList.getVariable('A') == 3);

//  done

printf("Tests complete\n");
return 0;
}
