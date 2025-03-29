set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # Generate compile_commands.json (optional)

include(FetchContent)

# Fetch cpp-dump
FetchContent_Declare(cpp-dump
    GIT_REPOSITORY https://github.com/philip82148/cpp-dump
    GIT_TAG main
)
FetchContent_MakeAvailable(cpp-dump)

add_executable(MemTreeVisualizer
	main.cpp
)

target_include_directories(MemTreeVisualizer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(MemTreeVisualizer cpp-dump)
