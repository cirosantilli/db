---
title: MongoDB
---

NoSQL database: looks like manipulating dictionaries / objects in Python / Ruby.

No fixed table format: everything is a dictionary.

Apparently, MongoDB and Redis are comparable tools, but MongoDB is slower and more flexible.

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

## Database operations

List databases <http://stackoverflow.com/questions/25947929/how-to-list-all-databases-in-the-mongo-shell>:

    show dbs

Sample output:

    local	0.078125GB
    test	0.203125GB

The `local` database contains metadata: <https://docs.mongodb.org/v3.0/reference/local-database/>.

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

List all collections on current DB <http://stackoverflow.com/questions/8866041/how-to-list-all-collections-in-the-mongo-shell>:

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

### remove

Clear a collection;

    db.collection0.remove({})

### _id

<https://docs.mongodb.org/manual/reference/object-id/>

    db.collection0.insert({ x:1, x2:1 })

### find

Limit columns returned:

    db.collection0.insert({x:1, y:2})
    db.collection0.find({})
    // { "_id" : ObjectId("568d2cdfbc7a812650566d04"), "x" : 1, "y" : 2 }
    db.collection0.find({}, {})
    // { "_id" : ObjectId("568d2cdfbc7a812650566d04"), "x" : 1, "y" : 2 }
    db.collection0.find({}, {x:true})
    // { "_id" : ObjectId("568d2cdfbc7a812650566d04"), "x" : 1 }
    db.collection0.find({}, {x:true, _id:false})
    // { "x" : 1 }
    db.collection0.remove({})

Note how `_id` is included by default even it it is not listed as `true`: we must explicitly exclude it for it to disappear.

#### Query

TODO: what can be the query?

-   `{}`: JavaScript like object

    May contain operators like:

        db.collection0.insert({x:1})
        db.collection0.insert({x:2})
        db.collection0.find({x: {$gt: 1}}, {_id:false})
        // { "x" : 2 }
        db.collection0.remove({})

-   `ObjectId`

    <http://stackoverflow.com/questions/8233014/how-do-i-search-for-an-object-by-its-objectid-in-the-console>

    Example:

        db.collection0.insert({x:1, y:2})
        db.collection0.insert({x:1, y:2})
        db.collection0.find()
        // { "_id" : ObjectId("568d308e312346e21beb91ce"), "x" : 1, "y" : 2 }
        db.collection0.find(ObjectId("568d308e312346e21beb91ce"))
        // { "_id" : ObjectId("568d30ac312346e21beb91cf"), "x" : 1, "y" : 2 }
        // { "_id" : ObjectId("568d308e312346e21beb91ce"), "x" : 1, "y" : 2 }
        db.collection0.remove({})

### update

The element finding is the same as for `find`.

    db.collection0.insert({x:1, y:1})
    db.collection0.insert({x:2, y:4})
    db.collection0.update({x:1}, {$set: {y:2}})
    db.collection0.find({}, {_id:false})
    // { "x" : 1, "y" : 2 }
    // { "x" : 2, "y" : 4 }
    db.collection0.find({}, {_id:false})
    db.collection0.remove({})

How the update is done is specified by a [Field Update Operator](https://docs.mongodb.org/manual/reference/operator/update-field/).

Update multiple fields at once requires `{multi:true}`: <http://stackoverflow.com/questions/1740023/mongodb-how-to-update-multiple-documents-with-a-single-command>

    db.collection0.insert({x:1})
    db.collection0.insert({x:2})
    db.collection0.update({}, {$mul: {x:-1}}, {multi:true})
    db.collection0.find({}, {_id:false})
    // { "x" : -1 }
    // { "x" : -2 }
    db.collection0.remove({})

#### inc

    db.collection0.insert({x:1, y:1})
    db.collection0.update({}, {$inc: {x:1}})
    db.collection0.find({}, {_id:false})
    // { "x" : 2, "y" : 1 }
    db.collection0.remove({})

## Cursor object

The result of `find()` operations.

### sort

    db.collection0.insert({x:1, y:-1})
    db.collection0.insert({x:2, y:-2})
    db.collection0.insert({x:2, y:-3})

    // Asc.
    db.collection0.find({}, {_id:false}).sort({x:1})
    // { "x" : 2, "y" : -3 }
    // { "x" : 2, "y" : -2 }
    // { "x" : 1, "y" : -1 }

    // Desc.
    db.collection0.find({}, {_id:false}).sort({x:-1})
    // { "x" : 2, "y" : -3 }
    // { "x" : 2, "y" : -2 }
    // { "x" : 1, "y" : -1 }

    // Order matters: syntax is not analogous to unordered JavaScript objects.
    // http://stackoverflow.com/questions/5525795/does-javascript-guarantee-object-property-order
    // Compare to APIs like Meteor http://docs.meteor.com/#/full/sortspecifiers
    db.collection0.find({}, {_id:false}).sort({x:1, y:1})
    // { "x" : 1, "y" : -1 }
    // { "x" : 2, "y" : -3 }
    // { "x" : 2, "y" : -2 }
    db.collection0.find({}, {_id:false}).sort({y:1, x:1})
    // { "x" : 2, "y" : -3 }
    // { "x" : 2, "y" : -2 }
    // { "x" : 1, "y" : -1 }

    db.collection0.remove({})

### limit

### skip

    db.collection0.insert({x:1})
    db.collection0.insert({x:2})
    db.collection0.insert({x:3})
    db.collection0.insert({x:4})
    db.collection0.find({},{_id:false}).sort({x:1}).skip(1).limit(2)
    // { "x" : 2 }
    // { "x" : 3 }
    db.collection0.remove({})

## assert

## Bibliography

Manual: <http://docs.mongodb.org/manual/>

## console.log on server

<https://forums.meteor.com/t/seeing-console-log-server-side-output/1130>
