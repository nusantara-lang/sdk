#pragma once

#define NDEBUG_ON

#ifdef NDEBUG_ON

  #include <iostream>
  
  #define NDEBUG_INFO(msg) std::cout << msg << "\n";

  #define NDEBUG_IF(con, code)                                                  \
    if(con) { code }

  #define NDEBUG_ELSE_IF(con, code)                                             \
    else if(con) { code }

  #define NDEBUG_ELSE(code)                                                     \
    else { code }

#else
  #define NDEBUG_INFO(msg)
  #define NDEBUG_IF(con, code)
  #define NDEBUG_ELSE_IF(con, code)
  #define NDEBUG_ELSE(code)
#endif
