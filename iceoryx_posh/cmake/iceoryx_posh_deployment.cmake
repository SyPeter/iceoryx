# configure deployment
if(NOT IOX_MAX_PORT_NUMBER)
    set(IOX_MAX_PORT_NUMBER 1024u)
endif()

if(NOT IOX_MAX_INTERFACE_NUMBER)
    set(IOX_MAX_INTERFACE_NUMBER 4u)
endif()

if(NOT IOX_MAX_RECEIVERS_PER_SENDERPORT)
    set(IOX_MAX_RECEIVERS_PER_SENDERPORT 256u)
endif()

if(NOT IOX_MAX_SUBSCRIBERS_PER_PUBLISHER)
    set(IOX_MAX_SUBSCRIBERS_PER_PUBLISHER 256u)
endif()

if(NOT IOX_MAX_CHUNKS_ALLOCATE_PER_SENDER)
    set(IOX_MAX_CHUNKS_ALLOCATE_PER_SENDER 8u)
endif()

if(NOT IOX_MAX_HISTORY_CAPACITY_OF_CHUNK_DISTRIBUTOR)
    set(IOX_MAX_HISTORY_CAPACITY_OF_CHUNK_DISTRIBUTOR 16u)
endif()

if(NOT IOX_MAX_CHUNKS_HELD_PER_RECEIVER)
    set(IOX_MAX_CHUNKS_HELD_PER_RECEIVER 256u)
endif()

message("#### ${CMAKE_CURRENT_SOURCE_DIR}/cmake/iceoryx_posh_deployment.hpp.in")
message("#### ${CMAKE_BINARY_DIR}/generated/iceoryx/include/iceoryx_posh/iceoryx_posh_deployment.hpp")

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/cmake/iceoryx_posh_deployment.hpp.in"
  "${CMAKE_BINARY_DIR}/generated/iceoryx/include/iceoryx_posh/iceoryx_posh_deployment.hpp" @ONLY)
