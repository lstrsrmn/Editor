cmake_minimum_required(VERSION 3.16)
project(engine_editor)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_PREFIX_PATH "~/Qt/5.14.2/gcc_64/lib/cmake")

find_package(OpenCV REQUIRED)
find_package(ASSIMP REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets OpenGL)

set(PROJECT_UI qtui/Editor.ui qtui/Editor.cpp qtui/Editor.h)
set(WIDGETS widgets/GameGLView.h widgets/GameGLView.cpp widgets/SceneGLView.h widgets/SceneGLView.cpp)
#set(PROJECT_UI_H qtui/Editor.h qtui/GameGLView.h)
#set(PROJECT_UI_SRC qtui/Editor.cpp qtui/GameGLView.cpp)
#qt5_wrap_ui(PROJECT_HEADERS_WRAPPED ${PROJECT_UI})
#qt5_wrap_cpp(PROJECT_SOURCES_MOC ${PROJECT_UI_SRC})

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_executable(engine_editor ${WIDGETS} ${PROJECT_UI} main.cpp)

add_subdirectory(${PROJECT_SOURCE_DIR}/../game-engine-qt ${PROJECT_SOURCE_DIR}/../game-engine-qt/build)

include_directories(${PROJECT_SOURCE_DIR}/../game-engine-qt/include)

target_link_libraries(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/../game-engine-qt/build/libgame_engine.a
        GL ${OpenCV_LIBS} assimp
        Qt5::Core Qt5::Gui Qt5::Widgets Qt5::OpenGL)

include_directories(${PROJECT_NAME} glm ${OpenCV_INCLUDE_DIRS} ${ASSIMP_INCLUDE_DIR})