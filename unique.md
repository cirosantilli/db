---
title: UNIQUE
permalink: unique/
---

Enforces uniqueness of each value of a row, except for `NULL` which may appear several times.

This can only be maintained efficiently if an index is created, so `UNIQUE` also creates an index, thus implying `INDEX`:

    CREATE TABLE t (a INT UNIQUE, b INT);
    INSERT INTO t VALUES (0, 0), (1, 0);
    INSERT INTO t VALUES (0, 1);
    SELECT * FROM t;
    DROP TABLE t;

Output:

    ERROR 1062 (23000): Duplicate entry '0' for key 'a'
    0    0
    1    0

Error can be ignored with `INSERT IGNORE`.

Unique pairs:

    CREATE TABLE t (
        a INT,
        b INT,
        UNIQUE INDEX (a, b)
    );
    INSERT INTO t VALUES (0, 0), (0, 1), (1, 0);
    INSERT INTO t VALUES (0, 1);
    SELECT * FROM t;
    DROP TABLE t;

