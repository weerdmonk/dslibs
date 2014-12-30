
# add stack library
add_library(stack SHARED stack.c)

# add stack example
add_executable(example_stack example_stack.c)
target_link_libraries(example_stack stack)

# install stack library and example
install(TARGETS stack DESTINATION lib)
install(TARGETS example_stack DESTINATION bin)

# add list library
add_library(list SHARED list.c)

# add list example
add_executable(example_list example_list.c)
target_link_libraries(example_list list)

# install list library and example
install(TARGETS list DESTINATION lib)
install(TARGETS example_list DESTINATION bin)
