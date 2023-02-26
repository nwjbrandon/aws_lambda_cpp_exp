cmake_minimum_required(VERSION 3.5)
#set(CMAKE_CXX_STANDARD 11)
set(
    CMAKE_PREFIX_PATH
    ~/libtorch
    ~/lambda-install
)

project(api LANGUAGES CXX)

find_package(aws-lambda-runtime REQUIRED)
find_package(OpenCV REQUIRED )

find_package(AWSSDK COMPONENTS core)
find_path(DMTX_INCLUDE_DIRS dmtx.h)
find_library(DMTX_LIBRARIES NAMES bdmtx libdmtx libdmtx.so PATHS /usr/lib)

find_package(Torch REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

find_package(NumCpp 2.6.2 REQUIRED)

if(${DMTX_LIBRARIES} STREQUAL DMTX_LIBRARIES-NOTFOUND)
    message(FATAL_ERROR "Libdmtx not installed, please install the dmtx lib using: sudo apt-get install libdmtx-dev")
endif()



include_directories(
  ${DMTX_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME} "main.cpp")
target_link_libraries(
    ${PROJECT_NAME} 
    PUBLIC 
    AWS::aws-lambda-runtime 
    ${AWSSDK_LINK_LIBRARIES} 
    ${DMTX_LIBRARIES}
    ${TORCH_LIBRARIES}
    NumCpp::NumCpp
)

aws_lambda_package_target(${PROJECT_NAME})
