install(
    TARGETS sandbox_exe
    RUNTIME COMPONENT sandbox_Runtime
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
