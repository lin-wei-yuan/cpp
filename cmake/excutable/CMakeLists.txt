cmake_minimum_required( VERSION 3.6.0 )
project( hello )
include_directories( include )
# Set all .cpp files to variable SOURCES
file( GLOB SOURCES "src/*.cpp")
add_executable( hello ${SOURCES} )
