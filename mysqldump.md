---
title: mysldump
---

CLI utility that allows to easily save a database to a file.

Dump to file, no `USE` instructions, drops existing tables:

    mysqldump -u root "$DB_NAME" > bak.sql
    mysqldump -u root "$DB_NAME" "$TABLE1" "$TABLE2" > bak.sql

Multiple DBMS, creates DBMS with old names, uses them:

    mysqldump -u root --databases "$DB1" "$DB2" > bak.sql

    mysqldump -u root --all-databases > bak.sql

All DBMS, includes `USE` statements.

    -d : no data
    --no-create-info : data only

## Restore database from file

Make sure the DB exists and that you really want to overwrite it!

    PASS=
    mysql -u root -p"$PASS" < bak.sql

    DB=
    DB2=
    PASS=
    mysql -u root -p"$PASS" -e "create database $DB2;"
    mysqldump -u root -p"$PASS" $DB | mysql -u root -p"$PASS" $DB2
