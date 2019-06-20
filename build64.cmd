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


REM pause
