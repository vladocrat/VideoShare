set(FFMPEG_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/ffmpeg)
set(FFMPEG_INCLUDE_DIR "${FFMPEG_ROOT}/include")
set(FFMPEG_LIB_DIR "${FFMPEG_ROOT}/lib")

set(FFMPEG_LIBRARIES
    avutil
    avcodec
    avformat
    swresample
    swscale
    avfilter
    avdevice
)

include_directories(${FFMPEG_INCLUDE_DIR})
link_directories(${FFMPEG_LIB_DIR})
