set(CORE_SRCS
    HangDetector.cpp
    Logger.cpp
    Config.cpp
    Thread.cpp
    Global.cpp
)

set(MAIN_SRCS
    main.cpp
)

add_library(CORE ${CORE_SRCS})

add_executable(MAIN ${MAIN_SRCS})
target_link_libraries(MAIN CORE ${OpenCV_LIBS})