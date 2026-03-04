cmake_minimum_required(VERSION 3.19)

project(Service LANGUAGES CXX)

find_package (vsomeip3 3.4.10 REQUIRED)

find_package( Boost 1.55 COMPONENTS system thread log REQUIRED )

include_directories (
    ${Boost_INCLUDE_DIR}
    ${VSOMEIP_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME} SomeIPServer.cpp)

target_link_libraries(${PROJECT_NAME} vsomeip3 ${Boost_LIBRARIES})
