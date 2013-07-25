enable_testing()

find_package(Check REQUIRED)
include_directories(${CHECK_INCLUDE_DIRS})
set(LIBS ${LIBS} ${CHECK_LIBRARIES} BigIntegerOps)

add_executable(TestBigInteger BigIntegerTest.c)
target_link_libraries(TestBigInteger ${LIBS})
add_test(TestBigInteger ${CMAKE_CURRENT_BINARY_DIR}/TestBigInteger)

