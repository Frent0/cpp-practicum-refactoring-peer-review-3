vector<Person> LoadPersons(string_view db_name, int db_connection_timeout, bool db_allow_exceptions,
    DBLogLevel db_log_level, int min_age, int max_age, string_view name_filter) {
    DBConnector connector(db_allow_exceptions, db_log_level);
    DBHandler db;

    if (db_name.starts_with("tmp."s)) {
        db = connector.ConnectTmp(db_name, db_connection_timeout);
    }
    else {
        db = connector.Connect(db_name, db_connection_timeout);
    }

    if (!db_allow_exceptions && !db.IsOK()) {
        return {};
    }

    string query_str = GenerateQuery(min_age, max_age, name_filter);
    DBQuery query(query_str);

    return LoadPersonsFromDB(db, query);
}

string GenerateQuery(int min_age, int max_age, string_view name_filter) {
    ostringstream query_str;
    query_str << "from Persons "s
        << "select Name, Age "s
        << "where Age between "s << min_age << " and "s << max_age << " "s
        << "and Name like '%"s << DBHandler::Quote(name_filter) << "%'"s;

    return query_str.str();
}

vector<Person> LoadPersonsFromDB(DBHandler& db, const DBQuery& query) {
    vector<Person> persons;
    for (auto [name, age] : db.LoadRows<string, int>(query)) {
        persons.emplace_back(move(name), age);
    }

    return persons;
}
