#include "moneyapp.h"

MoneyApp::MoneyApp()
{
    std::string currentDir = QDir::current().absolutePath().toStdString();

    _logs_path = currentDir + "/LOGS.txt";
    _target_path = currentDir + "/target.txt";

    std::cout<< "cur dir: " << currentDir<<std::endl;
}

MoneyApp& MoneyApp::instance() {
    static MoneyApp instance;
    return instance;
}

bool MoneyApp::read_target()
{
    std::ifstream inFile(_target_path);
    if (!inFile.is_open()) {

        std::cerr << "Failed to open the file for reading. " << _target_path << std::endl;
        return false;
    }

    std::string temp;
    std::getline(inFile, temp);

    if (temp.empty())
    {
        return false;
    }


    _target = stod(temp);
    return true;
}

void MoneyApp::add_constr()
{
    this->addToLogs();
}

StateCode MoneyApp::add(const std::string& str) {
    if (_target <= 0) { return StateCode::INVALID_TARGET; }
    else if (str.empty()) { return StateCode::INVALID_INPUT; }

    try
    {
        double temp = std::stod(str);
        _current = temp;
    }
    catch (const std::exception& e)
    {
        return StateCode::INVALID_INPUT;
    }

    return _current > 0 ? this->addToLogs() : StateCode::INVALID_INPUT;
}

const double MoneyApp::view_target() const
{
    return _target;
}

bool MoneyApp::load_logs() {
    std::ifstream inFile(_logs_path);
    if (!inFile.is_open()) {
        std::cerr << "Failed to open the file for reading." << std::endl;
        return false;
    }

    std::string value;
    int j = 1;

    while (inFile >> value) {
        if (j % 5 == 0) {
            _logs_sum += std::stod(value);
        }
        j++;
    }

    inFile.close();

    std::cout<<"logs: "<<this->_logs_sum<<'\n';
    std::cout<<"dir: "<<this->_logs_path<<'\n';

    return _logs_sum == 0;
}

int MoneyApp::getIncreasePercent()
{
    int temp = (_logs_sum /_target) * 100;
    return (temp > 100) ? 100 : temp ;
}

void MoneyApp::clear_labelTxt()
{
    _labelTxt.clear();
}

QString& MoneyApp::get_labelTxt()
{
    return _labelTxt;
}

void MoneyApp::change_target(const double newTarget, const bool del)
{
    _target = (newTarget < 1) ? _target : newTarget;

    if (del)
    {
        std::ofstream inFile(_logs_path);
        inFile.close();
        this->_logs_sum =0;
    }

    std::ofstream inFile(_target_path);
    if (!inFile.is_open()) {
        std::cerr << "Failed to open the file for reading." << std::endl;
        return;
    }

    inFile << _target;
    inFile.close();
}

void MoneyApp::set_date(const QDate& date)
{
    _date = date;
}

StateCode MoneyApp::addToLogs()
{
    std::ifstream inFile(_logs_path);
    if (!inFile.is_open()) {
        std::cerr << "Failed to open the file for reading." << std::endl;
        return StateCode::LOGS_FAILED;
    }

    std::stringstream content;


    if (_current > 0) { content << _date.toString().toStdString() << ": " << _current << std::endl; }




    content << inFile.rdbuf();
    inFile.close();

    /*
    if(content.str().empty())
    {
        this->_labelTxt = "No Logs\n";
        return StateCode::CTOR_CREATE;
    }
    */

    std::ofstream outFile(_logs_path);
    if (!outFile.is_open()) {
        std::cerr << "Failed to open the file for writing." << std::endl;
        return StateCode::LOGS_FAILED;
    }

    outFile << content.str();
    outFile.close();
    _logs_sum += _current;

    unsigned short int j = 0;
    std::string line;


    //std::cout<< "contenbt: "<< content.str()<<std::endl;
    // std::getline(content, line,'\n');

    std::getline(content, line,'\n');
    //  std::cerr << "line before: " << line << std::endl;
    if(line.empty())
    {
        _labelTxt.append(QString::fromStdString(content.str())).append("\n");
        return StateCode::SUCCESS;
    }
    ++j;
      _labelTxt.append(QString::fromStdString(line)).append("\n");



    while (std::getline(content, line,'\n') && j < 10)
    {
      //  std::cerr << "line in while: " << line << std::endl;

        _labelTxt.append(QString::fromStdString(line)).append("\n");
        ++j;
    }


    return StateCode::SUCCESS;
}
