project(kfunambol)

find_package(KDE4)
include(KDE4Defaults)

set(kfunambol_SRC
    main.cpp
)

include_directories(${KDE4_INCLUDES})

kde4_add_executable(kfunambol ${kfunambol_SRC})
target_link_libraries(kfunambol ${KDE4_KDEUI_LIBS})

install(TARGETS kfunambol DESTINATION ${BIN_INSTALL_DIR})
# install(FILES kfunambol.desktop DESTINATION ${XDG_APPS_INSTALL_DIR})
install(FILES kfunambolui.rc  DESTINATION  ${DATA_INSTALL_DIR}/kfunambol)
