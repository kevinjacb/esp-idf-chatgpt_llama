file(GLOB_RECURSE SRC_UI ${CMAKE_SOURCE_DIR} "ui/*.c")
idf_component_register(
    SRCS 
        "gui.c"
        "chatgpt.c"
        "wifi.c"
        ${SRC_UI}
    INCLUDE_DIRS 
        "."
        "ui"
)
