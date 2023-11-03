#ifndef REQUEST_INTERFACE_HEADER
#define REQUEST_INTERFACE_HEADER
#include <iostream>

class IRequest {
public:
  virtual void request() = 0;
};
#endif