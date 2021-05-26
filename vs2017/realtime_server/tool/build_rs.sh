#!/bin/sh

chmod u+x build_rs.sh;
chmod u+x kill_rs.sh;
chmod u+x run_rs.sh;
chmod u+x show_rs.sh;



RS_DIR=`cd .. && pwd`
RS_SYMBOLIC_LINK=~/rs

if [ ! -L "$RS_SYMBOLIC_LINK" ]; then
    ln -s $RS_DIR $RS_SYMBOLIC_LINK;
    echo "RS_SYMBOLIC_LINK is created successfully."
else
    echo "RS_SYMBOLIC_LINK is already exist."
fi



# cmake

CUR_DIR=`pwd`
SOURCE_DIR="${CUR_DIR}/../"
BUILD_DIR="${CUR_DIR}/../build"

if [ ! -d ${BUILD_DIR} ]; then
  mkdir ${BUILD_DIR}
fi

if [ -x ${BUILD_DIR} ]; then
    cd ${BUILD_DIR} && cmake ${SOURCE_DIR} && make $*
fi



cd -
RS_BIN_DIR="${CUR_DIR}/../build/bin"
RS_BIN_SYMBOLIC_LINK=bin_rs

if [ ! -L "$RS_BIN_SYMBOLIC_LINK" ]; then
    ln -s $RS_BIN_DIR $RS_BIN_SYMBOLIC_LINK;
    echo "RS_BIN_SYMBOLIC_LINK is created successfully."
else
    echo "RS_BIN_SYMBOLIC_LINK is already exist."
fi



# copy lua file to bin path

EXAMPLE_NAME="for_ue4_demo"
EXAMPLE_DIR="${RS_DIR}/example/${EXAMPLE_NAME}"

mkdir -p ${RS_BIN_DIR}/${EXAMPLE_NAME}
cp  ${EXAMPLE_DIR}/*.lua  ${RS_BIN_DIR}/${EXAMPLE_NAME}/
echo "copy lua file to bin path finished."



# copy config file to bin path

REALTIME_SRV_DIR="${RS_DIR}/realtime_srv"

mkdir -p ${RS_BIN_DIR}/config/
cp  ${REALTIME_SRV_DIR}/*.ini  ${RS_BIN_DIR}/config/
echo "copy config file to bin path finished."


exit 0