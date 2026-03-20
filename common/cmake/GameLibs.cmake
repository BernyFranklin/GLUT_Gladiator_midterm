if(NOT DEFINED COMMON_ROOT)
    message(FATAL_ERROR "COMMON_ROOT is not defined. Set it before including GameLibs.cmake")
endif()

set(COMMON_INCLUDE_DIR "${COMMON_ROOT}/include")
set(COMMON_LIB_DIR "${COMMON_ROOT}/lib")
set(COMMON_BIN_DIR "${COMMON_ROOT}/bin")

function(setup_game_target TARGET_NAME)

    target_include_directories(${TARGET_NAME} PRIVATE
        "${COMMON_INCLUDE_DIR}"
        "${COMMON_INCLUDE_DIR}/SNDS"
        "C:/msys64/mingw64/include"
    )

    target_link_directories(${TARGET_NAME} PRIVATE
        "C:/msys64/mingw64/lib"
    )

    find_package(OpenGL REQUIRED)

    unset(SOIL_LIB CACHE)
    find_library(SOIL_LIB
        NAMES SOIL Soil soil SOIL2 soil2
        PATHS
            "C:/msys64/mingw64/lib"
            "/mingw64/lib"
            "${COMMON_LIB_DIR}"
    )

    if(NOT SOIL_LIB)
        message(FATAL_ERROR "SOIL/SOIL2 library not found.")
    endif()

    unset(GLEW_LIBRARY CACHE)
    unset(GLEW_INCLUDE_DIR CACHE)
    find_package(GLEW QUIET)

    if(GLEW_FOUND)
        if(TARGET GLEW::GLEW)
            target_link_libraries(${TARGET_NAME} PRIVATE GLEW::GLEW)
        else()
            target_include_directories(${TARGET_NAME} PRIVATE ${GLEW_INCLUDE_DIRS})
            target_link_libraries(${TARGET_NAME} PRIVATE ${GLEW_LIBRARIES})
        endif()
    else()
        find_path(GLEW_INCLUDE_DIR
            NAMES GL/glew.h
            PATHS
                "${COMMON_INCLUDE_DIR}"
                "C:/msys64/mingw64/include"
        )

        find_library(GLEW_LIBRARY
            NAMES libglew32.dll.a glew32s glew32 libglew32.a glew libglew.a
            PATHS
                "C:/msys64/mingw64/lib"
                "${COMMON_LIB_DIR}"
        )

        if(GLEW_INCLUDE_DIR AND GLEW_LIBRARY)
            target_include_directories(${TARGET_NAME} PRIVATE ${GLEW_INCLUDE_DIR})
            target_link_libraries(${TARGET_NAME} PRIVATE ${GLEW_LIBRARY})

            if(GLEW_LIBRARY MATCHES "glew32s|.*static.*")
                target_compile_definitions(${TARGET_NAME} PRIVATE GLEW_STATIC)
            endif()
        else()
            message(FATAL_ERROR "GLEW not found.")
        endif()
    endif()

    unset(FREEGLUT_LIB CACHE)
    find_library(FREEGLUT_LIB
        NAMES freeglut libfreeglut freeglutd
        PATHS
            "C:/msys64/mingw64/lib"
            "/mingw64/lib"
            "${COMMON_LIB_DIR}"
    )

    if(NOT FREEGLUT_LIB)
        message(FATAL_ERROR "freeglut not found.")
    endif()

    set(IRRKLANG_LIB "${COMMON_LIB_DIR}/libirrKlang.a")
    message(STATUS "SOIL_LIB = ${SOIL_LIB}")
    message(STATUS "FREEGLUT_LIB = ${FREEGLUT_LIB}")
    message(STATUS "IRRKLANG_LIB = ${IRRKLANG_LIB}")

    target_link_libraries(${TARGET_NAME} PRIVATE
        ${SOIL_LIB}
        ${FREEGLUT_LIB}
        ${OPENGL_LIBRARIES}
        glu32
    )

    if(EXISTS "${IRRKLANG_LIB}")
	target_compile_definitions(${TARGET_NAME} PRIVATE IRRKLANG_STATIC)
        target_link_libraries(${TARGET_NAME} PRIVATE "${IRRKLANG_LIB}")
    else()
        message(WARNING "irrKlang library not found at ${IRRKLANG_LIB}")
    endif()

    if(EXISTS "${COMMON_BIN_DIR}/irrKlang.dll")
        add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${COMMON_BIN_DIR}/irrKlang.dll"
            "$<TARGET_FILE_DIR:${TARGET_NAME}>"
        )
    endif()

    if(EXISTS "${COMMON_BIN_DIR}/ikpMP3.dll")
        add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${COMMON_BIN_DIR}/ikpMP3.dll"
            "$<TARGET_FILE_DIR:${TARGET_NAME}>"
        )
    endif()

    if(EXISTS "${COMMON_BIN_DIR}/ikpFlac.dll")
        add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${COMMON_BIN_DIR}/ikpFlac.dll"
            "$<TARGET_FILE_DIR:${TARGET_NAME}>"
        )
    endif()

    if(EXISTS "${COMMON_BIN_DIR}/glew32.dll")
        add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${COMMON_BIN_DIR}/glew32.dll"
            "$<TARGET_FILE_DIR:${TARGET_NAME}>"
        )
    endif()

endfunction()