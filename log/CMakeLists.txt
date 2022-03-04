message(STATUS "========= build log start =========")

set(log_HEADERS
    log.h
    ${PROJECT_SOURCE_DIR}/include/singleton.h)

set(log_SOURCES
    log.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/spdlog/include)

add_subdirectory(spdlog)

add_library(log SHARED
	${log_SOURCES}
	${log_HEADERS})