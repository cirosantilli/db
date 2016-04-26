---
title: FOREIGN KEY
---

Constraint that states that a row points to `PRIMARY KEY` of another table.

As of 5.5, this feature is not available on most engine types, but available on the default InnoDB.

    CREATE TABLE authors (
        id INT PRIMARY KEY AUTO_INCREMENT,
        last_name VARCHAR(255)
    );
    CREATE TABLE books (
        id INT PRIMARY KEY AUTO_INCREMENT,
        title VARCHAR(255),
        author_id INT,
        FOREIGN KEY (author_id) REFERENCES authors(id)
    );
    DROP TABLE books, authors;

Pointing to an `UNIQUE` row is also possible:

    CREATE TABLE authors (
        id INT UNIQUE,
        last_name VARCHAR(255)
    );
    CREATE TABLE books (
        id INT PRIMARY KEY AUTO_INCREMENT,
        title VARCHAR(255),
        author_id INT,
        CONSTRAINT author_id_fk FOREIGN KEY (author_id) REFERENCES authors(id)
    );
    DROP TABLE books, authors;

but is not usually a good design choice.

Both tables should use the same engine. If this is not the case, the command may not generate any errors, but this is not a good idea since different engines treat foreign keys differently.

    CREATE TABLE authors (
        id INT PRIMARY KEY,
        last_name VARCHAR(255)
    ) ENGINE=InnoDB;
    CREATE TABLE books (
        id INT PRIMARY KEY AUTO_INCREMENT,
        title VARCHAR(255),
        author_id INT,
        CONSTRAINT author_id_fk FOREIGN KEY (author_id) REFERENCES authors(id)
    ) ENGINE=MyISAM;
    DROP TABLE books, authors;

It is not possible to drop a table if another table has foreign keys to it:

Foreign key names must be unique across all tables of all databases <http://stackoverflow.com/questions/13338198/mysql-index-name-and-foreign-key-name-must-be-different-for-different-tables>:

    CREATE TABLE authors (
        id INT PRIMARY KEY AUTO_INCREMENT,
        last_name VARCHAR(255)
    );
    CREATE TABLE books (
        id INT PRIMARY KEY AUTO_INCREMENT,
        title VARCHAR(255),
        author_id INT,
        CONSTRAINT author_id_fk FOREIGN KEY (author_id) REFERENCES authors(id)
    );
    # ERROR: cryptict error message becuase `author_id_fk` is used twice.
    CREATE TABLE books2 (
        id INT PRIMARY KEY AUTO_INCREMENT,
        title VARCHAR(255),
        author_id INT,
        CONSTRAINT author_id_fk FOREIGN KEY (author_id) REFERENCES authors(id)
    );
    DROP TABLE books, authors;

The only way to work around this is to either first drop the `FOREIGN KEY` constraint, or the table with the foreign key.

Drop the table:

    CREATE TABLE authors (
        id INT PRIMARY KEY AUTO_INCREMENT,
        last_name VARCHAR(255)
    );
    CREATE TABLE books (
        id INT PRIMARY KEY AUTO_INCREMENT,
        title VARCHAR(255),
        author_id INT,
        CONSTRAINT author_id_fk FOREIGN KEY (author_id) REFERENCES authors(id)
    );
    # ERROR: books has foreign keys to authors. Must first drop books.
    DROP TABLE authors;
    DROP TABLE books
    DROP TABLE authors;

Remove the constraint:

    CREATE TABLE authors (
        id INT AUTO_INCREMENT,
        last_name VARCHAR(255),
        CONSTRAINT id_pk PRIMARY KEY (id)
    );
    CREATE TABLE books (
        id INT PRIMARY KEY AUTO_INCREMENT,
        title VARCHAR(255),
        author_id INT,
        CONSTRAINT author_id_fk FOREIGN KEY (author_id) REFERENCES authors(id)
    );
    ALTER TABLE books DROP FOREIGN KEY author_id_fk;
    DROP TABLE authors;
    DROP TABLE books;

Engines like InnoDB prevent by default prevent update or delete of primary keys on tables which have foreign keys pointing in. If this is allows, and what should happen is determined by the `FOREIGN KEY` `ON DELETE` and `ON UPDATE` options.

For `InnoDB` as of 5.5 the following options are supported:

-   `NO ACTION` and `RESTRICT` do the same thing and are the default option: deletion attempt leads to an error.

-   `CASCADE`: `DELETE` of referenced author also deletes all books by the author.

-   `SET NULL`: if the author is removed, its book `FOREIGN KEY` is set to `NULL`

        CREATE TABLE authors (
            id INT PRIMARY KEY AUTO_INCREMENT,
            last_name VARCHAR(255)
        );
        CREATE TABLE books (
            id INT PRIMARY KEY AUTO_INCREMENT,
            title VARCHAR(255),
            author_id INT,
            CONSTRAINT author_id_fk FOREIGN KEY (author_id) REFERENCES authors(id)
        );

        INSERT INTO authors (last_name) VALUES ('sheakespeare');
        # Delete works because no book has this author:
        DELETE FROM authors WHERE last_name = 'sheakespeare';

        INSERT INTO authors (last_name) VALUES ('sheakespeare');
        SELECT @id := id FROM authors WHERE last_name = 'sheakespeare' LIMIT 1;
        INSERT INTO books (title, author_id)
            VALUES ('romeo and juliet', @id);
        # ERROR: delete fails because at least one book has this author:
        DELETE FROM authors WHERE last_name = 'sheakespeare';

        ALTER TABLE books DROP FOREIGN KEY author_id_fk;
        ALTER TABLE books ADD CONSTRAINT author_id_fk FOREIGN KEY (author_id) REFERENCES authors(id)
                ON DELETE CASCADE;
        DELETE FROM authors WHERE last_name = 'sheakespeare';
        # No books left
        SELECT * FROM books;

        INSERT INTO authors (last_name) VALUES ('sheakespeare');
        SELECT @id := id FROM authors WHERE last_name = 'sheakespeare' LIMIT 1;
        INSERT INTO books (title, author_id)
            VALUES ('romeo and juliet', @id);
        # ERROR: delete fails because at least one book has this author:
        ALTER TABLE books DROP FOREIGN KEY author_id_fk;
        ALTER TABLE books ADD CONSTRAINT author_id_fk FOREIGN KEY (author_id) REFERENCES authors(id)
                ON DELETE SET NULL;
        DELETE FROM authors WHERE last_name = 'sheakespeare';
        SELECT * FROM books;

        DROP TABLE books, authors;

