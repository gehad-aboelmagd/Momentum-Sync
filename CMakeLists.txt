cmake_minimum_required(VERSION 3.19)

project(LogManager LANGUAGES CXX)

find_package (vsomeip3 3.4.10 REQUIRED)

find_package( Boost 1.55 COMPONENTS system thread log REQUIRED )

include_directories (
    ${Boost_INCLUDE_DIR}
    ${VSOMEIP_INCLUDE_DIRS}
)

file(GLOB MY_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_executable(${PROJECT_NAME} main.cpp ${MY_SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc/)

target_link_libraries(${PROJECT_NAME} vsomeip3 ${Boost_LIBRARIES})
