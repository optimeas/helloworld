project(helloworld LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(HEADERS
)

set(SOURCES
    main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME}
    Qt${QT_VERSION_MAJOR}::Core
    cmake-git-version-tracking
    g3log
)
install(TARGETS ${PROJECT_NAME} DESTINATION .)
