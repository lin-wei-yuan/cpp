cmake_minimum_required( VERSION 3.6.0 )
project( network )
include_directories( include )
# Set all .cpp files to variable SOURCES
file( GLOB SOURCES "tests/*.cpp" )
add_executable( network ${SOURCES} )

FILE( GLOB_RECURSE LibFiles "include/*.h" )
add_custom_target( headers SOURCES ${LibFiles} )

target_link_libraries(network "-lpthread")
