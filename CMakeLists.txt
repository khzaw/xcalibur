cmake_minimum_required (VERSION 2.6)

# Maps to a solution file (XCalibur.sln).
# This solution will have all targets (exe, lib, dll) as projects (.vcproj)
project (XCalibur)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_BUILD_TYPE Debug)

if(UNIX)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x -pthread")
endif()

include_directories("${PROJECT_SOURCE_DIR}")





file(GLOB SPA_FRONTEND_SOURCES
	"SPA/Frontend/*.h"
	"SPA/Frontend/*.cpp"
	)

file(GLOB SPA_PKB_SOURCES
	"SPA/PKB/*.h"
	"SPA/PKB/*.cpp"
	)

file(GLOB SPA_QUERYPROCESSOR_SOURCES
	"SPA/QueryProcessor/*.h"
	"SPA/QueryProcessor/*.cpp"
	)
# Create named folders for the sources within the .vcproj
source_group ("Frontend" FILES ${SPA_FRONTEND_SOURCES})
source_group ("PKB" FILES ${SPA_PKB_SOURCES})
source_group ("QueryProcessor" FILES ${SPA_QUERYPROCESSOR_SOURCES})
add_library(SPA STATIC ${SPA_FRONTEND_SOURCES} ${SPA_PKB_SOURCES} ${SPA_QUERYPROCESSOR_SOURCES})




add_executable(impl
	impl/main.cpp
	)
target_link_libraries(impl SPA)





file(GLOB UNITTESTING_SOURCES
	"UnitTesting/*.cpp"
	"UnitTesting/*.h"
	)

file(GLOB UNITTESTING_SUB_SOURCES
	"UnitTesting/source/*.cpp"
	"UnitTesting/source/*.h"
	)
source_group("" FILES ${UNITTESTING_SOURCES})
source_group("source" FILES ${UNITTESTING_SUB_SOURCES})
add_executable(UnitTesting ${UNITTESTING_SOURCES} ${UNITTESTING_SUB_SOURCES})
target_link_libraries(UnitTesting SPA)


file(GLOB INTEGRATIONTESTING_SOURCES
	"IntegrationTesting/source/*.cpp"
	"IntegrationTesting/source/*.h"
	)
source_group("source" FILES ${INTEGRATIONTESTING_SOURCES})
add_executable(IntegrationTesting ${INTEGRATIONTESTING_SOURCES})
target_link_libraries(IntegrationTesting SPA)


file(GLOB AUTOTESTER_SOURCES
	"AutoTester/source/*.cpp"
	"AutoTester/source/*.h"
	)
source_group("source" FILES ${AUTOTESTER_SOURCES})
add_executable(AutoTester ${AUTOTESTER_SOURCES})
target_link_libraries(AutoTester SPA)

