
# add list library
add_library(list SHARED list.c)

# install list library
#install(TARGETS list DESTINATION lib)

####################################

# add stack library
add_library(stack SHARED stack.c)

# install stack library
#install(TARGETS stack DESTINATION lib)

####################################

# add queue library
add_library(queue SHARED queue.c)

# install queue library
#install(TARGETS queue DESTINATION lib)

####################################

# add graph library
add_library(graph SHARED graph.c)

# install graph library
#install(TARGETS graph DESTINATION lib)

####################################

# add btree library
add_library(btree SHARED btree.c)

# install btree library
#install(TARGETS btree DESTINATION lib)

####################################

# add sort library
add_library(sort SHARED sort.c)

# install sort library
#install(TARGETS sort DESTINATION lib)

####################################

# add maxheap library
add_definitions(-DOPTIMAL_ALGO)
add_library(maxheap SHARED maxheap.c)

# install maxheap library
#install(TARGETS maxheap DESTINATION lib)
