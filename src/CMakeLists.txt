################### Node STATIC LIBRARY ###################
add_library(Node Node.cpp)

# Include the directory containing the header file
target_include_directories(Node
        PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/Node>
)


################### DoublyLinkedSortedList STATIC LIBRARY ###################
add_library(DoublyLinkedSortedList DoublyLinkedSortedList.cpp)

# Include the directory containing the header file
target_include_directories(DoublyLinkedSortedList
        PUBLIC  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/Node>
                $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/DoublyLinkedSortedList>
) # once we do this PUBLIC dir include of .hpp files we can now
  # in test/CMakeLists.txt link "DoublyLinkedSortedList" library to testsTarget
  # and once we do it the #include <DoublyLinkedSortedList.hpp> directive will work just fine
  # compiler/preprocessor/builder/clangd/whatever IDK will see these included .hpp dirs as well
  # but if we did PRIVATE include above these includes wouldnt be visible for our test target
  # after linking DoublyLinkedSortedList


################### MAIN BINARY ###################
# Create executable target for your main source file
add_executable(main main.cpp)

# Link the library to the executable
target_link_libraries(main PRIVATE DoublyLinkedSortedList)
