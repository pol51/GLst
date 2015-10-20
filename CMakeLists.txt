cmake_minimum_required(VERSION 3.0.0)

project(glst)

# Build Type
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release
    CACHE STRING "Choose the type of build, options are: None Debug Release(*) RelWithDebInfo MinSizeRel."
    FORCE)
endif()

# Build flags
if(CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11")
endif()

# Qt5
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)

# QRC - Images
file(GLOB_RECURSE glst_images resources/images/*)
set(gslt_images_qrc ${CMAKE_CURRENT_BINARY_DIR}/images.qrc)
file(WRITE ${gslt_images_qrc} "<RCC>\n    <qresource prefix=\"/images\">\n")
foreach(image_file ${glst_images})
  file(RELATIVE_PATH image_file_relative_path ${CMAKE_CURRENT_BINARY_DIR} ${image_file})
  file(RELATIVE_PATH image_file_short_name ${CMAKE_SOURCE_DIR}/resources/images ${image_file})
  file(APPEND ${gslt_images_qrc} "        <file alias=\"${image_file_short_name}\">${image_file_relative_path}</file>\n")
endforeach()
file(APPEND ${gslt_images_qrc} "    </qresource>\n</RCC>")

# Build
file(GLOB_RECURSE glst_src src/*.cpp src/*.h)
file(GLOB_RECURSE glst_ui src/ui/*.ui)
include_directories(AFTER SYSTEM src ${CMAKE_BINARY_DIR})

qt5_add_resources(glst_rcc ${gslt_images_qrc})

add_executable(${PROJECT_NAME} ${glst_src} ${glst_moc} ${glst_rcc} ${gslt_images_qrc} ${glst_images} ${glst_ui} ${glst_uic})
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui Qt5::Widgets)
