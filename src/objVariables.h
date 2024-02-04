//  objVariables.h - collection of variables

class objVariables {
public:
  float values[26];
  
  void begin();
  void clear();
  void setVariable(char v, float n);
  float getVariable(char v);
    
  int getIndex(char v);
};
