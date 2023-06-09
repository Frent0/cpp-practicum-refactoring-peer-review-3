void CheckDateTimeValidity(const DateTime& dt) {
    CheckRange(dt.year, 1, 9999, "year");
    CheckRange(dt.month, 1, 12, "month");
    CheckRange(dt.day, 1, GetMonthLength(dt), "day");
    CheckRange(dt.hour, 0, 23, "hour");
    CheckRange(dt.minute, 0, 59, "minute");
    CheckRange(dt.second, 0, 59, "second");
}

void CheckRange(int value, int min_value, int max_value, const std::string& field_name) {
    if (value < min_value) {
        throw std::domain_error(field_name + " is too small");
    }
    if (value > max_value) {
        throw std::domain_error(field_name + " is too big");
    }
}

int GetMonthLength(const DateTime& dt) {
    const bool is_leap_year = (dt.year % 4 == 0) && !(dt.year % 100 == 0 && dt.year % 400 != 0);
    const std::array<int, 12> month_lengths = { 31, 28 + is_leap_year, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    return month_lengths[dt.month - 1];
}
