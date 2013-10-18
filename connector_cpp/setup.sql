CREATE USER 'conn_cpp_user'@'localhost' IDENTIFIED BY 'pass';
CREATE DATABASE conn_cpp_db;
GRANT ALL ON conn_cpp_db.* TO 'conn_cpp_user'@'localhost';
