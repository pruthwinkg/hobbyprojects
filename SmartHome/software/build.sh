
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

function run_make_all_with_debug() {
    mkdir $CMAKE_DIR
    cd $CMAKE_DIR
    cmake -DCMAKE_BUILD_TYPE=Debug ..
    make clean
    make all  
}

function run_make_all_with_testcode() {
    mkdir $CMAKE_DIR
    cd $CMAKE_DIR
    cmake -DEnableTestCode=true ..
    make clean
    make all  
}

function run_make_all_with_testcode_and_debug() {
    mkdir $CMAKE_DIR
    cd $CMAKE_DIR
    cmake -DEnableTestCode=true -DCMAKE_BUILD_TYPE=Debug ..
    make clean
    make all  
}

function run_generate_cscope_ctags() {
    ctags -R
    find ./ -name '*.c' -o -name '*.h' > cscope.files
    cscope -q -R -b -i cscope.files
    echo "Generated ctags and cscope. Ready for use (cscope -d)"
}

function run_autogenerate_clis() {
    python ./apps/shell/cli_parser.py --parse 
}

function run_clean_autogenerate_clis() {
    python ./apps/shell/cli_parser.py --clean
}


function run_install_tools() {
    echo "This will install build-tools, vim, cscope, ctags, tmux, cmake"

    sudo apt update
    apt install build-essential
    apt-get install manpages-dev
    apt install vim
    apt install cscope
    apt install ctags
    apt install tmux
    apt install cmake
    apt install python
    apt install python-yaml    
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
   -D) CMAKE_DIR="${2}"
      echo "make all directory is $CMAKE_DIR"
      run_make_all_with_debug 
      ;;
   -t) CMAKE_DIR="${2}"
      echo "make all directory is $CMAKE_DIR"
      run_make_all_with_testcode 
      ;;
   -Dt) CMAKE_DIR="${2}"
      echo "make all directory is $CMAKE_DIR"
      run_make_all_with_testcode_and_debug
      ;;
   -g) run_autogenerate_clis
      ;;
   -gc) run_clean_autogenerate_clis
      ;;     
   -s) run_generate_cscope_ctags
      ;;
   -i) run_install_tools
      ;;

   *)  
   printf "`basename ${0}`:usage:
                [-C <build dir> (Generate cmake files)] 
                [-a <build dir> (Runs 'make all')]
                [-c <build dir> (Runs 'make clean')]
                [-d <build dir> (Delete the cmake directory)]   
                [-D <build dir> (Runs 'Cmake and make all with debug')]
                [-t <build dir> (Runs 'Cmake and make all with test code')]
                [-Dt <build dir> (Runs 'Cmake and make all with test code and debug')]
                [-g <build dir> (Auto-generates cli files)]
                [-gc <build dir> (Cleans auto-generated cli files)]
                [-s (Generates cscope and ctags database for searches)]
                [-i (Installs various tools required for building and development of the project. Use Only if needed)]\n"
      exit 1 # Command to come out of the program with status 1
      ;; 
esac

