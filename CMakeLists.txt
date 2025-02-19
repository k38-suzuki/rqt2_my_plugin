cmake_minimum_required(VERSION 3.8)
project(rqt2_mypkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(ament_cmake_ros REQUIRED)
find_package(pluginlib REQUIRED)
find_package(rqt_gui_cpp REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)

pluginlib_export_plugin_description_file(rqt_gui plugins.xml)

set(sources
  src/mainwindow.cpp
  src/my_plugin.cpp
  src/my_widget.cpp
)

set(headers
  include/rqt2_mypkg/mainwindow.hpp
  include/rqt2_mypkg/my_plugin.hpp
  include/rqt2_mypkg/my_widget.hpp
)

qt5_wrap_cpp(rqt2_mypkg_moc ${headers})

add_library(rqt2_mypkg ${sources} ${rqt2_mypkg_moc} ${headers})
target_link_libraries(rqt2_mypkg Qt5::Widgets)
target_compile_features(rqt2_mypkg PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17
target_include_directories(rqt2_mypkg PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
ament_target_dependencies(
  rqt2_mypkg
  "pluginlib"
  "rqt_gui_cpp"
  "rclcpp"
  "std_msgs"
)

# Causes the visibility macros to use dllexport rather than dllimport,
# which is appropriate when building the dll but not consuming it.
target_compile_definitions(rqt2_mypkg PRIVATE "RQT2_MYPKG_BUILDING_LIBRARY")

install(
  DIRECTORY include/
  DESTINATION include
)
install(
  TARGETS rqt2_mypkg
  EXPORT export_${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
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

ament_export_include_directories(
  include
)
ament_export_libraries(
  rqt2_mypkg
)
ament_export_targets(
  export_${PROJECT_NAME}
)

ament_package()
