add_executable(bm_nop bm_nop.cpp)
target_include_directories(bm_nop
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
  PUBLIC $<INSTALL_INTERFACE:include>
)
target_link_libraries(bm_nop
  gnuradio::gnuradio-runtime
  gnuradio::gnuradio-blocks
  gnuradio-bench
  )