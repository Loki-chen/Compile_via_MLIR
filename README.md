          include git submodule

          creat file bulid 
  <!-- 
        mkdir build
        cd build    
   -->

          echo:
          cmake -G Ninja 
          -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE 
          -DCMAKE_BUILD_TYPE:STRING=Debug 
          -S                           # source file path
          -B/build                     #bninary file path
          -G Ninja

      
          echo :
          cmake --build /home/MLIR-Compiler/build --config Debug --target all -j 40 --

