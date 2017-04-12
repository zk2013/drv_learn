# install necessary static libs
yum install -y glibc-static  libstdc++-static zlib-static

ACE_BUILD_DIR=$(pwd)/ACE_build_tmp
rm -rf $ACE_BUILD_DIR
mkdir -p $ACE_BUILD_DIR
tar -xvf ACE-6.2.0.tar.bz2 -C  $ACE_BUILD_DIR 
export ACE_ROOT=$ACE_BUILD_DIR/ACE_wrappers
cp -f ace_config.h $ACE_ROOT/ace/config.h
cp -f ace_platform_macros.GNU $ACE_ROOT/include/makeinclude/platform_macros.GNU
cd $ACE_ROOT

# build and install dynamic lib
make && make install

# build and install static lib
make static_libs=1 && make install
