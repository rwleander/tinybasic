//  runtime  - interpret and execute program

#ifndef __objRuntime
#define __objRuntime

#include <hardwareserial.h>

#include "objStatement.h"
#include "objStatementList.h"
#include "objVariables.h"
#include "objExpression.h"
#include "constants.h"


class objRuntime {
public:
  objVariables varList;
  objExpression expr;
  char msg[100];
  char* tokens[MAX_TOKENS];
  int count = 0;
int nextAddress = 0;
int goStack[MAX_GOSTACK];
int goCount = 0;

void begin();
bool run(HardwareSerial* serial, objStatementList& codeList, bool tracer);

bool runGoto();
bool runGosub();
bool runReturn();
bool runIf();
bool runLet();
  bool runPrint(char* output);
  bool runInput(HardwareSerial* serial);
  bool runRem();
  bool runStop();

  int findTokens(char* text);

protected:
  char tokenData[MAX_STRING + MAX_TOKENS];
int sequence;
char* text;
char printerBuff[100];
bool traceFlag = false;
  
  bool runCommand(HardwareSerial* serial);
  bool printExpression(char* output, int n1, int n2); 
  void clearTokens();
  void copyTokens(char* text);
  void getTokenList();
  void stripQuotes(char* txt);
};

#endif
