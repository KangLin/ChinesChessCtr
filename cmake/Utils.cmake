include (CMakeParseArguments)

# 产生android平台分发设置
function(GENERATED_DEPLOYMENT_SETTINGS)
    cmake_parse_arguments(PARA "" "NAME;APPLACTION" "" ${ARGN})

    if(NOT ANDROID_NDK)
        set(ANDROID_NDK $ENV{ANDROID_NDK})
        if(NOT ANDROID_NDK)
            set(ANDROID_NDK ${ANDROID_NDK_ROOT})
            if(NOT ANDROID_NDK)
                set(ANDROID_NDK $ENV{ANDROID_NDK_ROOT})
            endif()
        endif()
    endif()

    if(NOT ANDROID_SDK)
        set(ANDROID_SDK $ENV{ANDROID_SDK})
        if(NOT ANDROID_SDK)
            set(ANDROID_SDK ${ANDROID_SDK_ROOT})
            if(NOT ANDROID_SDK)
                set(ANDROID_SDK $ENV{ANDROID_SDK_ROOT})
            endif()
        endif()
    endif()

    if(NOT DEFINED BUILD_TOOS_VERSION)
        set(BUILD_TOOS_VERSION $ENV{BUILD_TOOS_VERSION})
    endif()
    if(NOT DEFINED BUILD_TOOS_VERSION)
        set(BUILD_TOOS_VERSION "28.0.3")
    endif()
    
    if(DEFINED PARA_NAME)
        set(_file_name ${PARA_NAME})
        #message("file_name:${PARA_NAME}")
    else()
        SET(_file_name "${PROJECT_BINARY_DIR}/android-lib${PROJECT_NAME}.so-deployment-settings.json")
    endif()

    FILE(WRITE ${_file_name} "{\n")
    FILE(APPEND ${_file_name} "\"description\": \"This file is generated by qmake to be read by androiddeployqt and should not be modified by hand.\",\n")
    FILE(APPEND ${_file_name} "\"qt\":\"${QT_INSTALL_DIR}\",\n")
    FILE(APPEND ${_file_name} "\"sdk\":\"${ANDROID_SDK}\",\n")
    FILE(APPEND ${_file_name} "\"sdkBuildToolsRevision\":\"${BUILD_TOOS_VERSION}\",\n")
    FILE(APPEND ${_file_name} "\"ndk\":\"${ANDROID_NDK}\",\n")

    FILE(APPEND ${_file_name} "\"stdcpp-path\":\"${ANDROID_NDK}/sources/cxx-stl/llvm-libc++/libs/${ANDROID_ABI}/libc++_shared.so\",\n")
    FILE(APPEND ${_file_name} "\"useLLVM\":true,\n")
    FILE(APPEND ${_file_name} "\"toolchain-prefix\":\"llvm\",\n")
    FILE(APPEND ${_file_name} "\"tool-prefix\":\"llvm\",\n")

    IF(CMAKE_HOST_WIN32)
        IF(ANDROID_NDK_HOST_X64)
            FILE(APPEND ${_file_name} "\"ndk-host\":\"windows-x86_64\",\n")
        ELSE()
            FILE(APPEND ${_file_name} "\"ndk-host\":\"windows\",\n")
        ENDIF()
    ELSE()
        IF(ANDROID_NDK_HOST_X64)
            FILE(APPEND ${_file_name} "\"ndk-host\":\"linux-x86_64\",\n")
	ELSE()
	    FILE(APPEND ${_file_name} "\"ndk-host\":\"linux\",\n")
        ENDIF()
    ENDIF()
    FILE(APPEND ${_file_name} "\"target-architecture\":\"${CMAKE_ANDROID_ARCH_ABI}\",\n")
    FILE(APPEND ${_file_name} "\"android-package-source-directory\":\"${PROJECT_SOURCE_DIR}/android\",\n")
    IF(ANDROID_EXTRA_LIBS)
        FILE(APPEND ${_file_name} "\"android-extra-libs\":\"${ANDROID_EXTRA_LIBS}\",\n")
    ENDIF(ANDROID_EXTRA_LIBS)
    if(DEFINED PARA_APPLACTION)
        FILE(APPEND ${_file_name} "\"application-binary\":\"${PARA_APPLACTION}\"\n")
        #message("app_bin:${PARA_APPLACTION}")
    else()
        FILE(APPEND ${_file_name} "\"application-binary\":\"${CMAKE_BINARY_DIR}/bin/lib${PROJECT_NAME}.so\"\n")
    endif()
    FILE(APPEND ${_file_name} "}")
endfunction(GENERATED_DEPLOYMENT_SETTINGS)

