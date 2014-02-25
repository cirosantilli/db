---
title: Redis
layout: default
permalink: redis/
---

A key value server, also known as NoSQL database.

Default port is TCP/6379.

Can store complex datastructures like lists, sets and maps.

Values can have an expire time.

Once the server is running, command line REPL interface:

    redis-cli

Set value:

    SET server:name "fido"

Get value:

    GET server:name => "fido"

Increment integer (concurrency safe):

    INCR connections => 12

Delete value:

    DEL connections

