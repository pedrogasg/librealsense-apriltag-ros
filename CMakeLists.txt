cmake_minimum_required(VERSION 2.8)
project(undistort)

find_package(
  catkin 
  REQUIRED 
  COMPONENTS 
  cv_bridge 
  image_transport
  message_generation
  sensor_msgs)

catkin_package(
  CATKIN_DEPENDS 
  LIBRARIES undistort
  cv_bridge 
  image_transport 
  message_runtime 
  sensor_msgs)

find_package(OpenCV)

include_directories(include ${catkin_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS})

file(GLOB undistort_sources src/*.cpp)

# add the publisher example
add_executable(undistort_node ${undistort_sources})

add_dependencies(
  undistort_node 
  ${catkin_EXPORTED_TARGETS}
  ${${PROJECT_NAME}_EXPORTED_TARGETS})
target_link_libraries(undistort_node ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})


# Mark executables and/or libraries for installation
install(TARGETS undistort_node
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
