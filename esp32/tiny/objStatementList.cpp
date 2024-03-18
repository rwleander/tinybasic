//  objStatementList.cpp - list of statements

#include "objStatementList.h"
#include "objStatement.h"
#include <string.h>

//  begin - clear list

void objStatementList::begin() {
  for (int i =0; i<MAX_LINES; i++) {
    statementList[i] = 0;
  }
  count = 0;
}

//  clear method

void objStatementList::clear() {
  for (int i =0; i<MAX_LINES; i++) {
    if (statementList[i]= 0) {
      delete statementList[i];
    }

    statementList[i] = 0;
  }
  count = 0;
}

//  add a new statement to the list

int objStatementList::add(objStatement* stmt) {

//  initial add

  if (count == 0) {
    statementList[0] = stmt;
    count = 1;
    return count;
  }

//  add to end of list

  if (statementList[count - 1]->sequence < stmt->sequence) {
    statementList[count] = stmt;
    count++;
    return count;
  }

//  find position in list

  int n = find(stmt->sequence);

//  if not in list, insert

  if (statementList[n]->sequence != stmt->sequence) {
    insert(stmt, n);
    return count;
  }

//  if no text, delete

  if (strlen(stmt->text) == 0) {
    remove(n);
    return count;
  }

//  otherwise, replace

  replace(stmt, n);
  return count;
}

//--------------------
//  private methods

// find index of line number in list
//  if not in list, return insertion pointer

int objStatementList::find(int sequence) {

///  if nothing in list, return 0

  if (count == 0) {
    return 0;
  }

//  search from end of list

  int i = count - 1;
  while ((i >= 0) && (statementList[i]->sequence > sequence)) {
    i--;
  }

  if (i < 0) {
    return 0;
  }

  if (statementList[i]->sequence == sequence) {
    return i;
  }
  else {
    return i + 1;
  }
}


//  replace a line// delete old, replace with new

void objStatementList::replace(objStatement* stmt, int n)
{

//  make sure index is within range of list

  if ((n >= 0) && (n < count)) {
    delete statementList[n];
    statementList[n] = stmt;
  }
}

//  insert statement into list at insertion pointer

void objStatementList::insert(objStatement* stmt, int n) {

//  if n out of range, do nothing

  if ((n < 0) || (n >= count)) {
    return;
  }

//  otherwise, insert

  int i = count - 1;
  while (i >= n) {
    statementList[i + 1] = statementList[i];
    i--;
  }

  statementList[n] = stmt;
  count++;
}

//  delete at index

void objStatementList::remove(int n) {

//  make sure index is within bounds

  if ((n < 0) || (n >= count)) {
    return;
  }

//  otherwise remove item

  delete statementList[n];
  int i = n;
  while (i <= count) {
    statementList[i] = statementList[i + 1];
    i++;
  }

  count--;
}

