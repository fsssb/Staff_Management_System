# 1. 规定 CMake 最低版本 
cmake_minimum_required(VERSION 3.10)

# 2. 项目名称 
project(Stuff_Management_System)

# 3. 设置 C++ 标准 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 4. 头文件
include_directories(include)

# 5. 自动搜索 src 目录下所有的 .cpp 文件
file(GLOB SRC_FILES "src/*.cpp")

# 6. 生成可执行文件
add_executable(sms_app ${SRC_FILES})