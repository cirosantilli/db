---
title: MongoDB
layout: default
permalink: mongodb/
---

NoSQL database: looks like manipulating dicts / objects in Python / Ruby.

No fixed table format: everything is a dict.

CLI client:

    mongo

Sample session:

    j = { name : "mongo" }
    k = { x : 3 }

    db.testData.insert( j )
    db.testData.insert( k )

    show collections

Output:

    system.indexes
    testData
