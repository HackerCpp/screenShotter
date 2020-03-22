
if (CMAKE_VERSION VERSION_LESS 3.1.0)
    message(FATAL_ERROR "Qt 5 QmlDevTools module requires at least CMake version 3.1.0")
endif()

get_filename_component(_qt5QmlDevTools_install_prefix "${CMAKE_CURRENT_LIST_DIR}/../../../" ABSOLUTE)

# For backwards compatibility only. Use Qt5QmlDevTools_VERSION instead.
set(Qt5QmlDevTools_VERSION_STRING 5.13.1)

set(Qt5QmlDevTools_LIBRARIES Qt5::QmlDevTools)

macro(_qt5_QmlDevTools_check_file_exists file)
    if(NOT EXISTS "${file}" )
        message(FATAL_ERROR "The imported target \"Qt5::QmlDevTools\" references the file
   \"${file}\"
but this file does not exist.  Possible reasons include:
* The file was deleted, renamed, or moved to another location.
* An install or uninstall procedure did not complete successfully.
* The installation package was faulty and contained
   \"${CMAKE_CURRENT_LIST_FILE}\"
but not all the files it references.
")
    endif()
endmacro()

function(_qt5_QmlDevTools_process_prl_file prl_file_location Configuration lib_deps link_flags)
    set(_lib_deps)
    set(_link_flags)

    get_filename_component(_qt5_install_libs "${_qt5QmlDevTools_install_prefix}/lib" ABSOLUTE)

    if(EXISTS "${prl_file_location}")
        file(STRINGS "${prl_file_location}" _prl_strings REGEX "QMAKE_PRL_LIBS_FOR_CMAKE[ \t]*=")

        # file(STRINGS) replaces all semicolons read from the file with backslash semicolons.
        # We need to do a reverse transformation in CMake. For that we replace all backslash
        # semicolons with just semicolons, but due to the qmake substitution feature
        # creating this file, we need to double the amount of backslashes, so the final file
        # should have three backslashes and one semicolon.
        string(REGEX REPLACE "\\\;" ";" _prl_strings "${_prl_strings}")

        string(REGEX REPLACE "QMAKE_PRL_LIBS_FOR_CMAKE[ \t]*=[ \t]*([^\n]*)" "\\1" _static_depends "${_prl_strings}")
        string(REGEX REPLACE "[ \t]+" ";" _standard_libraries "${CMAKE_CXX_STANDARD_LIBRARIES}")
        set(_search_paths)
        string(REPLACE "\$\$[QT_INSTALL_LIBS]" "${_qt5_install_libs}" _static_depends "${_static_depends}")
        foreach(_flag ${_static_depends})
            string(REPLACE "\"" "" _flag ${_flag})
            if(_flag MATCHES "^-l(.*)$")
                # Handle normal libraries passed as -lfoo
                set(_lib "${CMAKE_MATCH_1}")
                foreach(_standard_library ${_standard_libraries})
                    if(_standard_library MATCHES "^${_lib}(\\.lib)?$")
                        set(_lib_is_default_linked TRUE)
                        break()
                    endif()
                endforeach()
                if (_lib_is_default_linked)
                    unset(_lib_is_default_linked)
                elseif(_lib MATCHES "^pthread$")
                    find_package(Threads REQUIRED)
                    list(APPEND _lib_deps Threads::Threads)
                else()
                    if(_search_paths)
                        find_library(_Qt5QmlDevTools_${Configuration}_${_lib}_PATH ${_lib} HINTS ${_search_paths} NO_DEFAULT_PATH)
                    endif()
                    find_library(_Qt5QmlDevTools_${Configuration}_${_lib}_PATH ${_lib})
                    mark_as_advanced(_Qt5QmlDevTools_${Configuration}_${_lib}_PATH)
                    if(_Qt5QmlDevTools_${Configuration}_${_lib}_PATH)
                        list(APPEND _lib_deps
                            ${_Qt5QmlDevTools_${Configuration}_${_lib}_PATH}
                        )
                    else()
                        message(FATAL_ERROR "Library not found: ${_lib}")
                    endif()
                endif()
            elseif(EXISTS "${_flag}")
                # The flag is an absolute path to an existing library
                list(APPEND _lib_deps "${_flag}")
            elseif(_flag MATCHES "^-L(.*)$")
                # Handle -Lfoo flags by putting their paths in the search path used by find_library above
                list(APPEND _search_paths "${CMAKE_MATCH_1}")
            else()
                # Handle all remaining flags by simply passing them to the linker
                list(APPEND _link_flags ${_flag})
            endif()
        endforeach()
    endif()

    string(REPLACE ";" " " _link_flags "${_link_flags}")
    set(${lib_deps} ${_lib_deps} PARENT_SCOPE)
    set(${link_flags} "SHELL:${_link_flags}" PARENT_SCOPE)
endfunction()

macro(_populate_QmlDevTools_target_properties Configuration LIB_LOCATION IMPLIB_LOCATION
      IsDebugAndRelease)
    set_property(TARGET Qt5::QmlDevTools APPEND PROPERTY IMPORTED_CONFIGURATIONS ${Configuration})

    set(imported_location "${_qt5QmlDevTools_install_prefix}/lib/${LIB_LOCATION}")
    _qt5_QmlDevTools_check_file_exists(${imported_location})
    set(_deps
        ${_Qt5QmlDevTools_LIB_DEPENDENCIES}
    )
    set(_static_deps
        ${_Qt5QmlDevTools_STATIC_${Configuration}_LIB_DEPENDENCIES}
    )

    set_target_properties(Qt5::QmlDevTools PROPERTIES
        "IMPORTED_LOCATION_${Configuration}" ${imported_location}
        # For backward compatibility with CMake < 2.8.12
        "IMPORTED_LINK_INTERFACE_LIBRARIES_${Configuration}" "${_deps};${_static_deps}"
    )
    set_property(TARGET Qt5::QmlDevTools APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                 "${_deps}"
    )

    if(NOT ${IsDebugAndRelease})
        set(_genex_condition "1")
    else()
        if(${Configuration} STREQUAL DEBUG)
            set(_genex_condition "$<CONFIG:Debug>")
        else()
            set(_genex_condition "$<NOT:$<CONFIG:Debug>>")
        endif()
    endif()

    if(_static_deps)
        set(_static_deps_genex "$<${_genex_condition}:${_static_deps}>")
        set_property(TARGET Qt5::QmlDevTools APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     "${_static_deps_genex}"
        )
    endif()

    set(_static_link_flags "${_Qt5QmlDevTools_STATIC_${Configuration}_LINK_FLAGS}")
    if(NOT CMAKE_VERSION VERSION_LESS "3.13" AND _static_link_flags)
        set(_static_link_flags_genex "$<${_genex_condition}:${_static_link_flags}>")
        set_property(TARGET Qt5::QmlDevTools APPEND PROPERTY INTERFACE_LINK_OPTIONS
            "${_static_link_flags_genex}"
        )
    endif()

endmacro()

if (NOT TARGET Qt5::QmlDevTools)

    set(_Qt5QmlDevTools_OWN_INCLUDE_DIRS "${_qt5QmlDevTools_install_prefix}/include/" "${_qt5QmlDevTools_install_prefix}/include/QtQml")
    set(Qt5QmlDevTools_PRIVATE_INCLUDE_DIRS
        "${_qt5QmlDevTools_install_prefix}/include/QtQml/5.13.1"
        "${_qt5QmlDevTools_install_prefix}/include/QtQml/5.13.1/QtQml"
    )

    foreach(_dir ${_Qt5QmlDevTools_OWN_INCLUDE_DIRS})
        _qt5_QmlDevTools_check_file_exists(${_dir})
    endforeach()

    # Only check existence of private includes if the Private component is
    # specified.
    list(FIND Qt5QmlDevTools_FIND_COMPONENTS Private _check_private)
    if (NOT _check_private STREQUAL -1)
        foreach(_dir ${Qt5QmlDevTools_PRIVATE_INCLUDE_DIRS})
            _qt5_QmlDevTools_check_file_exists(${_dir})
        endforeach()
    endif()

    set(Qt5QmlDevTools_INCLUDE_DIRS ${_Qt5QmlDevTools_OWN_INCLUDE_DIRS})

    set(Qt5QmlDevTools_DEFINITIONS -DQT_QMLDEVTOOLS_LIB)
    set(Qt5QmlDevTools_COMPILE_DEFINITIONS QT_QMLDEVTOOLS_LIB)
    set(_Qt5QmlDevTools_MODULE_DEPENDENCIES "Core")


    set(Qt5QmlDevTools_OWN_PRIVATE_INCLUDE_DIRS ${Qt5QmlDevTools_PRIVATE_INCLUDE_DIRS})

    set(_Qt5QmlDevTools_FIND_DEPENDENCIES_REQUIRED)
    if (Qt5QmlDevTools_FIND_REQUIRED)
        set(_Qt5QmlDevTools_FIND_DEPENDENCIES_REQUIRED REQUIRED)
    endif()
    set(_Qt5QmlDevTools_FIND_DEPENDENCIES_QUIET)
    if (Qt5QmlDevTools_FIND_QUIETLY)
        set(_Qt5QmlDevTools_DEPENDENCIES_FIND_QUIET QUIET)
    endif()
    set(_Qt5QmlDevTools_FIND_VERSION_EXACT)
    if (Qt5QmlDevTools_FIND_VERSION_EXACT)
        set(_Qt5QmlDevTools_FIND_VERSION_EXACT EXACT)
    endif()

    set(Qt5QmlDevTools_EXECUTABLE_COMPILE_FLAGS "")

    foreach(_module_dep ${_Qt5QmlDevTools_MODULE_DEPENDENCIES})
        if (NOT Qt5${_module_dep}_FOUND)
            find_package(Qt5${_module_dep}
                5.13.1 ${_Qt5QmlDevTools_FIND_VERSION_EXACT}
                ${_Qt5QmlDevTools_DEPENDENCIES_FIND_QUIET}
                ${_Qt5QmlDevTools_FIND_DEPENDENCIES_REQUIRED}
                PATHS "${CMAKE_CURRENT_LIST_DIR}/.." NO_DEFAULT_PATH
            )
        endif()

        if (NOT Qt5${_module_dep}_FOUND)
            set(Qt5QmlDevTools_FOUND False)
            return()
        endif()

        list(APPEND Qt5QmlDevTools_INCLUDE_DIRS "${Qt5${_module_dep}_INCLUDE_DIRS}")
        list(APPEND Qt5QmlDevTools_PRIVATE_INCLUDE_DIRS "${Qt5${_module_dep}_PRIVATE_INCLUDE_DIRS}")
        list(APPEND Qt5QmlDevTools_DEFINITIONS ${Qt5${_module_dep}_DEFINITIONS})
        list(APPEND Qt5QmlDevTools_COMPILE_DEFINITIONS ${Qt5${_module_dep}_COMPILE_DEFINITIONS})
        list(APPEND Qt5QmlDevTools_EXECUTABLE_COMPILE_FLAGS ${Qt5${_module_dep}_EXECUTABLE_COMPILE_FLAGS})
    endforeach()
    list(REMOVE_DUPLICATES Qt5QmlDevTools_INCLUDE_DIRS)
    list(REMOVE_DUPLICATES Qt5QmlDevTools_PRIVATE_INCLUDE_DIRS)
    list(REMOVE_DUPLICATES Qt5QmlDevTools_DEFINITIONS)
    list(REMOVE_DUPLICATES Qt5QmlDevTools_COMPILE_DEFINITIONS)
    list(REMOVE_DUPLICATES Qt5QmlDevTools_EXECUTABLE_COMPILE_FLAGS)

    set(_Qt5QmlDevTools_LIB_DEPENDENCIES "Qt5::Core")


    if(NOT Qt5_EXCLUDE_STATIC_DEPENDENCIES)

        _qt5_QmlDevTools_process_prl_file(
            "${_qt5QmlDevTools_install_prefix}/lib/libQt5QmlDevTools.prl" RELEASE
            _Qt5QmlDevTools_STATIC_RELEASE_LIB_DEPENDENCIES
            _Qt5QmlDevTools_STATIC_RELEASE_LINK_FLAGS
        )
    endif()

    add_library(Qt5::QmlDevTools STATIC IMPORTED)
    set_property(TARGET Qt5::QmlDevTools PROPERTY IMPORTED_LINK_INTERFACE_LANGUAGES CXX)

    set_property(TARGET Qt5::QmlDevTools PROPERTY
      INTERFACE_INCLUDE_DIRECTORIES ${_Qt5QmlDevTools_OWN_INCLUDE_DIRS})
    set_property(TARGET Qt5::QmlDevTools PROPERTY
      INTERFACE_COMPILE_DEFINITIONS QT_QMLDEVTOOLS_LIB)

    set_property(TARGET Qt5::QmlDevTools PROPERTY INTERFACE_QT_ENABLED_FEATURES )
    set_property(TARGET Qt5::QmlDevTools PROPERTY INTERFACE_QT_DISABLED_FEATURES )

    set(_Qt5QmlDevTools_PRIVATE_DIRS_EXIST TRUE)
    foreach (_Qt5QmlDevTools_PRIVATE_DIR ${Qt5QmlDevTools_OWN_PRIVATE_INCLUDE_DIRS})
        if (NOT EXISTS ${_Qt5QmlDevTools_PRIVATE_DIR})
            set(_Qt5QmlDevTools_PRIVATE_DIRS_EXIST FALSE)
        endif()
    endforeach()

    if (_Qt5QmlDevTools_PRIVATE_DIRS_EXIST)
        add_library(Qt5::QmlDevToolsPrivate INTERFACE IMPORTED)
        set_property(TARGET Qt5::QmlDevToolsPrivate PROPERTY
            INTERFACE_INCLUDE_DIRECTORIES ${Qt5QmlDevTools_OWN_PRIVATE_INCLUDE_DIRS}
        )
        set(_Qt5QmlDevTools_PRIVATEDEPS)
        foreach(dep ${_Qt5QmlDevTools_LIB_DEPENDENCIES})
            if (TARGET ${dep}Private)
                list(APPEND _Qt5QmlDevTools_PRIVATEDEPS ${dep}Private)
            endif()
        endforeach()
        set_property(TARGET Qt5::QmlDevToolsPrivate PROPERTY
            INTERFACE_LINK_LIBRARIES Qt5::QmlDevTools ${_Qt5QmlDevTools_PRIVATEDEPS}
        )
    endif()

    _populate_QmlDevTools_target_properties(RELEASE "libQt5QmlDevTools.a" "" FALSE)








_qt5_QmlDevTools_check_file_exists("${CMAKE_CURRENT_LIST_DIR}/Qt5QmlDevToolsConfigVersion.cmake")

endif()