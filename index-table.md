---
title: INDEX
permalink: db/mysql/index-table/
---

Same as `KEY`.

Implied by `UNIQUE`.

Make MySQL create an index for the given tables.

`INDEX` does not imply neither `UNIQUE` nor `NOT NULL`.

    CREATE TABLE t (
        id INT,
        val VARCHAR(16),
        INDEX (id)
    );
    INSERT INTO t VALUES (1, 'one');
    INSERT INTO t VALUES (1, 'one2');
    INSERT INTO t VALUES (2, 'two');
    INSERT INTO t VALUES (NULL, 'null');
    # Faster because of the index.
    SELECT * FROM t WHERE id = 1;
    DROP TABLE t;

Output:

    1     one
    1     one2

Note that there were no errors.

It is also common to make the key `NOT NULL`, which helps MySQL do certain optimizations.

## Multi-column index

TODO check all of this section.

An index can span multiple columns `c0` and `c1`, in which case it will be very efficiently used for `WHERE c0 AND c1` queries, but not on `WHERE c0` queries alone:

    CREATE TABLE t (
        id INT,
        val VARCHAR(16),
        INDEX (id, val)
    );
    INSERT INTO t VALUES (1, 'one');
    INSERT INTO t VALUES (1, 'one2');
    INSERT INTO t VALUES (2, 'two');
    # Faster because of the index.
    SELECT * FROM t WHERE id = 1 AND val = 'one2';
    EXPLAIN EXTENDED SELECT * FROM t WHERE id = 1 AND val = 'one2';
    EXPLAIN EXTENDED SELECT * FROM t WHERE val = 'one2' AND id = 1;
    DROP TABLE t;

Output (selection):

    1     one2

    +-------------+------+---------------+------+---------+-------------+----------+--------------------------+
    | select_type | type | possible_keys | key  | key_len | ref         | filtered | Extra                    |
    +-------------+------+---------------+------+---------+-------------+----------+--------------------------+
    | SIMPLE      | ref  | id            | id   | 24      | const,const |   100.00 | Using where; Using index |
    +-------------+------+---------------+------+---------+-------------+----------+--------------------------+

    +-------------+------+---------------+------+---------+-------------+----------+--------------------------+
    | select_type | type | possible_keys | key  | key_len | ref         | filtered | Extra                    |
    +-------------+------+---------------+------+---------+-------------+----------+--------------------------+
    | SIMPLE      | ref  | id            | id   | 24      | const,const |   100.00 | Using where; Using index |
    +-------------+------+---------------+------+---------+-------------+----------+--------------------------+

TODO: understand `EXPLAIN` output in relation to indexes.

Two separate indexes on individual columns `c0` and `c1` can be both used to speed up a `WHERE c0 c1` query by the MySQL optimizer, but this is a complex optimization (think in terms of the B-tree) and a multi-column `INDEX` is generally faster.

<http://dba.stackexchange.com/questions/24489/how-are-multiple-indexes-used-in-a-query-by-mysql>

    CREATE TABLE t (
        id INT,
        val VARCHAR(16),
        INDEX (id),
        INDEX (val)
    );
    INSERT INTO t VALUES (1, 'one');
    INSERT INTO t VALUES (1, 'one2');
    INSERT INTO t VALUES (2, 'two');
    # Faster because of the index.
    SELECT * FROM t WHERE id = 1 AND val = 'one2';
    EXPLAIN SELECT * FROM t WHERE id = 1 AND val = 'one2';
    EXPLAIN SELECT * FROM t WHERE val = 'one2' AND id = 1;
    DROP TABLE t;

## KEY

Same as `INDEX`.

## Add index after table is created

Either of:

    ALTER TABLE tbl ADD INDEX col (index_name);
    CREATE INDEX index_name ON your_table_name(column_name) USING HASH;

`CREATE INDEX` seems to be the most portable.
