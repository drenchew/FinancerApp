#ifndef MONEYAPP_H
#define MONEYAPP_H

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <QDate>
#include <QString>
#include <QDir>
#include <QDebug>
#include <future>  // Include for std::future

enum class StateCode
{
    INVALID_INPUT,
    INVALID_TARGET,
    LOGS_FAILED,
    SUCCESS,
    CTOR_CREATE,
};

class MoneyApp
{
public:
    MoneyApp();
    MoneyApp(const MoneyApp&) = delete;
    MoneyApp& operator=(const MoneyApp&) = delete;

    static MoneyApp& instance();

    bool read_target();
    void add_constr();
    StateCode add(const std::string& str);
    const double view_target() const;
    bool load_logs();
    int getIncreasePercent();
    void clear_labelTxt();
    QString& get_labelTxt();
    void change_target(const double newTarget, const bool del = false);
    void set_date(const QDate& date);
    const double viewLogsSum(){return this->_logs_sum;}

private:
    StateCode addToLogs();

    QString _labelTxt;
    QDate _date;

    std::string _logs_path;
    std::string _target_path;

    double _target = 0;
    double _current = 0;
    double _logs_sum = 0;
};

#endif // MONEYAPP_H
