---
title: JOIN
permalink: db/mysql/join/
---

Make a query result that uses rows from multiple tables.

{{ site.toc }}

## INNER JOIN

Only rows present on both are considered (intersection).

A very common usage is to join foreign key from one table to ids of the other.

    CREATE TABLE names (i INT, name VARCHAR(16));
    CREATE TABLE squares (i INT, square INT);
    INSERT INTO names   VALUES (0, 'zero'), (1, 'one'),         (3, 'three');
    INSERT INTO squares VALUES (0, 0),                  (2, 4), (3, 9);
    SELECT names.name, squares.square
        FROM names
        INNER JOIN squares
        ON names.i = squares.i
        ORDER BY squares.square, names.name;
    # Same as above by symmetry.
    SELECT names.name, squares.square
        FROM squares
        INNER JOIN names
        ON names.i = squares.i
        ORDER BY squares.square, names.name;
    DROP TABLE names, squares;

Output: 2x:

    name    square
    zero    0
    three   9

`1` and `2` are not there since they are only present on one of the tables.

Every possible match is done, so the new table is up to $n*m$ as large:

    CREATE TABLE names (i INT, name VARCHAR(16));
    CREATE TABLE roots (i INT, root INT);
    INSERT INTO names VALUES (1, 'one'), (1, 'one again');
    INSERT INTO roots VALUES (1, -1),    (1, 1);
    SELECT names.name, roots.root
        FROM names
        INNER JOIN roots
        ON names.i = roots.i
        ORDER BY roots.root, names.name;
    DROP TABLE names, roots;

Output:

    name        root
    one         -1
    one again   -1
    one         1
    one again   1

`INNER JOIN` is symmetric, unlike `LEFT JOIN` in the `NULL` case:

    CREATE TABLE names (i INT, name VARCHAR(16));
    CREATE TABLE roots (i INT, root INT);
    INSERT INTO names VALUES (1, 'one'), (1, 'one again');
    INSERT INTO roots VALUES (1, -1),    (1, 1);
    SELECT names.name, roots.root
        FROM names
        INNER JOIN roots
        ON names.i = roots.i
        ORDER BY roots.root, names.name;
    # Same as above by symmetry:
    SELECT names.name, roots.root
        FROM roots
        INNER JOIN names
            ON names.i = roots.i
        ORDER BY roots.root, names.name;
    DROP TABLE names, roots;

Output: 2x:

    name        root
    one         -1
    one again   -1
    one         1
    one again   1

Multiple joins:

    CREATE TABLE countrys (id INT,                 name VARCHAR(16));
    CREATE TABLE states   (id INT, country_id INT, name VARCHAR(16));
    CREATE TABLE citys    (id INT, state_id   INT, name VARCHAR(16));
    INSERT INTO countrys VALUES (1, 'a'), (2, 'b'), (3, 'c');
    INSERT INTO states   VALUES (1, 1, 'aa'), (2, 1, 'ab'), (3, 2, 'ba');
    INSERT INTO citys    VALUES (1, 1, 'aaa'), (2, 1, 'aab'), (3, 3, 'baa');
    SELECT countrys.name AS `countrys.name`, citys.name AS `citys.name`
        FROM countrys
        INNER JOIN states ON states.country_id = countrys.id
        INNER JOIN citys  ON citys.state_id    = states.id
        ORDER BY countrys.name, citys.name;
    DROP TABLE countrys, states, citys;

Output:

    countrys.name    citys.name
    a                aaa
    a                aab
    b                baa

### Select all columns from one table

<http://stackoverflow.com/questions/3492904/mysql-select-all-columns-from-one-table-and-some-from-another-table>

### Operate before the JOIN

E.g.: you want to `LIMIT` on the first table, not on the join.

Seems to require a subquery:

<http://stackoverflow.com/questions/7405432/can-you-apply-limit-on-mysql-before-left-join-another>

### ON vs WHERE

Multiple `ON` conditions can be used instead of `WHERE` clauses.

