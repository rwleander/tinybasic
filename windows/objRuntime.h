//  runtime class - interpret and execute program

#define MAX_TOKENS 25

class objRuntime {
	public:
  char tokenData[150];
  char* tokens[MAX_TOKENS];
  int count = 0;
    
  int findTokens(char* text);  
  
  protected:
    void clearTokens();
	void copyTokens(char* text);
	void getTokenList();
	
};

