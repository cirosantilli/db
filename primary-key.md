---
title: PRIMARY KEY
permalink: primary-key/
---

Implies the behaviors of `UNIQUE` and `NOT NULL`, that is:

- enforces that there are no duplicates.
- implies `NOT NULL`.
- creates an index.

Unlike `UNIQUE`, only one column per table can be marked as `PRIMARY KEY`.

Example:

    # ERROR: can only be used for a single col
    CREATE TABLE t (
        id INT PRIMARY KEY,
        val VARCHAR(16) PRIMARY KEY
    );
    CREATE TABLE t (
        id INT PRIMARY KEY,
        val VARCHAR(16)
    );
    INSERT INTO t VALUES (1, 'one');
    # ERROR: no dupes
    INSERT INTO t VALUES (1, 'one2');
    # ERROR: cannot be null
    INSERT INTO t VALUES (NULL, 'null');
    SELECT * FROM t;
    DROP TABLE t;

