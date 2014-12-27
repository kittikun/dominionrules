cmake_minimum_required(VERSION 2.6)

project(server)
set(CMAKE_MODULE_PATH   ${PROJECT_SOURCE_DIR})
set(ROOT_PATH           ${PROJECT_SOURCE_DIR}/../../)
set(SRC_PATH            ${ROOT_PATH}/src)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${ROOT_PATH}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${ROOT_PATH}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${ROOT_PATH}/bin)

find_package(Boost COMPONENTS chrono system filesystem log thread unit_test_framework REQUIRED)
find_package(SQLite3 REQUIRED)

if (Boost_FOUND AND SQLITE3_FOUND)
  add_definitions(-DBOOST_ALL_DYN_LINK -DDOMINION_DATAGEN -DSQLITE_THREADSAFE)

  set(DOMINION_PATH       ${SRC_PATH}/dominion)
  set(TEST_PATH           ${SRC_PATH}/unittest)
  set(EXE_PATH            ${SRC_PATH}/server)
  include_directories(${Boost_INCLUDE_DIRS}
	              ${SQLITE3_INCLUDE_DIR}
                      ${SRC_PATH}
                      ${SRC_PATH}/lib)

  set(DOMINION_SRC  ${DOMINION_PATH}/api.cpp
                    ${DOMINION_PATH}/database.cpp
                    ${DOMINION_PATH}/dice.cpp
                    ${DOMINION_PATH}/character/attributes.cpp
                    ${DOMINION_PATH}/character/character.cpp
                    ${DOMINION_PATH}/character/character_utility.cpp
                    ${DOMINION_PATH}/character/perk.cpp
                    ${DOMINION_PATH}/character/skill.cpp
                    ${DOMINION_PATH}/character/style.cpp
                    ${DOMINION_PATH}/impl/api_impl.cpp
                    ${DOMINION_PATH}/impl/character_impl.cpp
                    ${DOMINION_PATH}/impl/character_utility_impl.cpp
                    ${DOMINION_PATH}/impl/database_impl.cpp
                    ${DOMINION_PATH}/impl/dice_impl.cpp
                    ${DOMINION_PATH}/impl/perk_impl.cpp
                    ${DOMINION_PATH}/impl/skill_impl.cpp
                    ${DOMINION_PATH}/impl/skill_template.cpp
                    ${DOMINION_PATH}/impl/style_impl.cpp)
  add_library(dominion SHARED ${DOMINION_SRC})

  set(TEST_SRC  ${TEST_PATH}/main.cpp
                ${TEST_PATH}/dominion/api.cpp
                ${TEST_PATH}/dominion/attributes.cpp
                ${TEST_PATH}/dominion/character.cpp
                ${TEST_PATH}/dominion/database.cpp
                ${TEST_PATH}/dominion/dice.cpp
                ${TEST_PATH}/dominion/perk.cpp
                ${TEST_PATH}/dominion/skill.cpp
                ${TEST_PATH}/lib/minicsv.cpp)
  add_executable(unittest ${TEST_SRC})
  target_link_libraries(unittest dominion ${Boost_LIBRARIES} ${SQLITE3_LIBRARY})

endif(Boost_FOUND AND SQLITE3_FOUND)

