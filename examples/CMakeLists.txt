
# add list example
add_executable(example_list example_list.c)
target_link_libraries(example_list list)

# install list example
#install(TARGETS example_list DESTINATION bin)

####################################

# add stack example
add_executable(example_stack example_stack.c)
target_link_libraries(example_stack stack list)

# install stack example
#install(TARGETS example_stack DESTINATION bin)

####################################

# add queue example
add_executable(example_queue example_queue.c)
target_link_libraries(example_queue queue list)

# install queue example
#install(TARGETS example_queue DESTINATION bin)

####################################

# add graph example
add_executable(example_graph example_graph.c)
target_link_libraries(example_graph graph stack queue list)

# install graph library and example
#install(TARGETS example_graph DESTINATION bin)

####################################

# add btree example
add_executable(example_btree example_btree.c)
target_link_libraries(example_btree btree stack queue list)

# install btree library and example
#install(TARGETS example_btree DESTINATION bin)

####################################

# add sort example
add_executable(example_sort example_sort.c)
target_link_libraries(example_sort sort )

# install sort library and example
#install(TARGETS example_sort DESTINATION bin)

####################################

# add maxheap example
add_executable(example_maxheap example_maxheap.c)
target_link_libraries(example_maxheap maxheap)

# install maxheap example
#install(TARGETS example_maxheap DESTINATION bin)
