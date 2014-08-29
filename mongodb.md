---
title: MongoDB
permalink: mongodb/
---

NoSQL database: looks like manipulating dictionaries / objects in Python / Ruby.

No fixed table format: everything is a dictionary.

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
