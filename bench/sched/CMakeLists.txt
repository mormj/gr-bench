add_executable(bm_a bm_a.cpp)
target_include_directories(bm_a
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
  PUBLIC $<INSTALL_INTERFACE:include>
)
target_link_libraries(bm_a
  gnuradio::gnuradio-runtime
  gnuradio::gnuradio-blocks
  gnuradio-bench
  Boost::program_options
  )


add_executable(bm_b bm_b.cpp)
target_include_directories(bm_b
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
  PUBLIC $<INSTALL_INTERFACE:include>
)
target_link_libraries(bm_b
  gnuradio::gnuradio-runtime
  gnuradio::gnuradio-blocks
  gnuradio-bench
  Boost::program_options
  )


add_executable(bm_b_latency bm_b_latency.cpp)
target_include_directories(bm_b_latency
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
  PUBLIC $<INSTALL_INTERFACE:include>
)
target_link_libraries(bm_b_latency
  gnuradio::gnuradio-runtime
  gnuradio::gnuradio-blocks
  gnuradio-bench
  Boost::program_options
  )
