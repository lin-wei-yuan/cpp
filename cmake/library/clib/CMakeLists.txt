cmake_minimum_required( VERSION 3.6.0 )
project( CLib )
include_directories( include )
# Set all .cpp files to variable SOURCES
file( GLOB SOURCES "src/*.cpp" )
add_library( CLib STATIC ${SOURCES} )
target_include_directories (CLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
