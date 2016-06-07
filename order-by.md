---
title: ORDER BY
---

Order select output by one or more columns.

    CREATE TABLE t (c0 INT, c1 INT);
    INSERT INTO t VALUES (0, 1), (0, 0), (1, 1), (2, 0);
    # Partially unspecified:
    SELECT * FROM t ORDER BY c0;
    SELECT * FROM t ORDER BY c0*c1;
    # Fully specified:
    SELECT * FROM t ORDER BY c0,c1;
    SELECT c0 + c1 AS sum FROM t ORDER BY sum;
    DROP TABLE t;

Possible output (up to reordering unspecified orders):

    c0   c1
    0    1
    0    0
    1    1
    2    0

    c0   c1
    0    1
    0    0
    2    0
    1    1

    c0   c1
    0    0
    0    1
    1    1
    2    0

    sum
    0
    1
    2
    2

If not used, the orders are unspecified. Almost all `SELECT` statements done in practice will have specified order.

This query can be optimized by B-Tree indexes on MySQL and PostgreSQL.
