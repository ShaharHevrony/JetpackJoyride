file (GLOB MY_SOURCE_FILES CONFIGURE_DEPENDS LIST_DIRECTORIES false RELATIVE ${CMAKE_CURRENT_LIST_DIR} *.cpp)
target_sources (${CMAKE_PROJECT_NAME} PRIVATE ${MY_SOURCE_FILES})

add_subdirectory(Objects)
add_subdirectory(Events)
add_subdirectory(Menu)
add_subdirectory(Managers)
add_subdirectory(PlayGame)