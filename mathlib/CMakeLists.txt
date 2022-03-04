# 为库mathlib 添加源文件，该命令声明库文件
add_library(mathlib SHARED mathlib.cpp)

# 设置动态库的版本 为1.2
SET_TARGET_PROPERTIES(mathlib PROPERTIES VERSION 1.2 SOVERSION 1)

include_directories (${PROJECT_SOURCE_DIR}/log)

target_link_libraries(mathlib log)