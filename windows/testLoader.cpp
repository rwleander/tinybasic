//  test file loader

#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "objLoader.h"
#include "objStatementList.h"
#include "objStatement.h"


int main() {
  objLoader loader;
  objStatementList codeList;
  bool ok;

//  setup

codeList.begin();  
  
//  test default constructor

  printf("Testing default constructor method\n");  
  assert (strcmp(loader.fileName, "") == 0);

//  test build file name

  printf("Testing build file name method\n");
  ok = loader.buildFileName("SAVE TESTFILE");
  assert(ok == true);
  assert (strcmp(loader.fileName, "basic\\TESTFILE.bas") == 0);

//  test for bad command

  printf("Testing build file name with bad command\n");
  ok = loader.buildFileName("SAVE");
  assert(ok == false);

//  test save file method\n

  printf("Testing save test file 1 method\n");
  codeList.clear();
  codeList.add(new objStatement("10 LET A = 1"));
  codeList.add(new objStatement("20 LET B = 2"));
  codeList.add(new objStatement("30 PRINT A + B"));
  assert(codeList.count == 3);  
  ok = loader.saveFile("SAVE TESTFILE1", codeList);  
  assert (ok == true);
  assert(strcmp(loader.msg, "") == 0);
  
  //  write test file 2
  
    printf("Testing save test file 2 method\n");
  codeList.clear();
  codeList.add(new objStatement("10 LET X = 10"));
  codeList.add(new objStatement("20 LET Y = 30"));
  codeList.add(new objStatement("30 LET Z = 2"));
  codeList.add(new objStatement("40 PRINT X * Y / z"));
  assert(codeList.count == 4);  
  ok = loader.saveFile("SAVE TESTFILE2", codeList);  
  assert (ok == true);
  assert(strcmp(loader.msg, "") == 0);

//  test bad file name  

printf("test write bad file\n");
ok = loader.saveFile("SAVE TEST//FILE.", codeList);  
  assert (ok == false);
  assert(strcmp(loader.msg, "cannot create file") == 0);
  
  //  test load file
  printf("testing load file\n");
  codeList.clear();
  ok = loader.loadFile("LOAD TESTFILE1", codeList);
  assert (ok == true);
  assert (codeList.count == 3);
  assert(codeList.getSequence(0) == 10);
  assert(strcmp(codeList.getText(0), "LET A = 1") == 0);
assert (codeList.getSequence(2) == 30);
assert(strcmp(codeList.getText(2), "PRINT A + B")==  0);
  
  //  test load  missing file
  
  printf("testing read missing file\n");
  ok = loader.loadFile("LOAD XYZZY", codeList);
  assert (ok == false);
  assert (strcmp(loader.msg, "cannot find file") == 0);
  
//  done

printf("tests complete\n");
  return 0;
}
