//  objStatementList.cpp - list of statements

#include "objStatementList.h"
#include "objStatement.h"

//  begin - clear list

 void objStatementList::begin() {
	for (int i =0; i<MAX_LINES; i++) 
		  statementList[i] = 0;	
  count = 0;
}

//  clear method

void objStatementList::clear() {
	for (int i =0; i<MAX_LINES; i++) {
		  if (statementList[i]= 0)
		    delete statementList[i];
		  statementList[i] = 0;
	}
count = 0;
}