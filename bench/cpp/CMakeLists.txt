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

add_executable(bm_copy bm_copy.cpp)
target_include_directories(bm_nop
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
  PUBLIC $<INSTALL_INTERFACE:include>
)
target_link_libraries(bm_copy
  gnuradio::gnuradio-runtime
  gnuradio::gnuradio-blocks
  gnuradio-bench
  )

add_executable(bm_pmt_serialize_uvec bm_pmt_serialize_uvec.cpp)
target_include_directories(bm_pmt_serialize_uvec
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
  PUBLIC $<INSTALL_INTERFACE:include>
)
target_link_libraries(bm_pmt_serialize_uvec
  gnuradio::gnuradio-runtime
  # gnuradio::gnuradio-pmt
  )

add_executable(bm_pmt_dict_ref bm_pmt_dict_ref.cpp)
target_include_directories(bm_pmt_dict_ref
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
  PUBLIC $<INSTALL_INTERFACE:include>
)
target_link_libraries(bm_pmt_dict_ref
  gnuradio::gnuradio-runtime
  # gnuradio::gnuradio-pmt
  )


add_executable(bm_pmt_dict_pack_unpack bm_pmt_dict_pack_unpack.cpp)
target_include_directories(bm_pmt_dict_pack_unpack
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
  PUBLIC $<INSTALL_INTERFACE:include>
)
target_link_libraries(bm_pmt_dict_pack_unpack
  gnuradio::gnuradio-runtime
  # gnuradio::gnuradio-pmt
  )  

add_executable(bm_msg_forward bm_msg_forward.cpp)
target_include_directories(bm_msg_forward
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
  PUBLIC $<INSTALL_INTERFACE:include>
)
target_link_libraries(bm_msg_forward
  gnuradio::gnuradio-runtime
  gnuradio::gnuradio-blocks
  gnuradio-bench
  )


add_executable(bm_pdu_process bm_pdu_process.cpp)
target_include_directories(bm_pdu_process
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
  PUBLIC $<INSTALL_INTERFACE:include>
)
target_link_libraries(bm_pdu_process
  gnuradio::gnuradio-runtime
  gnuradio::gnuradio-blocks
  gnuradio-bench
  )