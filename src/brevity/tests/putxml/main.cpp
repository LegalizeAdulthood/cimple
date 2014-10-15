/*
**==============================================================================
**
** Copyright (c) 2003, 2004, 2005, 2006, Michael Brasher, Karl Schopmeyer
** 
** Permission is hereby granted, free of charge, to any person obtaining a
** copy of this software and associated documentation files (the "Software"),
** to deal in the Software without restriction, including without limitation
** the rights to use, copy, modify, merge, publish, distribute, sublicense,
** and/or sell copies of the Software, and to permit persons to whom the
** Software is furnished to do so, subject to the following conditions:
** 
** The above copyright notice and this permission notice shall be included in
** all copies or substantial portions of the Software.
** 
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
** SOFTWARE.
**
**==============================================================================
*/

#include <brevity/XML_Parser.h>
#include <string>

using namespace cimple;
using namespace std;

class Parser : public XML_Parser
{
public:

    Parser() : _level(0)
    {
    }

    void indent()
    {
        for (size_t i = 0; i < _level; i++)
            printf("  ");
    }

    virtual void handle_start_element(const char* el, const char** attrs)
    {
        indent();
        printf("<%s", el);

        for (; *attrs; attrs += 2)
        {
            printf(" %s=\"%s\"", attrs[0], attrs[1]);
        }

        printf(">\n");
        _level++;
    }

    virtual void handle_end_element(const char* el)
    {
        if (_data.size())
        {
            const char* p = _data.c_str();

            while (isspace(*p))
                p++;

            char* end = (char*)_data.c_str() + _data.size();

            while (end != p && isspace(end[-1]))
                *--end = '\0';

            if (*p)
            {
                indent();
                printf("%s\n", p);
                _data.clear();
            }
        }

        _level--;
        indent();
        printf("</%s>\n", el);
    }

    virtual void handle_character_data(const char* s, int len)
    {
        _data.append(s, len);
    }

private:

    string _data;
    size_t _level;
};

int main(int argc, char** argv)
{
    // Usage:

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        exit(1);
    }

    // Parse:

    Parser parser;

    if (parser.parse_file(argv[1]) != 0)
    {
        printf("%s\n", parser.error_msg().c_str());
    }

    return 0;
}
