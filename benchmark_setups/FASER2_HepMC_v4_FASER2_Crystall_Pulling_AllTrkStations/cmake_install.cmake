# Install script for directory: /Users/mcfayden/Work/FASER/FASER2/G4_v2/FASER2_HepMC_v4_FASER2_Crystall_Pulling_AllTrkStations2_Cavern_1stTrkStation

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/objdump")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/Users/mcfayden/Work/FASER/FASER2/G4_v2/FASER2_HepMC_v4_FASER2_Crystall_Pulling_AllTrkStations2_Cavern_1stTrkStation/FASER2_HepMC_v4_FASER2_Crystall_Pulling_AllTrkStations2_Cavern_1stTrkStation")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/FASER2_HepMC_v4_FASER2_Crystall_Pulling_AllTrkStations2_Cavern_1stTrkStation" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/FASER2_HepMC_v4_FASER2_Crystall_Pulling_AllTrkStations2_Cavern_1stTrkStation")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/mcfayden/Work/FASER/FASER2/G4_v2/geant4.10.07.p02-install/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/FASER2_HepMC_v4_FASER2_Crystall_Pulling_AllTrkStations2_Cavern_1stTrkStation")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -u -r "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/FASER2_HepMC_v4_FASER2_Crystall_Pulling_AllTrkStations2_Cavern_1stTrkStation")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/Users/mcfayden/Work/FASER/FASER2/G4_v2/FASER2_HepMC_v4_FASER2_Crystall_Pulling_AllTrkStations2_Cavern_1stTrkStation/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
