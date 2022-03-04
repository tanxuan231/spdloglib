message(STATUS "========= build capture base start =========")

cmake_minimum_required(VERSION 3.10)

project(demoSDK VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS NO)

# 提供一个选项是OFF或者ON，如果没有初始值被提供则默认使用OFF
option(USE_MYMATH "Use tutorial provided math implementation" ON)

configure_file(include/TutorialConfig.h.in TutorialConfig.h)

if(USE_MYMATH)
  add_subdirectory(mathlib)

  # 列出mathlib库的所有项目，并添加到外部库变量EXTRA_LIBS中
  list(APPEND EXTRA_LIBS mathlib)

  # 将子路径"${PROJECT_SOURCE_DIR}/mathlib"添加到外部路径变量EXTRA_INCLUDES中
  list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/mathlib")
endif()

option(USE_LOG "Use tutorial provided log implementation" ON)
if(USE_LOG)
    message("use log as lib hh")
    add_subdirectory(log)
    list(APPEND EXTRA_LIBS log)
    list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/log")

    add_executable(demoSDK main.cpp)
else()
    message("use log as cpp hh")
    include_directories (${CMAKE_CURRENT_SOURCE_DIR}/log/spdlog/include)
    include_directories (${CMAKE_CURRENT_SOURCE_DIR}/log)
    add_executable(demoSDK main.cpp log/log.cpp log/log.h)
endif()

# 对目标的外部库进行链接操作
target_link_libraries(demoSDK PUBLIC ${EXTRA_LIBS})

# 为指定项目添加 include 路径
target_include_directories(demoSDK PUBLIC
                        "${PROJECT_BINARY_DIR}"
                        ${EXTRA_INCLUDES})