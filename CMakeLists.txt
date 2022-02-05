cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(CameraGuiPlugin)
if(POLICY CMP0100)
	  cmake_policy(SET CMP0100 NEW)
endif()

  set (CMAKE_AUTOMOC ON)

  find_package (Qt5Widgets REQUIRED)
  find_package (Qt5Core REQUIRED)
  find_package(Protobuf REQUIRED)
  find_package(gazebo REQUIRED)
  find_package(OpenCV REQUIRED)

  include_directories(${OpenCV_INCLUDE_DIRS} )
  include_directories(SYSTEM ${GAZEBO_INCLUDE_DIRS} ${Qt5Core_INCLUDE_DIRS})
  link_directories(${GAZEBO_LIBRARY_DIRS})
  
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GAZEBO_CXX_FLAGS}")

  add_library(camera_gui_plugin SHARED ${headers_MOC} CameraGuiPlugin.cc)

  target_link_libraries(camera_gui_plugin 
	  	pthread
	  	${OpenCV_LIBS}
	  	${GAZEBO_LIBRARIES}
	        ${OGRE_LIBRARIES}
		${OGRE-Terrain_LIBRARIES}
	        ${Qt5Core_LIBRARIES}
		${Qt5Widgets_LIBRARIES}
	        ${PROTOBUF_LIBRARIES})
