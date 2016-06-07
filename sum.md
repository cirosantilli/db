---
title: SUM
---

Sum of a column.

It is possible to use any function of the input row such as `c0 * c1`.

It is possible to make two aggregate function queries on the same `SELECT` as in `(1)`, but making a non-aggregate function query with an aggregate function query only shows the first non aggregate output as in `(2)`, which is probably not what you want.

`WHERE` is applied before aggregate functions, and selects which rows will be used for the calculation of the aggregate:

    CREATE TABLE t (c0 INT, c1 INT);
    INSERT INTO t VALUES (1, 1), (2, 4), (3, 9);
    SELECT SUM(c0) FROM t;
    SELECT SUM(c1) FROM t;
    SELECT SUM(c0 * c1) FROM t;
    SELECT SUM(c0 + c1) AS name FROM t;
    SELECT MAX(c0), SUM(c0) FROM t;     #(1)
    SELECT MAX(c0) + SUM(c0) FROM t;
    SELECT c0, SUM(c0) FROM t;          #(2)
    SELECT SUM(c0) FROM t WHERE c0 > 1;
    DROP TABLE t;

Output:

    SUM(c0)
    6

    SUM(c1)
    14

    SUM(c0 * c1)
    36

    name
    20

    MAX(c0) SUM(c0)
    3       6

    MAX(c0) + SUM(c0)
    9

    c0  SUM(c0)
    1   6

    c0  SUM(c0)
    1   5

`NULL` is treated as TODO: is giving 1 in MySQL 5.5. But I have seen many places say it could break up, like return NULL.

    CREATE TABLE t (c INT);
    INSERT INTO t VALUES (1), (NULL);
    SELECT SUM(c) FROM t;
    DROP TABLE t;
