---
title: COUNT
---

Return the number of non `NULL` entries of a column.

`COUNT(*)` counts the total number of entries of a table, including entries that only contain `NULL` values.

    CREATE TABLE t (c0 INT, c1 INT);
    INSERT INTO t VALUES (0, 0), (1, NULL), (NULL, NULL);
    SELECT COUNT(c0) FROM t;
    SELECT COUNT(c1) FROM t;
    SELECT COUNT(*) FROM t;
    DROP TABLE t;

Output:

    COUNT(c0)
    2

    COUNT(c1)
    1

    COUNT(*)
    3
