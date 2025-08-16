cmake_minimum_required(VERSION 3.10)
project(test)
# gcc listViewVar.c -o listnew libucgui.a -IGUI_X -IGUI/Core -IGUI/Widget -IGUI/WM -lSDL
set(CMAKE_C_FLAGS " -Wall -pthread -DUSE_SDL")
set(CMAKE_BUILD_TYPE "Debug")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/GUI/Core
	${CMAKE_CURRENT_SOURCE_DIR}/GUI/AntiAlias
	${CMAKE_CURRENT_SOURCE_DIR}/GUI/ConvertColor
	${CMAKE_CURRENT_SOURCE_DIR}/GUI/Widget
	${CMAKE_CURRENT_SOURCE_DIR}/GUI/WM
	${CMAKE_CURRENT_SOURCE_DIR}/GUI_X
	/usr/include/SDL
	)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/GUI/Core UCGUI_SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/GUI/ConvertColor UCGUI_SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/GUI/AntiAlias UCGUI_SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/GUI/ConvertMono UCGUI_SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/GUI/Font UCGUI_SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/GUI/GIF UCGUI_SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/GUI/JPEG UCGUI_SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/GUI/MemDev UCGUI_SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/GUI/MultiLayer UCGUI_SRC)
	
	
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/GUI/Widget UCGUI_SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/GUI/WM UCGUI_SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/GUI_X UCGUI_SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/GUI_X/font UCGUI_SRC)

link_directories(
	# ${CMAKE_CURRENT_SOURCE_DIR}/..
	${CMAKE_CURRENT_SOURCE_DIR}/build
	)

add_library(ucgui STATIC ${UCGUI_SRC})
add_executable(listViewVar ${CMAKE_CURRENT_SOURCE_DIR}/test/listViewVar.c ${UCGUI_SRC})
# target_link_libraries(listViewVar libucgui.a SDL)
target_link_libraries(listViewVar m  SDL)

# add_executable(listViewVarNew ${CMAKE_CURRENT_SOURCE_DIR}/listViewVarNew.c)
# target_link_libraries(listViewVarNew libucgui.a SDL)
# target_include_directories(${PROJECT_NAME} PUBLIC )
