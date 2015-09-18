---
title: GROUP BY
permalink: group-by/
---

With aggregate functions, the aggregate is calculated once on each row of unique values:

    CREATE TABLE t (c0 CHAR(1), c1 INT);
    INSERT INTO t VALUES ('a', 1), ('a', 2), ('b', 3), ('b', 3);
    SELECT c0, SUM(c1) FROM t GROUP BY c0 ORDER BY c0;
    SELECT c0, COUNT(c1) FROM t GROUP BY c0 ORDER BY c0;
    DROP TABLE t;

Output:

    c0   SUM(c1)
    a    3
    b    6

    c0   COUNT(c1)
    a    2
    b    2

## GROUP BY and JOIN

    CREATE TABLE users (id INT PRIMARY KEY, age INT);
    CREATE TABLE posts (
        id INT PRIMARY KEY,
        userid INT,
        FOREIGN KEY (userid) REFERENCES users(id)
    );
    INSERT INTO users VALUES (1, 20), (2, 20);
    INSERT INTO posts VALUES (1, 1), (2, 1), (3, 2);
    # How many posts each user has. Also show user age.
    SELECT
        users.id,
        users.age,
        COUNT(*)
    FROM
        users
    INNER JOIN
        posts
    ON
        users.id = posts.userid
    GROUP BY
        users.id
    ;
    DROP TABLE posts;
    DROP TABLE users;

Output:

    id  age  COUNT(*)
    1   20   2
    2   20   1

T-SQL forces you to put `users.age` and any non-aggregate column under `GROUP BY` as well like:

    GROUP BY
        users.id,
        users.age,

## GROUP BY multiple columns

<http://stackoverflow.com/questions/2421388/using-group-by-on-multiple-columns>

Groups by distinct *tuples*.

## Ignore GROUP BY column

All selected columns must be either grouped by, or applied an aggregate function.

How to avoid repeating columns: <http://stackoverflow.com/questions/5364429/group-by-ignoring-an-attribute>

## GROUP BY without aggregate

Without an aggregate function and for a single column, works exactly like `DISTINCT`.

But don't rely on that and prefer `DISTINCT` instead, since `GROUP BY` is designed to work with aggregates, and may have subtly different semantics: <http://stackoverflow.com/questions/164319/is-there-any-difference-between-group-by-and-distinct>

In particular, T-SQL raises an error if you try to do that.

    CREATE TABLE t (c0 CHAR(1), c1 INT);
    INSERT INTO t VALUES ('a', 1), ('a', 2), ('b', 3), ('b', 3);
    SELECT * FROM t GROUP BY c0 ORDER BY c0,c1;
    SELECT * FROM t GROUP BY c1 ORDER BY c0,c1;
    #TODO what happens on this one? same as above?
    SELECT * FROM t GROUP BY c0,c1 ORDER BY c0,c1;
    DROP TABLE t;

Output:

    c0   c1
    a    1
    b    3

    c0   c1
    a    1
    a    2
    b    3

    c0   c1
    a    1
    a    2
    b    3
