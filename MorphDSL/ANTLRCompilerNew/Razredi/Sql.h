#pragma once
#include <map>
#include <string>
#include <vector>

class SqlWhere;

class Sql {
public:
    Sql();
    ~Sql();

    void dodajOmejitev(std::string keyword, SqlWhere* omejitev);
    std::vector<SqlWhere*> getOmejtiveZaKeyword(std::string keyword);
    std::vector<std::string> getUporabljeneKeyworde();

private:
    std::map<std::string, std::vector<SqlWhere*>> omejitve;
};

