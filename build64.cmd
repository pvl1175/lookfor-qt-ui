rmdir /S /Q .vscode
rmdir /S /Q .vs
rmdir /S /Q out
rmdir /S /Q thrift-interface-definitions
rmdir /S /Q thrift
rmdir /S /Q api

git clone https://github.com/pvl1175/thrift-interface-definitions
mkdir api
thrift -r -gen cpp:no_skeleton,pure_enums,moveable_types -out .\api .\thrift-interface-definitions\lookfor9.thrift

git clone https://github.com/pvl1175/thrift
cd thrift

cd ..
mkdir build64
cd build64

cmake .. -A x64 -DCMAKE_TOOLCHAIN_FILE=e:/vcpkg/scripts/buildsystems/vcpkg.cmake
cmake  --build . --config Debug
cmake  --build . --config Release

REM pause
