#include <iostream>
#include <string>

using namespace std;

class NumberException {

public:
   NumberException(const string& msg) : msg_(msg) {}
  ~NumberException() {}

   string getMessage() const { return(msg_); }
private:
   string msg_;
};