# Setup the project
cmake_minimum_required(VERSION 3.8...3.18)
if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()
project(Prac)

# Find Geant4 package
option(WITH_GEANT4_UIVIS "practice_Geant4_1" ON)
if(WITH_GEANT4_UIVIS)
    find_package(Geant4 REQUIRED ui_all vis_all)
else()
    find_package(Geant4 REQUIRED)
endif()

# Set Geant4 include directories
include(${Geant4_USE_FILE})
    include_directories(${PROJECT_SOURCE_DIR}/include)

# Locate sources and headers for this project
file(GLOB sources ${PROJECT_SOURCE_DIR}/source/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

# Add the executable, and link it to the Geant4 libraries
add_executable(practice practice.cc ${sources} ${headers})
target_link_libraries(practice ${Geant4_LIBRARIES})

# Copy all scripts to the build derectory
set(PRACTICE_SCRIPTS init_ter.mac init_vis.mac vis.mac)

foreach(_script ${PRACTICE_SCRIPTS})
    configure_file(${PROJECT_SOURCE_DIR}/${_script} ${PROJECT_BINARY_DIR}/${_script} COPYONLY)
endforeach()


# example standalone
add_custom_target(Prac DEPENDS practice)

# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
install(TARGETS practice DESTINATION bin)
