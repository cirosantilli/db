---
title: PostgreSQL
layout: default
permalink: postgresql/
---

CLI executable name: `psql`

#get started

<http://stackoverflow.com/questions/1471571/how-to-configure-postgresql-for-the-first-time>

First you must have an OS user (not a database user) named `postgres`.

This OS user usually is created when PostgreSQL is installed.
The PostgreSQL superuser `postgres` should always exist on all installations.

The first login can only be done by an user with that exact username.

Under the following configuration file:

    sudo vim /etc/postgresql/9.1/main/pg_hba.conf

Check that the authentication method for user `postgres` is `peer`.
If this is not the case, make it so, and restart the server with:

    sudo service postgresql restart

or:

    sudo /etc/init.d/postgresql restart

depending on your system's init method.

`peer` means that if the OS user named `XXX` is logged in, then he can
automatically login on the database if `XXX` exists on the database,
without having a database password.

Now that user `postgres` can login with the `peer` method, do it:

    sudo -u postgres psql template1

`template1` is the name of a database which always exists on new installations.
If not given, login may fail, since it tries to use a default database with the same
name as the username `postgres`.

Once logged in, set the `postgres` password:

    ALTER USER postgres with encrypted password 'xxxxxxx';

and exit.

Change the login method for user `postgres` to `md5`.
`md5` means that a PostgreSQL password is required.

Now using the `postgres` PostgreSQL user create a user for yourself as superuser

    createuser -U postgres -deElPrs <my_username>

You can choose your login method for yourself: `peer` or `md5`. `md5` is safer,
but you will have to type more every time. Your login method is probably being controlled
by the user `all` in the config file.

#role

In PostgreSQL, an user is commonly called a *role*.
