---
title: Getting started
---

Before doing any tests, create a test user and a test database.

    mysql -u root -h localhost -p -e "
        CREATE USER 'a'@'localhost' IDENTIFIED BY 'a';
        CREATE DATABASE a;
        GRANT ALL ON a.* TO 'a'@'localhost';
    "

You can now put into your `.bashrc`:

    alias myt='mysql -u a -h localhost -pa a'

and now you can type `myt` to safely run any tests.
