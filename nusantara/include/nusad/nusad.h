#pragma once

#define NUSAD_ON

#ifdef NUSAD_ON

  #include <iostream>
  #define NUSAD_INFO(msg) std::cout << msg << "\n";

  #define NUSAD_IF(con, code)                                                  \
    if(con) { code }

  #define NUSAD_ELSE_IF(con, code)                                             \
    else if(con) { code }

  #define NUSAD_ELSE(code)                                                     \
    else { code }

#else
  #define NUSAD_INFO(msg)
  #define NUSAD_IF(con, code)
  #define NUSAD_ELSE_IF(con, code)
  #define NUSAD_ELSE(code)
#endif
