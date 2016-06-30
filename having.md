---
title: HAVING
---

<http://stackoverflow.com/questions/287474/whats-the-difference-between-having-and-where>

`HAVING` is similar to `WHERE`, but:

-   `HAVING` can refer to columns generated via `AS` or aggregate functions.

        CREATE TABLE t (c0 INT, c1 INT);
        INSERT INTO t VALUES (1, 1), (2, 4), (3, 9);
        SELECT c0+c1 AS sum FROM t HAVING sum > 3 ORDER BY sum;
        DROP TABLE t;

    Output:

        sum
        6
        12

-   `HAVING` is applied after `GROUP BY` while `WHERE` is applied before.

        CREATE TABLE t (c0 CHAR(1), c1 INT);
        INSERT INTO t VALUES ('a', 1), ('a', 2), ('b', 3), ('b', 3);
        SELECT c0, SUM(c1) AS sum FROM t GROUP BY c0 HAVING sum > 4;
        DROP TABLE t;

    Output:

        c0   sum
        b    6
