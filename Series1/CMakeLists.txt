# 1. 声明 CMake 的最低版本要求
cmake_minimum_required(VERSION 3.10)

# 2. 项目名称（随便起，比如 MyPPM）
project(RTIW_Chap1)

# 3. 指定 C++ 标准（建议至少 C++11，PPM 写入常用）
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 4. 生成可执行文件
# 第一个参数是生成程序的名称（比如 ppm_gen）
# 第二个参数是你的源代码文件名
add_executable(ppm_gen main.cc)
