cmake_minimum_required(VERSION 2.8.3)
project(rs-pose-apriltag)
add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
    message_generation
    nav_msgs
    roscpp
    sensor_msgs
    std_msgs
    )

find_package(realsense2 2.28.0)
if(NOT realsense2_FOUND)
    message(FATAL_ERROR "\n\n Intel RealSense SDK 2.0 is missing, please install it from https://github.com/IntelRealSense/librealsense/releases\n\n")
endif()

find_path(APRILTAG_INC NAMES apriltag.h PATH_SUFFIXES apriltag)
find_library(APRILTAG_LIB apriltag)
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(apriltag DEFAULT_MSG APRILTAG_INC APRILTAG_LIB)
if(APRILTAG_FOUND AND NOT TARGET apriltag)
    add_library(apriltag INTERFACE)
    target_include_directories(apriltag INTERFACE ${APRILTAG_INC})
    target_link_libraries(apriltag INTERFACE ${APRILTAG_LIB})
endif()


set(CMAKE_NO_SYSTEM_FROM_IMPORTED true)
include_directories(
    include
    ${realsense2_INCLUDE_DIR}
    ${catkin_INCLUDE_DIRS}
    )

# RealSense ROS Node
catkin_package(
    LIBRARIES ${PROJECT_NAME}
    CATKIN_DEPENDS message_runtime roscpp sensor_msgs std_msgs
    nav_msgs
    )

add_executable(rs-pose-apriltag 
    ${rs-pose-apriltag_sources}
)

add_dependencies(${PROJECT_NAME} ${catkin_EXPORTED_TARGETS})

target_include_directories(${PROJECT_NAME}
  PRIVATE ${realsense2_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME}
    ${realsense2_LIBRARY}
    ${catkin_LIBRARIES}
    )




