#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iomanip>

#include <mysql++.h>

int main(int argc, char *argv[])
{
    std::string db_name = "mysqlpp_db";
    std::string table_name = "t";
    std::vector<std::string> values{"0", "1", "2"};
    mysqlpp::Connection conn(false);
    mysqlpp::Query query(&conn);
    if (conn.connect(db_name.c_str(), "localhost", "mysqlpp_user", "pass")) {
        query.exec("USE " + db_name);
        query.exec("CREATE TABLE IF NOT EXISTS " + table_name + " (c INT)");
        query.exec("INSERT INTO " + table_name + " VALUES (0), (1), (2)");
        mysqlpp::Query query = conn.query();
        if (mysqlpp::StoreQueryResult res = query.store("SELECT * FROM " + table_name)) {
            mysqlpp::StoreQueryResult::const_iterator it;
            decltype(values)::iterator val_it;
            for (it = res.begin(), val_it = values.begin();
                    it != res.end(); ++it, ++val_it) {
                mysqlpp::Row row = *it;
                assert(row[0] == *val_it);
            }
        }
        else {
            std::cerr << "Failed to get item list: " << query.error() << std::endl;
            return EXIT_FAILURE;
        }
        query.exec("DROP TABLE " + table_name);
        return EXIT_SUCCESS;
    }
    else {
        std::cerr << "DB connection failed: " << conn.error() << std::endl;
        return EXIT_FAILURE;
    }
}
