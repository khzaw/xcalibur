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

set(SOURCE
	SPA/Frontend/DesignExtractor.cpp
	SPA/Frontend/Lexeme.cpp
	SPA/Frontend/Lexer.cpp
	SPA/Frontend/Operator.cpp
	SPA/Frontend/Parser.cpp
	SPA/Frontend/TNode.cpp
	SPA/PKB/AST.cpp
	SPA/PKB/ConstantTable.cpp
	SPA/PKB/Follows.cpp
	SPA/PKB/FollowsRecord.cpp
	SPA/PKB/Modifies.cpp
	SPA/PKB/Parent.cpp
	SPA/PKB/ParentRecord.cpp
	SPA/PKB/PKB.cpp
	SPA/PKB/PKBController.cpp
	SPA/PKB/ProcTable.cpp
	SPA/PKB/StatementTable.cpp
	SPA/PKB/Uses.cpp
	SPA/PKB/VarTable.cpp
	)

add_library(spa STATIC ${SOURCE})

add_executable(impl
	impl/main.cpp
	)

target_link_libraries(impl spa)

add_executable(UnitTesting
	UnitTesting/source/testConstant.cpp
	UnitTesting/source/testFollows.cpp
	UnitTesting/source/TestModifies.cpp
	UnitTesting/source/testParent.cpp
	UnitTesting/source/TestParser.cpp
	UnitTesting/source/TestProcTable.cpp
	UnitTesting/source/testStatement.cpp
	UnitTesting/source/TestUses.cpp
	UnitTesting/source/TestVarTable.cpp
	UnitTesting/source/UnitTest.cpp
	UnitTesting/TestAST.cpp
	UnitTesting/TestAST.cpp
	UnitTesting/testConstant.cpp
	UnitTesting/testFollows.cpp
	UnitTesting/TestFollowsSubquery.cpp
	UnitTesting/TestModifies.cpp
	UnitTesting/testParent.cpp
	UnitTesting/TestParentSubquery.cpp
	UnitTesting/TestParser.cpp
	UnitTesting/TestProcTable.cpp
	UnitTesting/testQueryEvaluator.cpp
	UnitTesting/TestQueryParser.cpp
	UnitTesting/testStatement.cpp
	UnitTesting/TestUses.cpp
	UnitTesting/TestVarTable.cpp
	UnitTesting/UnitTest.cpp
	)

target_link_libraries(UnitTesting spa)

add_executable(IntegrationTesting
	IntegrationTesting/source/IntegrationTest.cpp
	)

target_link_libraries(IntegrationTesting spa)

add_executable(AutoTester
	AutoTester/source/TestWrapper.cpp
	)

target_link_libraries(AutoTester spa)

