rm -r -f .vscode
rm -r -f .vs
rm -r -f out
rm -r -f thrift-interface-definitions
rm -r -f thrift
rm -r -f api

git clone https://github.com/pvl1175/thrift-interface-definitions
mkdir api
thrift -r -gen cpp:no_skeleton,pure_enums,moveable_types -out .\api .\thrift-interface-definitions\lookfor9.thrift

git clone https://github.com/pvl1175/thrift
cd thrift

