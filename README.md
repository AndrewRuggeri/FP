# Finger Print Enhancement
TODO: overview


## Executables
There are two executables that get build within this code base.
### FP
This a POSIX only executable

#### Arguments
-id : input directory
-od : ouput directory
-n  : nominal test

### Filter
Testing application, which can be used to test specific filters or filter chains


## Build instructions
building is handled using cmake, which will build both executables (unless on windows)
```$bash
mkdir build
cd build
cmake ..
make
```

### ARM
ARM specific compiler flags for a cortex-A15 can be enabled wiht the following cmake argument
```$bash
cmake .. -DARMBUILD:BOOL=true
```

