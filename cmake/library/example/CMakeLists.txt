cmake_minimum_required( VERSION 3.6.0 )
project( CLibDemo )
add_executable( CLibDemo main.cpp )
target_link_libraries( CLibDemo LINK_PUBLIC CLib )
