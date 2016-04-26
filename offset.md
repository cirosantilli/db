---
title: OFFSET
---

Which 1-based Nth row will be the first to show on the output.

Useful for paging in addition to `LIMIT`.

    CREATE TABLE t (c INT);
    INSERT INTO t VALUES (0), (1), (2);
    SELECT * FROM t LIMIT 1;
    SELECT * FROM t ORDER BY c ASC LIMIT 1 OFFSET 1;
    DROP TABLE t;

Output:

    c
    1

Mandatory to use `LIMIT` with it: <http://stackoverflow.com/questions/255517/mysql-offset-infinite-rows>

`LIMIT` must come before `OFFSET`.
