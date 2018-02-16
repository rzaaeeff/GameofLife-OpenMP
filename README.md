# Game of Life - OpenMP
Conway's Game of Life implementation in C++ and OpenMP.

# Instructions
First, you'll need to create input file (especially for huge inputs). There's RandomFileMaker.cpp for this. To run:
```sh
$ g++ RandomFileMaker.cpp –o RandomeFileMaker
$ ./RandomFileMaker
```

and enter details...

To run serial implementation:
```sh
$ g++ -fopenmp GoLSerial.cpp -o GoLSerial
$ ./GoLSerial
```

and enter details...

To run parallel implementation:
```sh
$ g++ -fopenmp GoLParallel.cpp -o GoLParallel
$ ./GoLParallel
```

# Report
Report document can be found here: https://goo.gl/vJBXfW
