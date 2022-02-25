project(DBBase)

cmake_minimum_required(VERSION 3.12)

find_package(Qt5 COMPONENTS Core Sql REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)
file(GLOB INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp)
file(GLOB MAIN_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/app/main.cpp)

qt5_wrap_cpp(WRAPPED_HEADERS ${INCLUDE})

add_library(DBBase ${SOURCE} ${INCLUDE} ${WRAPPED_HEADERS})
target_link_libraries(DBBase Qt5::Core Qt5::Sql)

add_executable(DBTest ${MAIN_SOURCE})
target_link_libraries(DBTest DBBase)
