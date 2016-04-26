---
title: Redis Cheat
---

A key value server, also known as NoSQL database.

Default port is TCP/6379.

Values can have an expire time.

Once the server is running, command line REPL interface:

    redis-cli

# vs MySQL

- <http://stackoverflow.com/questions/3966689/when-to-use-redis-instead-of-mysql-for-php-applications>
- <http://www.mysqlperformanceblog.com/2009/08/27/looking-at-redis/>

TODO check everything bellow, in particular if MySQL can do each of those things.

Can store complex data structures like lists, sets and maps, MySQL only represents those structures indirectly with tables and columns.

Loads all of it's data on RAM, persists it by default to disk. Therefore faster than MySQL which always reads from disk TODO check but it can store much less data. TODO possible to not load everything on RAM?

Only saves modifications to disk from time to time, thus lower durability, and greater performance.

Pipelining support: multiple operations on a single HTTP request.

# Things Redis can't do that RDMSs can

As far as we can tell:

- `SUM`

# SET and GET

Set value to string:

    SET key "val space"

Get value:

    GET key

Output:

    "val space"

No quotes:

    SET key val
    GET key

Output:

    "val"

Only works for value without spaces:

    SET key val space

Output:

    (error) ERR syntax error

# INCR

Increment integer (concurrency safe):

    SET key 0
    INCR key
    GET key

Output:

    "1"

Only works for integers:

    SET key a
    INCR key

Output:

    (error) ERR value is not an integer or out of range

# DELETE

Undefined key returns nil:

    GET undefined_key

Output:

    (nil)

Delete value:

    SET key
    DEL key
    GET key

Output:

    (nil)

# Data types

## String

Base data type.

## Integer

There is no integer data type, only strings that can be converted to integers or not.

## List

    LPUSH list a
    LPUSH list b
    RPUSH list c

Get entire list:

    LRANGE list 0 -1

Output:

    1) "b"
    2) "a"
    3) "c"