# 得到子目录
macro(SUBDIRLIST result curdir)
    file(GLOB children RELATIVE ${curdir} ${curdir}/*)
    set(dirlist "")
    foreach(child ${children})
        if(IS_DIRECTORY ${curdir}/${child})
            LIST(APPEND dirlist ${child})
        endif()
    endforeach()
    set(${result} ${dirlist})
endmacro()

function(ADD_TARGET)
    cmake_parse_arguments(PARA "" "NAME;ISEXE;OUTPUT_DIR;INSTALL_DIR;VERSION" "SOURCES_FILES;HEADER_FILES;LIBS;INCLUDE_DIRS;DEFINITIONS" ${ARGN})
    if(NOT (DEFINED PARA_NAME
            AND DEFINED PARA_INSTALL_DIR
            AND DEFINED PARA_SOURCES_FILES
            ))
        message(FATAL_ERROR "Use:
            ADD_PLUG_TARGET
                NAME name
                [ISEXE TRUE/FALSE]
                SOURCES_FILES source1 [source2 ...] 
                [HEADER_FILES header1 [header2 ...]]
                [LIBS lib1 [lib2 ...]]
                [INCLUDE_DIRS [include_dir1 ...]]
                [DEFINITIONS [definition1 ...]]
                [OUTPUT_DIR output_dir]
                INSTALL_DIR install_dir
                [VERSION version]")
        return()
    endif()
    if(${PARA_ISEXE})
        add_executable(${PARA_NAME} ${PARA_SOURCES_FILES} ${PARA_HEADER_FILES})
    else()
        add_library(${PARA_NAME} ${PARA_SOURCES_FILES} ${PARA_HEADER_FILES})
    endif()

    if(DEFINED PARA_OUTPUT_DIR)
        set_target_properties(${PARA_NAME} PROPERTIES
            LIBRARY_OUTPUT_DIRECTORY ${PARA_OUTPUT_DIR}
            ARCHIVE_OUTPUT_DIRECTORY ${PARA_OUTPUT_DIR}
            RUNTIME_OUTPUT_DIRECTORY ${PARA_OUTPUT_DIR}
            )
    endif()
    if(DEFINED PARA_VERSION)
        set_target_properties(${PARA_NAME} PROPERTIES
            VERSION ${PARA_VERSION})
    endif()
    
    if(DEFINED PARA_LIBS)
        target_link_libraries(${PARA_NAME} PUBLIC ${PARA_LIBS})
    endif()
    
    if(DEFINED PARA_DEFINITIONS)
        target_compile_definitions(${PARA_NAME} PUBLIC ${PARA_DEFINITIONS})
    endif()
    
    if(DEFINED PARA_INCLUDE_DIRS)
        target_include_directories(${PARA_NAME}
            PRIVATE ${PARA_INCLUDE_DIRS})
    endif()
    
    # Install target
    INSTALL(TARGETS ${PARA_NAME}
        EXPORT ${PARA_NAME}Config
        RUNTIME DESTINATION "${PARA_INSTALL_DIR}"
            COMPONENT Runtime
        LIBRARY DESTINATION "${PARA_INSTALL_DIR}"
            COMPONENT Runtime
        ARCHIVE DESTINATION "${PARA_INSTALL_DIR}"
        )
    
    export(TARGETS ${PARA_NAME}
           APPEND FILE ${CMAKE_BINARY_DIR}/${PARA_NAME}Config.cmake
    )
    
    # Install cmake configure files
    install(EXPORT ${PARA_NAME}Config
            DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake"
            )

    if(DEFINED PARA_VERSION)
        write_basic_package_version_file(
            "${CMAKE_BINARY_DIR}/${PARA_NAME}ConfigVersion.cmake"
            VERSION ${PARA_VERSION}
            COMPATIBILITY AnyNewerVersion)
        install(FILES "${CMAKE_BINARY_DIR}/${PARA_NAME}ConfigVersion.cmake" DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake")
    endif()
endfunction()

function(ADD_PLUG_TARGET)
    cmake_parse_arguments(PARA "" "NAME;ISEXE;OUTPUT_DIR;INSTALL_DIR;VERSION" "SOURCES_FILES;HEADER_FILES;LIBS;INCLUDE_DIRS;DEFINITIONS" ${ARGN})
    ADD_TARGET(NAME ${PARA_NAME}
        ISEXE ${PARA_ISEXE}
        OUTPUT_DIR ${PARA_OUTPUT_DIR}
        INSTALL_DIR ${PARA_INSTALL_DIR}
        VERSION ${PARA_VERSION}
        SOURCES_FILES ${PARA_SOURCES_FILES}
        HEADER_FILES ${PARA_HEADER_FILES}
        LIBS FaceRecognizer RabbitCommon ${QT_LIBRARIES} ${PARA_LIBS}
        INCLUDE_DIRS ${RabbitCommon_DIR}/Src
            ${CMAKE_SOURCE_DIR}/Src
            ${CMAKE_BINARY_DIR}
            ${PARA_INCLUDE_DIRS}
        DEFINITIONS ${PARA_DEFINITIONS}
        )
endfunction()