cmake_minimum_required(VERSION 3.0.2)
project(lego_loam_pose_saver)

find_package(catkin REQUIRED COMPONENTS
  nav_msgs
  roscpp
  tf
)

catkin_package(
  CATKIN_DEPENDS roscpp nav_msgs tf
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

# 실행 파일 추가
add_executable(pose_saver src/pose_saver.cpp)
target_link_libraries(pose_saver ${catkin_LIBRARIES})
