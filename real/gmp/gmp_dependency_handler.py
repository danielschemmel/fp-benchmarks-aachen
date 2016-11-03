def generate_gmp_dependency_code(depAndTargetInfo):
  import svcb
  import svcb.build
  # Unpack the needed information
  assert isinstance(depAndTargetInfo, svcb.build.CMakeDependencyAndTargetInfo)
  info = depAndTargetInfo.dependencyInfo
  targetName = depAndTargetInfo.targetName
  enableTargetCMakeVariable = depAndTargetInfo.enableTargetCMakeVariable
  disabledTargetReasonsCMakeVariable = depAndTargetInfo.disabledTargetReasonsCMakeVariable
  cmakeIndent = depAndTargetInfo.cmakeIndent

  # Emit code that decides whether or not to build the target.
  preGuardCode = """
if (NOT GMP_AVAILABLE)
{indent}set({enableTargetCMakeVariable} FALSE)
{indent}list(APPEND {disabledTargetReasonsCMakeVariable} "GMP library not available")
endif()
  """.format(indent=cmakeIndent,
             enableTargetCMakeVariable=enableTargetCMakeVariable,
             disabledTargetReasonsCMakeVariable=disabledTargetReasonsCMakeVariable)

  # Emit code to link the target against the necessary libraries
  # and set include paths. This code is emitted inside the guard so
  # it only has an effect if the target is being built.
  inGuardCode = "{indent}target_include_directories({targetName} SYSTEM BEFORE PRIVATE ${{GMP_INCLUDE_DIR}})\n".format(
    indent=cmakeIndent,
    targetName=targetName)

  inGuardCode += "{indent}target_link_libraries({targetName} PRIVATE ${{GMP_LIBS}})\n".format(
    indent=cmakeIndent,
    targetName=targetName)
  return (preGuardCode, inGuardCode)

# Register the handler
register_handler('gmp', generate_gmp_dependency_code)
