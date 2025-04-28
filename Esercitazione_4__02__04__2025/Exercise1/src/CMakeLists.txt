list(APPEND DotProduct_headers ${CMAKE_CURRENT_SOURCE_DIR}/Utils.hpp)
list(APPEND DotProduct_sources ${CMAKE_CURRENT_SOURCE_DIR}/Utils.cpp)
list(APPEND DotProduct_sources ${CMAKE_CURRENT_SOURCE_DIR}/ClassObj.hpp)

list(APPEND DotProduct_includes ${CMAKE_CURRENT_SOURCE_DIR})

set(DotProduct_sources ${DotProduct_sources} PARENT_SCOPE)
set(DotProduct_headers ${DotProduct_headers} PARENT_SCOPE)
set(DotProduct_includes ${DotProduct_includes} PARENT_SCOPE)
