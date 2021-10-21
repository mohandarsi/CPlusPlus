function(PROTOBUF_GENERATE_CPP SRCS HDRS OUTPUT_FOLDER)

    if(NOT ARGN)
        message(SEND_ERROR "Error: PROTOBUF_GENERATE_CPP() called without any proto files")
        return()
    endif()

    set(${SRCS})
    set(${HDRS})
    foreach(PROTO ${ARGN})
        get_filename_component(PROTO_PATH ${PROTO} DIRECTORY)
        get_filename_component(ABSOLUTE_FILE_NAME ${PROTO} ABSOLUTE)
        get_filename_component(PROTO_ID ${PROTO} NAME_WE)

        list(APPEND ${SRCS} "${OUTPUT_FOLDER}/${PROTO_ID}.pb.cc")
        list(APPEND ${HDRS} "${OUTPUT_FOLDER}/${PROTO_ID}.pb.h")

        add_custom_command(
            OUTPUT  "${OUTPUT_FOLDER}/${PROTO_ID}.pb.cc"
                    "${OUTPUT_FOLDER}/${PROTO_ID}.pb.h"
            COMMAND "${PROTOBUF_PROTOC_EXECUTABLE}"
            ARGS    "--proto_path=${PROTO_PATH}"
                    "--cpp_out=${OUTPUT_FOLDER}"
                    ${ABSOLUTE_FILE_NAME}
            COMMENT "Running C++ protocol buffer compiler on ${PROTO}"
            VERBATIM)
    endforeach()

    set_source_files_properties(${${SRCS}} ${${HDRS}} PROPERTIES GENERATED TRUE)
    set(${SRCS} ${${SRCS}} PARENT_SCOPE)
    set(${HDRS} ${${HDRS}} PARENT_SCOPE)

endfunction()
