INCLUDE(ParaViewTestingMacros)

set(MODULE_TESTS
  ${CMAKE_CURRENT_SOURCE_DIR}/SLACTools.xml
)

IF (PARAVIEW_BUILD_QT_GUI AND BUILD_SHARED_LIBS)

  set (SLACTools_THRESHOLD 70)

  add_client_tests("pv"
    LOAD_PLUGIN "SLACTools"
    TEST_SCRIPTS ${MODULE_TESTS}
  )

ENDIF ()
