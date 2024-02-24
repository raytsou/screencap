cmake_minimum_required(VERSION 3.8)
project(screencap)

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(image_transport REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(OpenCV 4 REQUIRED)
find_package(X11 REQUIRED)
find_package(screencap REQUIRED)

include_directories(include)
include_directories(SYSTEM ${X11_INCLUDE_DIR})
include_directories ("/usr/include/opencv4/")

# find_package(Boost REQUIRED COMPONENTS system)

link_libraries(${X11_LIBRARIES})

add_library(screencap src/screencap.cpp)

# find_package(screencap REQUIRED)
# link_libraries(screencap)
# include_directories(screencap)

# ament_target_dependencies(screencap
#                           ${THIS_PACKAGE_INCLUDE_DEPENDS})

add_executable(screencap_node src/screencap_node.cpp)

target_include_directories(screencap_node PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
target_compile_features(screencap_node PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17
ament_target_dependencies(
  screencap_node
  "cv_bridge"
  "rclcpp"
  "OpenCV"
  "std_msgs"
  "image_transport"
  # screencap
)
# ament_target_dependencies(screencap PRIVATE screencap)

# ament_export_include_directories(include)
# ament_export_libraries(screencap)
# ament_export_dependencies(cv_bridge roscpp std_msgs system_lib)
# ament_package()




install(TARGETS screencap_node
  DESTINATION lib/${PROJECT_NAME})


if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
