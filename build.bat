
SET CUR_PATH=%~dp0

SET PKG_ROOT_PATH=%CUR_PATH%vcpkg\installed\x64-windows
SET PKG_INC_PATH=%PKG_ROOT_PATH%\include
SET PKG_LIB_PATH=%PKG_ROOT_PATH%\lib
SET PKG_CONFIG_PATH=%PKG_ROOT_PATH%\share


.\vcpkg\downloads\tools\cmake-3.17.2-windows\cmake-3.17.2-win32-x86\bin\cmake.exe -S ./src -B build -DCMAKE_TOOLCHAIN_FILE="%CUR_PATH%\vcpkg\scripts\buildsystems\vcpkg.cmake" -DVCPKG_TARGET_TRIPLET=x64-windows -DPKG_INC_PATH=%PKG_INC_PATH% -DPKG_LIB_PATH=%PKG_LIB_PATH% -DPKG_CONFIG_PATH=%PKG_CONFIG_PATH%

PAUSE