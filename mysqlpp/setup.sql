CREATE USER 'mysqlpp_user'@'localhost' IDENTIFIED BY 'pass';
CREATE DATABASE mysqlpp_db;
GRANT ALL ON mysqlpp_db.* TO 'mysqlpp_user'@'localhost';
