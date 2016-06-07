---
title: CASE WHEN
---

Aggregates can have an internal `CASE WHEN` condition.

Application: use multiple aggregates in a single query: <http://stackoverflow.com/questions/5462961/how-to-combine-two-count-queries-to-their-ratio>

Example: calculate the total net upvotes minus downvotes:

    CREATE TABLE votes (
        article_id INT,
        type CHAR(4)
    );

    INSERT INTO votes VALUES
        (1, 'UP'), (1, 'DOWN'), (2, 'UP'), (3, 'DOWN');

    SELECT
        article_id,
        SUM(
            CASE type
            WHEN 'UP' THEN 1
            WHEN 'DOWN' THEN -1
            END
        ) AS count
    FROM votes
    GROUP BY article_id
    ORDER BY count DESC;

    DROP TABLE votes;

This example could be simplified by using type as `INT` and upvote as `1` and downvote as `-1`, then we can just do a `SUM(type)`.
