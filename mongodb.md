---
title: MongoDB
permalink: mongodb/
---

NoSQL database: looks like manipulating dictionaries / objects in Python / Ruby.

No fixed table format: everything is a dictionary.

Apparently, MongoDB and Redis are comparable tools,
but MongoDB is slower and more flexible.

## Sources

Manual: <http://docs.mongodb.org/manual/>

## Command line client

CLI client:

    mongo

## Server

By default runs on port `27017`.

## help

Get general help:

    help

Get help on specific classes:

    db.help()
    db.collection0.help()

## Database

List databases:

    show db

Sample output:

    local	0.078125GB
    test	0.203125GB

Set current DB:

    use test

Get current database name:

    db

Sample output:

    test

## Collection

Collections are the analogue of relational tables of a database.

Create a new collection called `collection0` in the current DB `test` and insert some values into it:

    db.collection0.insert({ x:1, x2:1 })
    db.collection0.insert({ x:1, x2:2 })
    db.collection0.insert({ x:2 })
    db.collection0.insert({ y:3 })
    db.collection0.insert({ s:"s" })

Note how you don't have to create a database table as in traditional relational databases like MySQL.

List all collections on current DB:

    show collections

Sample output:

    collection0
    system.indexes

`system.indexes` is present by default.

List entire collection:

    db.collection0.find()

Sample output:

    { "_id" : ObjectId("5488607f9a6f3a85128cd8be"), "x" : 1, "x2" : 1 }
    { "_id" : ObjectId("5488607f9a6f3a85128cd8bf"), "x" : 1, "x2" : 2 }
    { "_id" : ObjectId("5488607f9a6f3a85128cd8c0"), "x" : 2 }
    { "_id" : ObjectId("5488607f9a6f3a85128cd8c1"), "y" : 3 }
    { "_id" : ObjectId("5488607f9a6f3a85128cd8c2"), "s" : "s" }

Find elements where `x = 1`:

    db.collection0.find({ x: 1 })

Output:

    { "_id" : ObjectId("5488607f9a6f3a85128cd8be"), "x" : 1, "x2" : 1 }
    { "_id" : ObjectId("5488607f9a6f3a85128cd8bf"), "x" : 1, "x2" : 2 }
