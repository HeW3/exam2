cmake_minimum_required(VERSION 3.10)
project(custom)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(cus_msg REQUIRED)
find_package(geometry_msgs REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)


add_executable(custom_pub src/cus_pub.cpp)
target_link_libraries(custom_pub PUBLIC
  rclcpp::rclcpp
  ${cus_msg_TARGETS}
)


add_executable(exam src/exam.cpp)

target_link_libraries(exam PUBLIC
  rclcpp::rclcpp
  ${cus_msg_TARGETS}
  ${geometry_msgs_TARGETS}
)

install(TARGETS
  custom_pub
  exam
  DESTINATION lib/${PROJECT_NAME}
)

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