The behavior is the same except for edge cases: <http://stackoverflow.com/a/7967048/895245>.

In theory `ON` is more efficient, but because of optimizers in practice both are almost always the same speed.

Because of the slim possibilities of slowdown and the edge case, always use multiple `ON` conditions instead of `WHERE`:

    CREATE TABLE names (i INT, name VARCHAR(16));
    CREATE TABLE squares (i INT, square INT);
    INSERT INTO names   VALUES (0, 'zero'), (1, 'one'),         (3, 'three');
    INSERT INTO squares VALUES (0, 0),                  (2, 4), (3, 9);
    SELECT names.name, squares.square
        FROM names
        INNER JOIN squares
        ON names.i = squares.i
        AND squares.square < 5;
    DROP TABLE names, squares;

Output:

    name    square
    zero    0

## LEFT JOIN

Consider all rows of the left (first) table, even if they have no match on the second table,

If the second table has no match, its columns receive `NULL`.

As a result, all rows of the left table will generate at least one row on the joined table.

If the left row has at least one match, the `NULL` row is not generated:

    CREATE TABLE names (i INT, name VARCHAR(16));
    CREATE TABLE squares (i INT, square INT);
    INSERT INTO names VALUES (0, 'zero'), (0, 'zero again'), (1, 'one'), (3, 'three');
    INSERT INTO squares VALUES (0, 0), (0, 0), (2, 4), (3, 9);
    SELECT names.name, squares.square
        FROM names
        LEFT JOIN squares
        ON names.i = squares.i
        ORDER BY names.i, names.name, squares.square;
    DROP TABLE names, squares;

Output:

    name        square
    zero        0
    zero        0
    zero again  0
    zero again  0
    one         NULL
    three       9

`one` is present because it is on the left table.
`two` is not because it is on the right table.

Since `one` has no corresponding square, the square is `NULL`.

### LEFT JOIN on SELECT

This syntax is being generally deprecated: use `LET JOIN` instead: <http://stackoverflow.com/questions/894490/sql-left-join-vs-multiple-tables-on-from-line>

Multiple tables:

    CREATE TABLE t  (i INT);
    CREATE TABLE t2 (j INT);
    INSERT INTO t VALUES  (1), (3);
    INSERT INTO t2 VALUES (2), (4);
    SELECT * FROM t, t2 ORDER BY t.i, t2.j;
    DROP TABLE t, t2;

Output is the Cartesian product of the two tables:

    i   j
    1   2
    1   4
    3   2
    3   4

Must include all the table names to be used, or error:

    CREATE TABLE t  (i INT);
    CREATE TABLE t2 (j INT);
    INSERT INTO t VALUES  (1), (3);
    INSERT INTO t2 VALUES (2), (4);
    SELECT * FROM t ORDER BY t.i, t2.j;
    DROP TABLE t, t2;

Output:

    ERROR 1054 (42S22): Unknown column 't2.j' in 'order clause'

Table names are omitted from the headers. To disambiguate use `AS`.

## RIGHT JOIN

    CREATE TABLE names (i INT, name VARCHAR(16));
    CREATE TABLE squares (i INT, square INT);
    INSERT INTO names VALUES (0, 'zero'), (1, 'one'), (3, 'three');
    INSERT INTO squares VALUES (0, 0), (2, 4), (3, 9);
    SELECT names.name, squares.square
        FROM names
        RIGHT JOIN squares
        ON names.i = squares.i;
        ORDER BY names.name, squares.square;
    DROP TABLE names, squares;

Output:

    name    square
    zero    0
    NULL    4
    three   9

## OUTER JOIN

`{LEFT|RIGHT} OUTER JOIN` is the same as `LEFT JOIN`.

`FULL OUTER JOIN` (select at least one item from both sides) is not present as of MySQL 5.5, but can be emulated with `UNION`: <http://stackoverflow.com/questions/7978663/mysql-full-join/7978665#7978665>.

