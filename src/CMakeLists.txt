set(CORE_SRCS
    HangDetector.cpp
    Logger.cpp
    Config.cpp
    Thread.cpp
    GPIO.cpp
    RPI_GPIO.cpp
    Global.cpp
    MemoryPool.cpp
)

set(MAIN_SRCS
    main.cpp
)

add_library(CORE ${CORE_SRCS})

add_executable(MAIN ${MAIN_SRCS})
target_link_libraries(MAIN CORE Threads::Threads ${OpenCV_LIBS})
