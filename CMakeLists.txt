
cmake_minimum_required (VERSION 3.20)

project (JetpackJoyride)
#set (MY_AUTHORS "Lior_yakobovich-Shahar_hevrony_Aviv-erez")

if (MSVC AND CMAKE_VERSION VERSION_GREATER_EQUAL 3.21)
    set(CMAKE_CXX_STANDARD 23)
else ()
    set(CMAKE_CXX_STANDARD 20)
endif ()
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)
if (MSVC)
    add_compile_options (/W4 /permissive- /Zc:externConstexpr /Zc:inline /analyze)
endif ()


if(APPLE)

    add_executable (pacmanProject MACOSX_BUNDLE "")

    add_subdirectory (include)
    add_subdirectory (src)
    add_subdirectory (resources)
    add_subdirectory(external/box2d/src)

    set (SFML_STATIC_LIBRARIES FALSE)
    set (SFML_DIR "/usr/local/Cellar/sfml/2.5.1")

    find_package (SFML 2.5 COMPONENTS audio graphics REQUIRED)

    set_target_properties ( PROPERTIES MAP_IMPORTED_CONFIG_RELWITHDEBINFO RELEASE)
    target_link_libraries (pacmanProject sfml-graphics sfml-audio)

endif()


if(WIN32)

    add_executable (${CMAKE_PROJECT_NAME})

    add_subdirectory (include)
    add_subdirectory (src)
    add_subdirectory (resources)
    add_subdirectory(external/box2d/src)


    set (SFML_STATIC_LIBRARIES TRUE)
    set (SFML_DIR "C:/SFML/SFML-2.5.1/lib/cmake/SFML")

    find_package (SFML 2.5 COMPONENTS graphics audio REQUIRED)

    set_target_properties (sfml-main sfml-system sfml-window sfml-graphics sfml-audio sfml-network PROPERTIES MAP_IMPORTED_CONFIG_RELWITHDEBINFO RELEASE)

    target_link_libraries (${CMAKE_PROJECT_NAME} sfml-graphics sfml-main sfml-audio)
    target_link_libraries(${CMAKE_PROJECT_NAME} box2d)

    configure_file (C:/SFML/SFML-2.5.1/bin/openal32.dll ${CMAKE_BINARY_DIR} COPYONLY)

endif()
