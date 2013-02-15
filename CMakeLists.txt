#
# SSG B748 PLUGIN
# Copyright (c) 2013 Péricles Lopes Machado <pericles.raskolnikoff@gmail.com>
#
# CMakeLists - CMake recipe
#

project(SSG_B748)

cmake_minimum_required(VERSION 2.6)

include_directories(.)
include_directories(./MAC)
include_directories(./MAC/XPLM.framework)
include_directories(./MAC/XPWidgets.framework)



#
# Compilling mode
#


if (ReleaseMode)
	message(STATUS "Compilling in release mode")
	add_definitions(-DDEBUGMODE=0)
else (ReleaseMode)
	message(STATUS "Compilling in debug mode")
	add_definitions(-DDEBUGMODE=1)
endif (ReleaseMode)


#
#Plugin general configuration
#
set(BUILD_SHARED_LIBS ON)


set(CMAKE_SHARED_LIBRARY_PREFIX "")
set(CMAKE_SHARED_LIBRARY_SUFFIX "")


#
#Plugin source code
#
set(
	XPLANE_SDK
	SDK/CHeaders/Wrappers/XPCBroadcaster.cpp
	SDK/CHeaders/Wrappers/XPCBroadcaster.h
	SDK/CHeaders/Wrappers/XPCDisplay.cpp
	SDK/CHeaders/Wrappers/XPCDisplay.h
	SDK/CHeaders/Wrappers/XPCListener.cpp
	SDK/CHeaders/Wrappers/XPCListener.h
	SDK/CHeaders/Wrappers/XPCProcessing.cpp
	SDK/CHeaders/Wrappers/XPCProcessing.h
	SDK/CHeaders/Wrappers/XPCWidgetAttachments.cpp
	SDK/CHeaders/Wrappers/XPCWidgetAttachments.h
	SDK/CHeaders/Wrappers/XPCWidget.cpp
	SDK/CHeaders/Wrappers/XPCWidget.h

	SDK/CHeaders/XPLM/XPLMCamera.h
	SDK/CHeaders/XPLM/XPLMDataAccess.h
	SDK/CHeaders/XPLM/XPLMDefs.h
	SDK/CHeaders/XPLM/XPLMDisplay.h
	SDK/CHeaders/XPLM/XPLMGraphics.h
	SDK/CHeaders/XPLM/XPLMMenus.h
	SDK/CHeaders/XPLM/XPLMNavigation.h
	SDK/CHeaders/XPLM/XPLMPlanes.h
	SDK/CHeaders/XPLM/XPLMPlugin.h
	SDK/CHeaders/XPLM/XPLMProcessing.h
	SDK/CHeaders/XPLM/XPLMScenery.h
	SDK/CHeaders/XPLM/XPLMUtilities.h

	SDK/CHeaders/Widgets/XPStandardWidgets.h
	SDK/CHeaders/Widgets/XPUIGraphics.h
	SDK/CHeaders/Widgets/XPWidgetDefs.h
	SDK/CHeaders/Widgets/XPWidgets.h
	SDK/CHeaders/Widgets/XPWidgetUtils.h
)


#
#Plugin flags
#
if(APPLE)

	add_definitions(-DIBM=0)
	add_definitions(-DAPL=1)
	add_definitions(-DLIN=0)


	set(CMAKE_CXX_FLAGS "-fvisibility=hidden  -arch i386")

	set(XPLANE_SDK
		${XPLANE_SDK}
		#"MAC/XPLM"
		#"MAC/XPWidgets"
		)
	set(PLUGIN_LIBS "")#GL GLU

elseif(MSVC)

	add_definitions(-DIBM=1)
	add_definitions(-DAPL=0)
	add_definitions(-DLIN=0)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)

	if(W64)
		set(PLUGIN_LIBS
		SDK/Libraries/Win/XPLM_64
		SDK/Libraries/Win/XPWidgets_64)

	else(W64)
		set(PLUGIN_LIBS
		SDK/Libraries/Win/XPLM
		SDK/Libraries/Win/XPWidgets)
	endif(W64)

elseif(UNIX)

	add_definitions(-DIBM=0)
	add_definitions(-DAPL=0)
	add_definitions(-DLIN=1)

	set(PLUGIN_SCRIPT "SSG_B748.names")
	set(CMAKE_CXX_FLAGS "-fvisibility=hidden -fPIC -O0 -Wall")
	set(CMAKE_SHARED_LINKER_FLAGS "-fvisibility=hidden -rdynamic -nodefaultlibs -undefined_warning -Wl,--version-script=${PLUGIN_SCRIPT}  -Wl,-soname,lin.xpl -L.")


	set(PLUGIN_LIBS GL GLU)

endif(APPLE)

include_directories("SDK/CHeaders/XPLM")
include_directories("SDK/CHeaders/Wrappers/")
include_directories("SDK/CHeaders/Widgets/")

set(PLUGIN_SRC
	${XPLANE_SDK}
	utils.cpp
	utils.h
	PluginData.cpp
	PluginData.h
	PluginManagement.cpp
	PluginManagement.h
	PluginCallBacks.cpp
	PluginCallBacks.h
	PluginEntry.cpp
	PluginEntry.h
	SSGB748.h
)

#
#Plugin compilation
#
if(APPLE)
	set(FRAMEWORK_DIR
		MAC/)
	add_library(mac.xpl
		SHARED
		${PLUGIN_SRC})

	find_library(CARBON NAMES Carbon)

	set_target_properties(mac.xpl PROPERTIES
		COMPILE_FLAGS "-F MAC/XPLM.framework -F MAC/XPWidgets.framework -bundle"
		LINK_FLAGS "-F MAC/XPLM.framework -framework XPLM  -F MAC/XPWidgets.framework -framework XPWidgets"
	)
	target_link_libraries(mac.xpl ${PLUGIN_LIBS} ${CARBON})

elseif(MSVC)
	add_library(win.xpl
		SHARED
		${PLUGIN_SRC}
	)
	target_link_libraries(win.xpl ${PLUGIN_LIBS})

elseif(UNIX)
	add_library(lin.xpl
		SHARED
		${PLUGIN_SRC}
	)
	target_link_libraries(lin.xpl ${PLUGIN_LIBS})

endif(APPLE)


#
#Configuration messages
#
message(STATUS "*******************************")
message(STATUS "SSG PLUGIN CMAKE SCRIPT")
message(STATUS "*******************************")

message(STATUS "-------------------------------")
message(STATUS "SETTINGS :")
message(STATUS "-------------------------------")

message(STATUS "LINKER FLAGS = ${CMAKE_CXX_FLAGS}")
message(STATUS "CXX FLAGS = ${CMAKE_SHARED_LINKER_FLAGS}")
message(STATUS "LIBS = ${PLUGIN_LIBS}")

message(STATUS "-------------------------------")
message(STATUS "OPTIONS :")
message(STATUS "-------------------------------")

message(STATUS "Use -DDebugMode=1 to enable debug messages")
message(STATUS "Use -DReleaseMode=1 to disable debug messages")

