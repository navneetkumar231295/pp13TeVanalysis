# A class to hold results with statistical and systematic errors 

## The class

The class _GraphSysErr_ lives in `GraphSysErr.C`.  The class is
heavily commented and marked up for documentation using Doxygen.

## Usage and API documentation 

See the [the walk-through](Usage.md) example.

The API dpcumentation can be found at 

- http://cholmcc.gitlab.io/GraphSysErr/

## Features

- Support multiple types of systematic uncertainties
  - Uncertainties common (correlated) between all points
  - Uncertainties for each individual (uncorrelated) point 
- Support statistical errors.
- Uncertainties can be relative or absolute
- Import data sets from HepData input format
- Export data to HepData input format
  - Sets of objects can be exported as tables
  - Number of significant digits can be specified 
- Visual representation in many ways 
- Rigorous error propagation 
- Ratios, scaling, etc. of graphs 
- Combination (averages) of data sets.
- ... 

## The tests

- [`Combiner.C`](tests/Combiner.C): Stand-alone combiner
  implementation (obsolete?)
- [`DrawStyles.C`](tests/DrawStyles.C): An (X,Y) graph with
  configurable errors - Tests
- [`FlipTest.C`](tests/FlipTest.C): Test flip of GraphSysErr
- [`Load.C`](tests/Load.C): Utility to load GraphSysErr
- [`ManyTables.C`](tests/ManyTables.C): Create many tables
- [`SplitInput.C`](tests/SplitInput.C): Split input data into separate
  files
- [`TestAverage.C`](tests/TestAverage.C): Test of averaging 
- [`TestCombiner.C`](tests/TestCombiner.C): Test of combining
  measurements
- [`TestExport.C`](tests/TestExport.C): Test of exporting data to
  Durham input files
- [`TestFWHM.C`](tests/TestFWHM.C): Test to calculate
  full-width-at-half-maximum (FWHM)
- [`TestImport.C`](tests/TestImport.C): Test of importing Durham
  database input files
- [`TestJSON.C`](tests/TestJSON.C): Test JSON I/O
- [`TestLargeImport.C`](tests/TestLargeImport.C): Test import of a
  large Durham input file
- [`TestLine.C`](tests/TestLine.C): Test with a simple line
- [`TestMaker.C`](tests/TestMaker.C): A class to make tests
- [`TestMultiImport.C`](tests/TestMultiImport.C): Test of multple
  imports from a single file
- [`TestRatio.C`](tests/TestRatio.C): Test taking ratios
- [`TestRound.C`](tests/TestRound.C): Test rounding
- [`TestSignificant.C`](tests/TestSignificant.C): Test round of
  numbers
- [`TestStat.C`](tests/TestStat.C): Run tests on statistics
- [`ToJson.C`](tests/ToJson.C): Test of writing to JSON
- [`WriteTests.C`](tests/WriteTests.C): Tests of writing

## Installation

Clone from the GitLab server 

    git clone https://gitlab.com/cholmcc/GraphSysErr.git
    
or get a tar-ball, zip-archive, etc. from the same site. 

Unpack and copy the file `GraphSysErr.C` anywhere you like.

Test scripts and data is available in the distribution together with
this information.  To run a full test, do

    make test

This will run the `TestGSE.C` example, and then import the generated
`test.input` using `TestImport.C` and then re-export to `check.input`
and finally compare the two generated files. 

## License

Copyright (c) 2014 Christian Holm Christensen <cholm@nbi.dk>

The code is licensed under the LGPL-3

<!-- Local Variables: -->
<!--   mode: markdown -->
<!-- End: -->
