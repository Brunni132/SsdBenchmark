# SsdBenchmark
A quick and dirty benchmark for SSD in real world (reading/writing files from a C program)

Benchmarks like CrystalDisk return waaay too optimistic data because of the write cache in SSD. A write speed around 300 MB/sec is probably more realistic for a laptop, even though many will return 2 GB/sec with various benchmarks. Same with read speed. In practise even with a good CPU it's unlikely that you will get read speeds beyond 3 GB/sec (as of writing this, in 2022).

This is meant to create a real world use case. Do it with a file size that's way bigger than the internal write cache of your SSD (in my experience it's usually below 1 GB) and higher than the amount of RAM you have.

Use this for a 20 GB test file:

time ssdbenchmark w test.bin 1024 20

Then to measure the time to read it:

time ssdbenchmark r test.bin 4

Note that bigger blocks for reading doesn't necessarily measure real world performance. In this case 4 MB blocks is a good compromise.

You might want to create 2 files, bigger than the RAM you have, and do the read test two times with each file, else you might get results that are too good to be true.
