cmake_minimum_required(VERSION 3.10)
project(test)
# gcc listViewVar.c -o listnew libucgui.a -IGUI_X -IGUI/Core -IGUI/Widget -IGUI/WM -lSDL
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -pthread ")
set(CMAKE_BUILD_TYPE "Release")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/../GUI/Core
	${CMAKE_CURRENT_SOURCE_DIR}/../GUI/Widget
	${CMAKE_CURRENT_SOURCE_DIR}/../GUI/WM
	${CMAKE_CURRENT_SOURCE_DIR}/../GUI_X
	)

link_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/..
	)

add_executable(listViewVar ${CMAKE_CURRENT_SOURCE_DIR}/listViewVar.c)
target_link_libraries(listViewVar libucgui.a SDL)
# target_include_directories(${PROJECT_NAME} PUBLIC )
