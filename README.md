# | piperate |

Simple UNIX tool for copying stdin to stdout while measuring and printing the
transfer rate to stderr every second.

## Quickstart

Build:

    $(CC) piperate.c -o piperate
    
Or simple:

    make

Run:

    cat /dev/urandom | ./piperate > /dev/null
    399 MB/sec
    583 MB/sec
    573 MB/sec
    581 MB/sec
    577 MB/sec
    574 MB/sec
    575 MB/sec
    585 MB/sec
