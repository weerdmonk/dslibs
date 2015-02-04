
# add list library
add_library(list SHARED list.c)

# add list example
add_executable(example_list example_list.c)
target_link_libraries(example_list list)

# install list library and example
install(TARGETS list DESTINATION lib)
install(TARGETS example_list DESTINATION bin)


# add stack library
add_library(stack SHARED stack.c)

# add stack example
add_executable(example_stack example_stack.c)
target_link_libraries(example_stack stack list)

# install stack library and example
install(TARGETS stack DESTINATION lib)
install(TARGETS example_stack DESTINATION bin)


# add queue library
add_library(queue SHARED queue.c)

# add queue example
add_executable(example_queue example_queue.c)
target_link_libraries(example_queue queue list)

# install queue library and example
install(TARGETS queue DESTINATION lib)
install(TARGETS example_queue DESTINATION bin)


# add graph library
add_library(graph SHARED graph.c)

# add graph example
add_executable(example_graph example_graph.c)
target_link_libraries(example_graph graph stack queue list)

# install graph library and example
install(TARGETS graph DESTINATION lib)
install(TARGETS example_graph DESTINATION bin)


# add btree library
add_library(btree SHARED btree.c)

# add btree example
add_executable(example_btree example_btree.c)
target_link_libraries(example_btree btree stack queue list)

# install btree library and example
install(TARGETS btree DESTINATION lib)
install(TARGETS example_btree DESTINATION bin)
