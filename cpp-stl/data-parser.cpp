#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cctype>
#include <cmath>
#include <iterator>
#include <sstream>
#include <limits>

struct DataStruct 
{
    char key1;
    std::pair<long long, unsigned long long> key2;
    std::string key3;
};


std::string trim(const std::string& str) 
{
    size_t start = str.find_first_not_of(" \t");
    if (start == std::string::npos)
    {
        return "";
    }
    size_t end = str.find_last_not_of(" \t");
    return str.substr(start, end - start + 1);
}

std::string extractFieldValue(const std::string& content, const std::string& fieldName) 
{
    std::string pattern = ":" + fieldName + " ";
    size_t pos = content.find(pattern);
    if (pos == std::string::npos)
    {
        return "";
    }
    
    pos += pattern.length();  
    

    if (pos >= content.size())
    {
        return "";
    }
    
    char firstChar = content[pos];
    
    if (firstChar == '\'') 
    {

        size_t end = content.find('\'', pos + 1);
        if (end == std::string::npos)
        {
            return "";
        }
        return content.substr(pos, end - pos + 1);
    }
    else if (firstChar == '"') 
    {

        size_t end = content.find('"', pos + 1);
        if (end == std::string::npos)
        {
            return "";
        }
        return content.substr(pos, end - pos + 1);
    }
    else if (firstChar == '(')
    {

        int depth = 1;
        size_t end = pos + 1;
        while (end < content.size() && depth > 0) 
        {
            if (content[end] == '(') depth++;
            if (content[end] == ')') depth--;
            end++;
        }
        return content.substr(pos, end - pos);
    }
    
    return "";
}

bool parseCharValue(const std::string& value, char& result) 
{
    if (value.size() >= 3 && value[0] == '\'' && value[2] == '\'') 
    {
        result = value[1];
        return true;
    }
    return false;
}


bool parseRationalValue(const std::string& value, std::pair<long long, unsigned long long>& result) {
    size_t numStart = value.find("(:N ");
    if (numStart == std::string::npos) return false;
    numStart += 4;  
    
    size_t numEnd = value.find(":D", numStart);
    if (numEnd == std::string::npos) return false;
    
    std::string numStr = trim(value.substr(numStart, numEnd - numStart));
    

    size_t denStart = numEnd + 2;
    size_t denEnd = value.find(":)", denStart);
    if (denEnd == std::string::npos) return false;
    
    std::string denStr = trim(value.substr(denStart, denEnd - denStart));
    
    try {
        result.first = std::stoll(numStr);
        result.second = std::stoull(denStr);
        return result.second != 0;
    } catch (...) {
        return false;
    }
}


bool parseStringValue(const std::string& value, std::string& result)
{
    if (value.size() >= 2 && value[0] == '"' && value.back() == '"') 
    {
        result = value.substr(1, value.size() - 2);
        return true;
    }
    return false;
}



bool parseDataStruct(const std::string& line, DataStruct& ds) 
{
    if (line.size() < 4 || line[0] != '(' || line[1] != ':' ||
        line[line.size() - 2] != ':' || line[line.size() - 1] != ')')
    {
        return false;
    }

    size_t pos1 = line.find(":key1");
    if (pos1 == std::string::npos)
    {
        return false;
    }
    pos1 += 5;

    while (pos1 < line.size() && std::isspace(line[pos1]))
    {
        ++pos1;
    }
    if (pos1 + 2 >= line.size())
    {
        return false;
    }
    ds.key1 = line[pos1 + 1];
    if (line[pos1 + 2] != line[pos1])
    {
        return false;
    }

    size_t pos2 = line.find(":key2");
    if (pos2 == std::string::npos)
    {
        return false;
    }
    pos2 += 5;

    while (pos2 < line.size() && std::isspace(line[pos2]))
    {
        ++pos2;
    }
    if (line.find("(:N", pos2) != pos2)
    {
        return false;
    }
    pos2 += 3;

    while (pos2 < line.size() && std::isspace(line[pos2]))
    {
        ++pos2;
    }

    bool negative = false;
    if (line[pos2] == '-') 
    {
        negative = true;
        ++pos2;
    }

    long long numerator = 0;
    while (pos2 < line.size() && std::isdigit(line[pos2])) 
    {
        numerator = numerator * 10 + (line[pos2] - '0');
        ++pos2;
    }
    if (negative)
    {
        numerator = -numerator;
    }

    while (pos2 < line.size() && std::isspace(line[pos2]))
    {
        ++pos2;
    }
    if (line.find(":D", pos2) != pos2)
    {
        return false;
    }
    pos2 += 2;

    while (pos2 < line.size() && std::isspace(line[pos2]))
    {
        ++pos2;
    }

    unsigned long long denominator = 0;
    while (pos2 < line.size() && std::isdigit(line[pos2])) 
    {
        denominator = denominator * 10 + (line[pos2] - '0');
        ++pos2;
    }

    while (pos2 < line.size() && std::isspace(line[pos2]))
    {
        ++pos2;
    }
    if (line.find(":)", pos2) != pos2)
    {
        return false;
    }

    if (denominator == 0) return false;
    ds.key2 = { numerator, denominator };

    size_t pos3 = line.find(":key3");
    if (pos3 == std::string::npos) return false;
    pos3 += 5;

    while (pos3 < line.size() && std::isspace(line[pos3])) ++pos3;
    if (pos3 >= line.size()) return false;

    char quote = line[pos3];
    ++pos3;

    ds.key3.clear();
    while (pos3 < line.size() && line[pos3] != quote) {
        ds.key3 += line[pos3];
        ++pos3;
    }

    return true;
}


std::istream& operator>>(std::istream& in, DataStruct& ds) 
{
    std::string line;
    
    while (std::getline(in, line))
    {
        if (!line.empty() && line.back() == '\r')
        {
            line.pop_back();
        }
        
        if (line.empty())
        {
            continue;
        }
        
        if (parseDataStruct(line, ds))
        {
            return in;
        }
    }
    
    in.setstate(std::ios::failbit);
    return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& ds) 
{
    out << "(:key1 '" << ds.key1 << "':"
        << "key2 (:N " << ds.key2.first << ":D " << ds.key2.second << ":):"
        << "key3 \"" << ds.key3 << "\":)";
    return out;
}


bool compareDataStruct(const DataStruct& first, const DataStruct& second)
{
    if (first.key1 != second.key1)
    {
        return first.key1 < second.key1;
    }
    double first_val = static_cast<double>(first.key2.first) / static_cast<double>(first.key2.second);
    double second_val = static_cast<double>(second.key2.first) / static_cast<double>(second.key2.second);
    double epsilon = std::numeric_limits<double>::epsilon();
    if (std::abs(first_val - second_val) > epsilon)
    {
        return first_val < second_val;
    }
    return first.key3.length() < second.key3.length();
}



int main() 
{
    std::vector<DataStruct> data;

    std::copy(std::istream_iterator<DataStruct>(std::cin),
        std::istream_iterator<DataStruct>(),
        std::back_inserter(data));

    std::sort(data.begin(), data.end(), compareDataStruct);

    std::copy(data.begin(), data.end(),
        std::ostream_iterator<DataStruct>(std::cout, "\n"));

    return 0;
}