CMAKE_DIR=build

function run_cmake() { 
    mkdir $CMAKE_DIR
    cd $CMAKE_DIR
    cmake ..
}

function run_make_all() {
    cd $CMAKE_DIR
    make clean
    make all
}

function run_make_clean() {
    cd $CMAKE_DIR
    make clean
}

function run_delete_cmake_dir() {
    rm -rf $CMAKE_DIR
}

option="${1}" 
case ${option} in 
   -C) CMAKE_DIR="${2}" 
      echo "cmake directory is $CMAKE_DIR"
      run_cmake
      ;; 
   -a) CMAKE_DIR="${2}"
      echo "make all directory is $CMAKE_DIR"
      run_make_all 
      ;;
   -c) CMAKE_DIR="${2}"
      echo "make clean directory is $CMAKE_DIR"
      run_make_clean
      ;; 

   -d) CMAKE_DIR="${2}"
      echo "Delete directory is $CMAKE_DIR"
      run_delete_cmake_dir
      ;; 
    
   *)  
   printf "`basename ${0}`:usage:
                [-C <build dir> (Generate cmake files)] 
                [-a <build dir> (Runs 'make all')]
                [-c <build dir> (Runs 'make clean')]
                [-d <build dir> (Delete the cmake directory)]\n"   
      exit 1 # Command to come out of the program with status 1
      ;; 
esac

