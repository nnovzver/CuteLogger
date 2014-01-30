import qbs 1.0

DynamicLibrary {
  name: "CuteLogger"

  files: [ "src/*", "include/*" ]
  excludeFiles: [ "src/OutputDebugAppender.*" ]

  Group {
    condition: qbs.targetOS == "windows"
    files: [ "src/OutputDebugAppender.cpp", "include/OutputDebugAppender.h" ]
  }

  Depends { name: "cpp" }
  cpp.includePaths: "include"
  cpp.defines: "CUTELOGGER_LIBRARY"

  Depends { name: "Qt.core" }

  Export {
    Depends { name: "cpp" }
    cpp.includePaths: "include"
  }
}