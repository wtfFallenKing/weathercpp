# cmake_minimum_required(VERSION 3.8)
# project(Main)

# set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" ${CMAKE_SOURCE_DIR}/cmake)

# find_package(Threads REQUIRED)

# set(CMAKE_CXX_STANDARD 17)

# include(FetchContent)

# FetchContent_Declare(
# 	cpr_repo
# 	GIT_REPOSITORY https://github.com/libcpr/cpr.git
#     GIT_TAG 11e5954
# )

# FetchContent_MakeAvailable(cpr_repo)

# include_directories(${CPR_INCLUDE_DIRS})

# include_directories(include)

# add_subdirectory(src)
# add_executable(main main.cpp)
cmake_minimum_required(VERSION 3.10)
project(main-project)

add_subdirectory(src)

include(FetchContent)
FetchContent_Declare(
	cpr_repo
	GIT_REPOSITORY https://github.com/libcpr/cpr.git
    GIT_TAG 11e5954
)
FetchContent_MakeAvailable(cpr_repo)
include_directories(${CPR_INCLUDE_DIRS})
add_executable(Exec main.cpp)
target_link_libraries(Exec WeatherLib)
