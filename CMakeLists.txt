cmake_minimum_required(VERSION 3.26)

project(EncryptionTool)

set(CMAKE_CXX_STANDARD 20)

# Find Boost libraries - specifically the Program Options component
find_package(Boost 1.65 REQUIRED COMPONENTS program_options)

# Include directories for Crypto++
include_directories(/usr/include/crypto++)
include_directories(${Boost_INCLUDE_DIRS})

# Add your executable
add_executable(EncryptionTool src/main.cpp src/Encryption.cpp include/Encryption.h)

# Link directories - if Crypto++ is installed in a non-standard directory
# Otherwise, this line can be omitted
link_directories(/usr/lib)

# Link both Boost and Crypto++ libraries to your executable
target_link_libraries(EncryptionTool ${Boost_LIBRARIES} cryptopp)