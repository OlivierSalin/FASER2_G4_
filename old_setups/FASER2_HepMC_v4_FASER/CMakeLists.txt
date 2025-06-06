#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 3.8...3.18)
if(${CMAKE_VERSION} VERSION_LESS 3.12)
  cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()
project(FASER2_HepMC_v4_FASER)

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
#
include(${Geant4_USE_FILE})

#----------------------------------------------------------------------------
# Find HepMC (required package)
#
find_package(HepMC REQUIRED)

#----------------------------------------------------------------------------
# Find Pythia6 (optional package)
#
find_package(Pythia6 QUIET)
if(PYTHIA6_FOUND)
  message(STATUS "G4 Examples: Pythia6 found. --> FASER2_HepMC_v4_FASER example with Pythia6 enabled.") 
  add_definitions(-DG4LIB_USE_PYTHIA) 
else()
  set(PYTHIA6_LIBRARIES "")  
endif()

#----------------------------------------------------------------------------
# Locate sources and headers for this project
#
include_directories(${PROJECT_SOURCE_DIR}/include 
                    ${Geant4_INCLUDE_DIR}
                    ${HEPMC_INCLUDE_DIR})
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(FASER2_HepMC_v4_FASER FASER2_HepMC_v4_FASER.cc ${sources} ${headers})
#target_link_libraries(FASER2_HepMC_v4_FASER ${Geant4_LIBRARIES}
#                      ${HEPMC_LIBRARIES} ${HEPMC_FIO_LIBRARIES}
#                      ${PYTHIA6_LIBRARIES} gfortran)
target_link_libraries(FASER2_HepMC_v4_FASER ${Geant4_LIBRARIES}
                      ${HEPMC_LIBRARIES} ${HEPMC_FIO_LIBRARIES}
                      ${PYTHIA6_LIBRARIES})

# if pythia is compiled with g77, link with -lg2c instead.
#target_link_libraries(FASER2_HepMC_v4_FASER ${Geant4_LIBRARIES}
#                      ${HEPMC_LIBRARIES} ${HEPMC_FIO_LIBRARIES}
#                      ${PYTHIA6_LIBRARIES} g2c)

#----------------------------------------------------------------------------
# Copy all scripts to the build directory, i.e. the directory in which we
# build FASER2_HepMC_v4_FASER. This is so that we can run the executable directly because it
# relies on these scripts being in the current working directory.
#
set(FASER2_HepMC_v4_FASER_SCRIPTS
    hepmc_ascii.in hepmc_ascii.out hepmc_pygen.in hepmc_pygen.out pyh4mu.mac pyset.mac vis.mac
    data/example_MyPythia.dat
  )

foreach(_script ${FASER2_HepMC_v4_FASER_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
install(TARGETS FASER2_HepMC_v4_FASER DESTINATION bin)

