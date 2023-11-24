cmake_minimum_required(VERSION 3.26)

project(EncryptionTool)

set(CMAKE_CXX_STANDARD 20)

# Find Boost libraries - specifically the Program Options component
find_package(Boost 1.65 REQUIRED COMPONENTS program_options)

# Include directories for Crypto++ and Boost
include_directories(/usr/include/crypto++)
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/include)
# Google Test integration
add_subdirectory(googletest)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# Add your main executable
add_executable(EncryptionTool src/main.cpp src/Encryption.cpp include/Encryption.h)

# Add your test executable
add_executable(EncryptionDecryptionTests tests/EncryptionDecryptionTests.cpp src/Encryption.cpp include/Encryption.h)
target_link_libraries(EncryptionDecryptionTests gtest gtest_main)

# Link directories - if Crypto++ is installed in a non-standard directory
# Otherwise, this line can be omitted
link_directories(/usr/lib)

# Link both Boost and Crypto++ libraries to your main executable
target_link_libraries(EncryptionTool ${Boost_LIBRARIES} cryptopp)

# Link Google Test to your test executable
target_link_libraries(EncryptionDecryptionTests gtest gtest_main cryptopp)