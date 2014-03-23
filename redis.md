---
title: Redis
layout: default
permalink: redis/
---

A key value server, also known as NoSQL database.

Default port is TCP/6379.

Can store complex data structures like lists, sets and maps.

Values can have an expire time.

Once the server is running, command line REPL interface:

    redis-cli

#Things Redis can't do that RDMSs can

As far as we can tell:

- `SUM`

#SET and GET

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

#INCR

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

#DELETE

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

#Data types

##String

Base data type.

##Integer

There is no integer data type, only strings that can be converted to integers or not.

##List

    LPUSH list a
    LPUSH list b
    RPUSH list c

Get entire list:

    LRANGE list 0 -1

Output:

    1) "b"
    2) "a"
    3) "c"
