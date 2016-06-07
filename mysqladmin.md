---
title: mysqladmin
---

CLI utility that simplifies MySQL administration tasks.

`-u`, `-p` and `-h` have analogous usage to that of the `mysql` command.

Login as user `root` and change its password:

    mysqladmin -u root -h localhost -p password

`password` here is a `mysqladmin` subcommand. It seems that it is not possible to change the password of another user with this method. Use `SET PASSWORD` or `UPDATE PASSWORD` for that instead.
