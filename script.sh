####################################
echo Stage 1 - Building Dependencies
####################################

# make a working directory
cd $HOME/Documentos
rm -rf Cross
mkdir Cross
cd Cross

# install or update all apt-get dependencies
sudo apt-get update
sudo apt-get upgrade
sudo apt-get install gcc                   # not cross
sudo apt-get install g++
sudo apt-get install make
sudo apt-get install bison
sudo apt-get install flex
sudo apt-get install gawk
sudo apt-get install libgmp3-dev
sudo apt-get install libmpfr-dev libmpfr-doc libmpfr4 libmpfr4-dbg
sudo apt-get install mpc
sudo apt-get install texinfo               # optional
sudo apt-get install libcloog-isl-dev      # optional
sudo apt-get install build-essential
sudo apt-get install glibc-devel
sudo apt-get -y install gcc-multilib libc6-i386

# download and unpack necessary files
wget http://ftpmirror.gnu.org/binutils/binutils-2.25.1.tar.gz
wget http://ftpmirror.gnu.org/gcc/gcc-5.3.0/gcc-5.3.0.tar.gz
wget http://ftpmirror.gnu.org/mpc/mpc-1.0.3.tar.gz
for f in *.tar*; do tar zvxf $f; done

# create installation directory
mkdir Install
export PREFIX="$HOME/Documentos/Cross/Install"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"

################################
echo Stage 2 - Building Compiler
################################

# install mpc
mkdir build-mpc
cd build-mpc
../mpc-1.0.3/configure --prefix="$PREFIX"
make -j2
make -j2 check
make -j2 install
cd ..

# install binutils
mkdir build-binutils
cd build-binutils
../binutils-2.25.1/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
make -j2
make -j2 install
cd ..

# install gcc
mkdir build-gcc
cd build-gcc
../gcc-5.3.0/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers --with-mpc="$PREFIX"
make -j2 all-gcc
make -j2 all-target-libgcc
make -j2 install-gcc
make -j2 install-target-libgcc
