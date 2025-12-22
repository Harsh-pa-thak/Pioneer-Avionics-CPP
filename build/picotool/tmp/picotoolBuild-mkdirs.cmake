# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/kunsh/Ignition/Pioneer/build/_deps/picotool-src"
  "/home/kunsh/Ignition/Pioneer/build/_deps/picotool-build"
  "/home/kunsh/Ignition/Pioneer/build/_deps"
  "/home/kunsh/Ignition/Pioneer/build/picotool/tmp"
  "/home/kunsh/Ignition/Pioneer/build/picotool/src/picotoolBuild-stamp"
  "/home/kunsh/Ignition/Pioneer/build/picotool/src"
  "/home/kunsh/Ignition/Pioneer/build/picotool/src/picotoolBuild-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/kunsh/Ignition/Pioneer/build/picotool/src/picotoolBuild-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/kunsh/Ignition/Pioneer/build/picotool/src/picotoolBuild-stamp${cfgdir}") # cfgdir has leading slash
endif()
