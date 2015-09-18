---
title: SQLite Cheat
permalink: sqlite/
---

File based.

Not intended for production servers, but can useful for testing and use in user applications.

## Internals

Written in C.

### Source code

<http://www.sqlite.org/download.html>

Version controlled with Fossil... which uses SQLite on the backend, and was written by the same person who wrote SQLite.

And on top of that, you need Fossil to generate some build files... for the Git repository this can be achieved with:

    git log -1 --format=format:%ci%n | sed -e 's/ [-+].*$//;s/ /T/;s/^/D /' > manifest
    echo $(git log -1 --format=format:%H) > manifest.uuid
    make

So here is the most starred GitHub unofficial mirror: <https://github.com/mackyle/sqlite>

Or you can create some courage and deal with Fossil:

    sudo apt-get install fossil
    mkdir sqlite
    cd sqlite
    fossil clone http://www.sqlite.org/cgi/src/doc/trunk a
    fossil open a
    rm a

To run the tests you need Tcl development files. In Ubuntu 14.04:

    sudo apt-get install tcl8.6-dev

TODO: what then? `tcl.h` is not in the path, and adding it with `CPATH` gives a ton of link errors. 
