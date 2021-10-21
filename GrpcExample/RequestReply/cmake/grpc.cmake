get_target_property(gRPC_CPP_PLUGIN_EXECUTABLE gRPC::grpc_cpp_plugin IMPORTED_LOCATION_RELEASE)


function(GRPC_GENERATE_CPP SRCS HDRS OUTPUT_FOLDER)

    if(NOT ARGN)
        message(SEND_ERROR "Error: GRPC_GENERATE_CPP() called without any proto files")
        return()
    endif()

    set(${SRCS})
    set(${HDRS})
    foreach(PROTO ${ARGN})
        get_filename_component(PROTO_PATH ${PROTO} DIRECTORY)
        get_filename_component(ABSOLUTE_FILE_ID ${PROTO} ABSOLUTE)
        get_filename_component(FILE_ID ${PROTO} NAME_WE)

        list(APPEND ${SRCS} "${OUTPUT_FOLDER}/${FILE_ID}.grpc.pb.cc")
        list(APPEND ${HDRS} "${OUTPUT_FOLDER}/${FILE_ID}.grpc.pb.h")

        add_custom_command(
                OUTPUT "${OUTPUT_FOLDER}/${FILE_ID}.grpc.pb.cc"
                       "${OUTPUT_FOLDER}/${FILE_ID}.grpc.pb.h"
                COMMAND ${PROTOBUF_PROTOC_EXECUTABLE}
                ARGS "--proto_path=${PROTO_PATH}"
                     "--grpc_out=${OUTPUT_FOLDER}"
                     "--plugin=protoc-gen-grpc=${gRPC_CPP_PLUGIN_EXECUTABLE}"
                     "${ABSOLUTE_FILE_ID}"
                COMMENT "Running C++ gRPC compiler on ${PROTO}"
                VERBATIM)
    endforeach()

    set_source_files_properties(${${SRCS}} ${${HDRS}} PROPERTIES GENERATED TRUE)
    set(${SRCS} ${${SRCS}} PARENT_SCOPE)
    set(${HDRS} ${${HDRS}} PARENT_SCOPE)

endfunction()
