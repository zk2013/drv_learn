# install necessary static libs
yum install -y glibc-static  libstdc++-static zlib-static

ACE_BUILD_DIR := ACE_build_tmp
rm -rf ${ACE_BUILD_DIR}
