find_program(GLSLC glslc HINTS "$ENV{VULKAN_SDK}/Bin")

if(NOT GLSLC)
    message(WARNING "glslc not found! Shader compilation will fail.")
endif()

function(compile_shader SHADER_NAME STAGE)
    set(INPUT_FILE "${CMAKE_CURRENT_SOURCE_DIR}/${SHADER_NAME}.${STAGE}")
    set(OUTPUT_FILE "${CMAKE_BINARY_DIR}/shaders/${SHADER_NAME}.${STAGE}.spv")
    
    file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/shaders")
    
    add_custom_command(
        OUTPUT ${OUTPUT_FILE}
        COMMAND ${GLSLC} ${INPUT_FILE} -o ${OUTPUT_FILE}
        DEPENDS ${INPUT_FILE}
        COMMENT "Compiling shader: ${INPUT_FILE}"
    )
    
    list(APPEND SHADER_SPVS ${OUTPUT_FILE})
    set(SHADER_SPVS ${SHADER_SPVS} PARENT_SCOPE)
endfunction()

# Example shaders (Faz 0 placeholders)
# compile_shader(basic vert)
# compile_shader(basic frag)

add_custom_target(Shaders ALL DEPENDS ${SHADER_SPVS})
