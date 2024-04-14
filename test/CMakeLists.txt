cmake_minimum_required(VERSION 3.26)

project(CmakeConfigPackageTests
        LANGUAGES CXX)


set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g") # may not be needed
#################### GOOGLE TESTS ####################

add_executable(testsTarget tests.cpp)
enable_testing()
# Printing of set doublyLinkedList_warnings and doublyLinkedList_options INTERFACE libraries properties

get_target_property(WARNINGS doublyLinkedList_warnings INTERFACE_COMPILE_OPTIONS)
message(VERBOSE "testsTarget WARNINGS: ${WARNINGS}")

get_target_property(OPTIONS doublyLinkedList_options INTERFACE_COMPILE_OPTIONS)
message(VERBOSE "testsTarget OPTIONS: ${OPTIONS}")

target_link_libraries(testsTarget
    PRIVATE doublyLinkedList::doublyLinkedList_warnings
            doublyLinkedList::doublyLinkedList_options

            gtest_main
            DoublyLinkedSortedList)

add_test(NAME mainZeroArgs COMMAND main)
