---
title: EXISTS
---

Takes a subquery and returns `TRUE` iff that subquery has at least one row, even if all its values are `NULL`.

    CREATE TABLE t(c0 INT);
    SELECT EXISTS( SELECT * FROM t );
    INSERT INTO t VALUES (NULL);
    SELECT EXISTS( SELECT * FROM t );
    DROP TABLE t;

Output:

    0
    1
