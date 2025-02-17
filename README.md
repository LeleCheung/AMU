# AMU
This repo includes XiangShan's matrix unit AMU.


## Unit-Test with Verilator

* First prepare environment with verilator/mill.
* `make emu [EMU_TRACE=1]`
* `./build/emu [-C MAX_CYCLES] [-O MAX_OPERATIONS] [--dump-wave] [-b begin_dump] [-e end_dump]`
* CAUTION: `--dump-wave` is a must if `EMU_TRACE=1` is set, otherwise coredump will occur.

Others:

* `make clean` to clean build dir.
* `make clean-softfloat` to clean softfloat compile dir.


## Matrix Testcase generation

* First change directory to `testcase`
* `bash init.sh` to initialize the testcase generation environment.
* `bash cmake.sh` to generate the testcase.

Others:

* `bash clean.sh` to clean the testcase.


## Scripts for Parallel Emu & Log Analysis

* `make emu EMU_TRACE=1`
* `cd scripts`
### Run emu parallelly, logs are in ./log, for exeample, run 10 emu with 100 oprations each.
* `python3 emu_parallel.py 10 100`
### Analyse logs, the number of error logs or empty logs, all error logs are summarized in ./log/logs.log.
* `python3 log_analyse.py`