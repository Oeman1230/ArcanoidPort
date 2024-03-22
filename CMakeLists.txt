
cmake_minimum_required(VERSION 3.29)

set(PROJ_NAME ArcanoidPortProject)
set(EXEC_NAME ArcanoidPort)

project(PROJ_NAME)

set(CUR_DIR_PATH ${CMAKE_CURRENT_SOURCE_DIR})
set(OESDL_MODULE_PATH ${CUR_DIR_PATH}/src/OESDL_Module)
set(SDL_LIB_PATH ${CUR_DIR_PATH}/src/OESDL_Module/SDL_Include)

set(SOURCE_FILES    
                    ${OESDL_MODULE_PATH}/OESDL_Module.cpp
                    ${OESDL_MODULE_PATH}/OETexture.cpp)

set(OEFRAMES_SRC    
                    ${CUR_DIR_PATH}/src/OEFrames/OEWindow.cpp
                    ${CUR_DIR_PATH}/src/OEFrames/OEFrame.cpp
                    ${CUR_DIR_PATH}/src/OEFrames/OELabel.cpp
                    ${CUR_DIR_PATH}/src/OEFrames/BaseWindowObj.cpp
                    ${CUR_DIR_PATH}/src/OEFrames/OEFrameWrapper.cpp
                    ${CUR_DIR_PATH}/src/OEFrames/OELabelWrapper.cpp
                    ${CUR_DIR_PATH}/src/OEFrames/OEButton.cpp
                    ${CUR_DIR_PATH}/src/OEFrames/OEFigures/WindowLine.cpp
                    ${CUR_DIR_PATH}/src/OEFrames/OEFigures/WinObjBorder.cpp)

set(ARCANOID_SRC    ${CUR_DIR_PATH}/src/Main.cpp
                    ${CUR_DIR_PATH}/src/Arcanoid.cpp
                    ${CUR_DIR_PATH}/src/Hitbox.cpp
                    )

include_directories(${SDL_LIB_PATH}/include)
include_directories(${CUR_DIR_PATH}/src/OEFrames)
include_directories(${OESDL_MODULE_PATH})
include_directories(${CUR_DIR_PATH}/src/SDL2_gfx_files/Include)



add_executable(${EXEC_NAME} ${ARCANOID_SRC} ${OEFRAMES_SRC} ${SOURCE_FILES})


target_link_libraries(${EXEC_NAME}  ${SDL_LIB_PATH}/lib/x64/SDL2main.lib
                                    ${SDL_LIB_PATH}/lib/x64/SDL2.lib
                                    ${SDL_LIB_PATH}/lib/x64/SDL2_image.lib
                                    ${SDL_LIB_PATH}/lib/x64/SDL2_ttf.lib )


target_link_libraries(${EXEC_NAME} ${CUR_DIR_PATH}/src/SDL2_gfx_lib/SDL2_gfx.lib)
