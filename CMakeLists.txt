cmake_minimum_required(VERSION 3.12)
project(cpp_red)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -pedantic -Wfatal-errors -O0")

message("CMAKE_CXX_FLAGS_DEBUG:  ${CMAKE_CXX_FLAGS_DEBUG}")

add_executable(cpp_red main.cpp)
add_executable(week_1_assignment_1 week_1/assignment_1/log.cpp)
add_executable(week_1_assignment_2 week_1/assignment_2/sort_by.cpp)
add_executable(week_1_assignment_3 week_1/assignment_3/update_field.cpp)
add_executable(week_1_assignment_4 week_1/assignment_4/bad_macro.cpp)
add_executable(week_1_assignment_5 week_1/assignment_5/uniq_id.cpp)
add_executable(week_1_assignment_6 week_1/assignment_6/table.cpp)
add_executable(week_1_assignment_7 week_1/assignment_7/deque.cpp)
add_executable(week_1_assignment_8 week_1/assignment_8/paginator.cpp)
add_executable(week_2_assignment_1 week_2/assignment_1/compare_students.cpp week_2/assignment_1/sort_students.cpp)
add_executable(week_2_assignment_2 week_2/assignment_2/learner.cpp)