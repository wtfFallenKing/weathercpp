add_library(WeatherLib Weather.cpp)
target_link_libraries(WeatherLib cpr)
target_include_directories(WeatherLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)
