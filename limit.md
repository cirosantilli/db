---
title: LIMIT
---

Limit the number of outputs.

    CREATE TABLE t (c INT);
    INSERT INTO t VALUES (0), (1), (2);
    SELECT * FROM t ORDER BY c ASC LIMIT 2;
    DROP TABLE t;

Output:

    c
    0
    1
