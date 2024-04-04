#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<string> parseFields(const string& input)
{
    vector<string> fields;
    string field;
    bool inQuotesOne = false;
    bool inQuotesTwo = false;
    bool escaped = false;

    for (char c : input)
    {
        if ((inQuotesOne == false) && (inQuotesTwo == false))
        {
            if (c == '\'')
            {
                if (!field.empty())
                {
                    fields.push_back(field);
                    field.clear();
                }
                inQuotesOne = true;
            }
            else if (c == '\"')
            {
                if (!field.empty())
                {
                    fields.push_back(field);
                    field.clear();
                }
                inQuotesTwo = true;
            }
            else if (c == ' ')
            {
                if (!field.empty())
                {
                    fields.push_back(field);
                    field.clear();
                }
            }
            else
            {
                field += c;
            }

        }

        else if ((inQuotesOne == true) || (inQuotesTwo == true))
        {
            if ((c == '\'') && (inQuotesOne == true) && (escaped == false))
            {
                inQuotesOne = false;
                if (!field.empty())
                {
                    fields.push_back(field);
                    field.clear();
                }
            }
            else if ((c == '\"') && (inQuotesTwo == true) && (escaped == false))
            {
                inQuotesTwo = false;
                if (!field.empty())
                {
                    fields.push_back(field);
                    field.clear();
                }
            }
            else if ((c == '\\') && (escaped == false))
            {
                escaped = true;
            }
            else if (((c == '\\') || (c == '\'') || (c == '\"')) && (escaped == true))
            {
                escaped = false;
                field += c;
            }
            else
            {
                field += c;
            }
        }
    }
    if (!field.empty())
    {
        fields.push_back(field);
        field.clear();
    }

    return fields;
}

int main() {

    setlocale(LC_ALL, "Russian");

    string input;
    cout << "Введите строку текста: ";
    getline(cin, input);

    vector<string> result = parseFields(input);

    cout << "Результат парсинга:" << endl;
    for (const auto& field : result) {
        cout << field << endl;
    }

    return 0;
}
