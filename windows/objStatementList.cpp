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

//  add a new statement to the list

int objStatementList::add(objStatement* stmt)
{
	
	//  initial add
	
	if (count == 0)
	{
		statementList[0] = stmt;
		count = 1;
		return count;
	}
	
	//  add to end of list
	
	if (statementList[count - 1]->sequence < stmt->sequence) 
	{
		statementList[count] = stmt;
		count++;
		return count;
	}
	
	//  insert into list//  forst move lines down
	
	int i = count - 1;
	while ((i >= 0) && (statementList[i]->sequence > stmt->sequence))
	{
		statementList[i+1] = statementList[i];
		i--;
	}
	
	//  now insert line
	
	statementList[i+1] = stmt;
	count ++;
	return count;
}