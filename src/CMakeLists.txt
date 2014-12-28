
add_library(stack SHARED stack.c)

add_executable(example_stack example_stack.c)
target_link_libraries(example_stack stack)

install(TARGETS stack DESTINATION lib)
install(TARGETS example_stack DESTINATION bin)
