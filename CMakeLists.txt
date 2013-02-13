#
# SSG B748 PLUGIN
# Copyright (c) 2013 Péricles Lopes Machado <pericles.raskolnikoff@gmail.com>
#
# CMakeLists - CMake recipe
#

project(SSG_B748)

cmake_minimum_required(VERSION 2.6)
include_directories(.)

#
#Plugin general configuration
#
set(BUILD_SHARED_LIBS ON)


set(CMAKE_SHARED_LIBRARY_PREFIX "")
set(CMAKE_SHARED_LIBRARY_SUFFIX "")


#
#Plugin flags
#
if(APPLE)

	add_definitions(-DIBM=0)
	add_definitions(-DAPL=1)
	add_definitions(-DLIN=0)


	set(CMAKE_CXX_FLAGS "-fvisibility=hidden -shared")
	set(CMAKE_SHARED_LINKER_FLAGS "-dynamiclib  suppress")

	set(PLUGIN_LIBS GL GLU)

elseif(MSVC)

	add_definitions(-DIBM=1)
	add_definitions(-DAPL=0)
	add_definitions(-DLIN=0)

	if(W64)
		set(PLUGIN_LIBS
		"../SDK/Libraries/Win/XPLM_64.lib"
		"../SDK/Libraries/Win/XPWidgets_64.lib")

	else(W64)
		set(PLUGIN_LIBS
		"../SDK/Libraries/Win/XPLM.lib"
		"../SDK/Libraries/Win/XPWidgets.lib")

	endif(W64)

elseif(UNIX)

	add_definitions(-DIBM=0)
	add_definitions(-DAPL=0)
	add_definitions(-DLIN=1)

	set(PLUGIN_SCRIPT "SSG_B748.names")
	set(CMAKE_CXX_FLAGS "-fvisibility=hidden -fPIC -O0 -shared -Wall")
	set(CMAKE_SHARED_LINKER_FLAGS "-fvisibility=hidden -shared -rdynamic -nodefaultlibs -undefined_warning -Wl,--version-script=${PLUGIN_SCRIPT}  -Wl,-soname,lin.xpl")

	set(PLUGIN_LIBS GL GLU)

endif(APPLE)

include_directories("../SDK/CHeaders/XPLM")
include_directories("../SDK/CHeaders/Wrappers/")
include_directories("../SDK/CHeaders/Widgets/")

#
#Plugin source code
#
set(
	XPLANE_SDK
	../SDK/CHeaders/Wrappers/XPCBroadcaster.cpp
	../SDK/CHeaders/Wrappers/XPCBroadcaster.h
	../SDK/CHeaders/Wrappers/XPCDisplay.cpp
	../SDK/CHeaders/Wrappers/XPCDisplay.h
	../SDK/CHeaders/Wrappers/XPCListener.cpp
	../SDK/CHeaders/Wrappers/XPCListener.h
	../SDK/CHeaders/Wrappers/XPCProcessing.cpp
	../SDK/CHeaders/Wrappers/XPCProcessing.h
	../SDK/CHeaders/Wrappers/XPCWidgetAttachments.cpp
	../SDK/CHeaders/Wrappers/XPCWidgetAttachments.h
	../SDK/CHeaders/Wrappers/XPCWidget.cpp
	../SDK/CHeaders/Wrappers/XPCWidget.h

	../SDK/CHeaders/XPLM/XPLMCamera.h
	../SDK/CHeaders/XPLM/XPLMDataAccess.h
	../SDK/CHeaders/XPLM/XPLMDefs.h
	../SDK/CHeaders/XPLM/XPLMDisplay.h
	../SDK/CHeaders/XPLM/XPLMGraphics.h
	../SDK/CHeaders/XPLM/XPLMMenus.h
	../SDK/CHeaders/XPLM/XPLMNavigation.h
	../SDK/CHeaders/XPLM/XPLMPlanes.h
	../SDK/CHeaders/XPLM/XPLMPlugin.h
	../SDK/CHeaders/XPLM/XPLMProcessing.h
	../SDK/CHeaders/XPLM/XPLMScenery.h
	../SDK/CHeaders/XPLM/XPLMUtilities.h

	../SDK/CHeaders/Widgets/XPStandardWidgets.h
	../SDK/CHeaders/Widgets/XPUIGraphics.h
	../SDK/CHeaders/Widgets/XPWidgetDefs.h
	../SDK/CHeaders/Widgets/XPWidgets.h
	../SDK/CHeaders/Widgets/XPWidgetUtils.h
)

set(PLUGIN_SRC
	${XPLANE_SDK}
	utils.cpp
	utils.h
	PluginData.cpp
	PluginData.h
	PluginDataRef.cpp
	PluginDataRef.h
	PluginCallBacks.cpp
	PluginCallBacks.h
	fmc.cpp
	fmc.h
	SSGB748.h
)


#
#Plugin compilation
#
if(APPLE)
	add_library(mac.xpl
		SHARED
		${PLUGIN_SRC}
	)
	target_link_libraries(mac.xpl ${PLUGIN_LIBS})

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
message(STATUS "LINKER FLAGS = ${CMAKE_CXX_FLAGS}")
message(STATUS "CXX FLAGS = ${CMAKE_SHARED_LINKER_FLAGS}")
