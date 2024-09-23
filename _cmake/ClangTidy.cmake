function(target_enable_clang_tidy target)
    find_program(CLANG-TIDY_PATH clang-tidy)

    if (CLANG-TIDY_PATH-NOTFOUND)
        message(WARNING "clang-tidy not found.")
    else()
        message(STATUS "Enabling clang-tidy for ${target}")
        list(APPEND CLANG-TIDY_CHECKS
            "bugprone-*"
            "clang-analyzer-*"
            "concurrency-*"
            "cppcoreguidelines-*"
            "modernize-*"
            "performance-*"
            "readability-*"
            "-modernize-use-trailing-return-type"
        )

        list(JOIN CLANG-TIDY_CHECKS ";" CLANG-TIDY_CHECK_STR)

        set_target_properties(${target}
            PROPERTIES CXX_CLANG_TIDY "${CLANG-TIDY_PATH};-checks=-*;--warnings-as-errors=*;${CLANG-TIDY-CHECK-STR}"
        )

        mark_as_advanced(CLANG-CLANG-TIDY_CHECK_STR)
    endif()
endfunction()