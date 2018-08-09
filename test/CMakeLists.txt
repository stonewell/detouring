SET(test_detouring_src
   test_detouring.cpp
)

ADD_LIBRARY(test_detouring SHARED
    ${test_detouring_src}
)

TARGET_INCLUDE_DIRECTORIES(test_detouring PRIVATE
  ".."
)

TARGET_LINK_LIBRARIES(test_detouring
  detouring
)
