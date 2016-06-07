---
title: SQLite Cheat
---

File based.

Not intended for production servers, but can useful for testing and use in user applications.

This type of database is called an <https://en.wikipedia.org/wiki/Embedded_database>

One of the most deployed software in the world.

If you ever think something like: "hey, I'd like to store this hash map persistently to disk", then you should try this.

## Versions

As of 2015, there are two major versions: 2 and 3.

On Ubuntu 15.10, you need to specify the executable name:

    sqlite

is version 2, and does not open version 3 databases properly:

    sqlite3

It is likely a good idea to use `sqlite3` always for new applications.

## Create a database

    sqlite3 my.db

Now as soon as you create a table the db file is created:

    CREATE TABLE t (i INTEGER);

## Invocation

## CLI interface

Run command on a given database:

    sqlite3 db.sqlite3 'select * from table;'

### attach

### Create multiple databases

    sqlite3 a.db

Then:

    ATTACH DATABASE 'b.db' as b;

`b` is the name that shows on `.databases`, and is used to refer to it:

    SELECT * FROM b.t;

This creates the `b.db` file.

#### Schema of databases attached with attach

Impossible: <http://stackoverflow.com/questions/82875/how-do-i-list-the-tables-in-a-sqlite-database-file>

### Database name

The initial database is always called `main`. `ATTACH DATABASE` can be given arbitrary names:

- <http://stackoverflow.com/questions/10845974/how-to-change-database-name-in-sqlite>
- <http://stackoverflow.com/questions/7313190/can-i-name-sqlite-databases>

### out

Export database data.

#### Export to CSV

<http://stackoverflow.com/questions/75675/how-do-i-dump-the-data-of-some-sqlite3-tables>

## Data types

### Integers

<http://stackoverflow.com/questions/7337882/sqlite-and-integer-types-int-integer-bigint>

### Date

Current time:

- <http://stackoverflow.com/questions/15473325/inserting-current-date-and-time-in-sqlite-database>
- <http://stackoverflow.com/questions/200309/sqlite-database-default-time-value-now>

## Dot commands

### help

List special `.` commands:

    .help

### exit

    .exit

### databases

List databases and their paths.

    .databases

### tables

List tables:

    .tables

### schema

Get the schema of all tables with their creation query:

    .schema

### mode

### import

#### Import CSV file

<https://stackoverflow.com/questions/1045910/how-can-i-import-load-a-sql-or-csv-file-into-sqlitevu>:

    printf '1,2\n3,4\n' > a.cvs

Then:

    CREATE TABLE t (i INTEGER, j INTEGER)
    .mode csv table_name
    .import a.cvs table_name

Apparently does not deal with quotes.

## FULLTEXT

Only available as extensions

- <https://sqlite.org/fts5.html>
- <https://www.sqlite.org/fts3.html>

## Types

Types are more flexible than MySQL: they are treated more like suggestions, and can increase in size "dynamically".

## Internals

Written in C.

### Source code

<http://www.sqlite.org/download.html>

Version controlled with Fossil... which uses SQLite on the backend, and was written by the same person who wrote SQLite.

He is openly anti-git: <https://www.youtube.com/watch?v=ghtpJnrdgbo>

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

### License

Public domain! WOW.

### Format

The format is documented and fixed.

### Bytecode

It compiles the text input into a bytecode, and then runs it.

<https://www.quora.com/Why-does-SQLite-compile-queries-into-bytecode-to-execute-in-a-virtual-machine-instead-of-using-composable-operators-like-scan-join-aggregate-etc-which-is-probably-more-common-in-other-databases-implementations>

### Creator

Richard Hipp https://en.wikipedia.org/wiki/D._Richard_Hipp

He is a pious Christian it seems: https://twitter.com/drichardhipp

You gotta love his Southern accent.

### Vs MySQL

- <http://stackoverflow.com/questions/4813890/sqlite-or-mysql-how-to-decide>
- <http://stackoverflow.com/questions/3630/sqlite-vs-mysql>
- <https://www.youtube.com/watch?v=Jib2AmRb_rk>

## Index on large database

Insertion becomes really slow, I could not deal with 10M rows:

- <http://stackoverflow.com/questions/6808138/sqlite-how-to-create-indexes-faster-in>
- <http://stackoverflow.com/questions/15778716/sqlite-insert-speed-slows-as-number-of-records-increases-due-to-an-index>

## ALTER TABLE

### DROP COLUMN

Nope: <http://stackoverflow.com/questions/8442147/how-to-delete-or-add-column-in-sqlite>
