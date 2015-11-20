//
//  CsvParser.h
//  MatchPuzzleRPGT
//
//

#pragma once

#include <vector>
#include <string>
using namespace  std;

namespace CsvParser {
    
    class Row
    {
    public:
        Row() { }
        ~Row() { }
        
        void push_back(const string& value) { m_values.push_back(value); }
        void setHeader(const vector<string>* header) { m_header = header; }
        
    public:
        
        unsigned int size() const { return m_values.size(); }
        
        string& operator[](unsigned int key)
        {
            if (key < size()) return m_values[key];
            throw "can't return this value (doesn't exist)";
        }
        
        string& operator[](const string& key)
        {
            vector<string>::const_iterator it;
            int pos = 0;
            for (it = (*m_header).begin(); it != (*m_header).end(); it++) {
                if (key == *it) return m_values[pos];
                pos++;
            }
            throw "can't return this value (doesn't exist)";
        }
        
    private:
        const vector<string>* m_header;
        vector<string> m_values;
    };
    
    
    class Csv
    {
    public:
        Csv(const string& filename);
        ~Csv();
        
        void Parse(const string& filename);
        
        const string& getErrorInfo() const { return m_strErrorInfo; }
        
        vector<string> getHeader() const { return m_header; }

        unsigned int getRowCount() const { return m_content.size(); }
        
        unsigned int getColumnCount() const { return m_header.size(); }
        
        Row& operator[](unsigned int key);
        
        static void Write(const string& filename, vector<vector<string>>& rows);
        
    private:
        void Load(const string& filename, string& Data);
        void setHeader();
        
        private :
        vector<Row> m_content;
        vector<string> m_header;
        string m_strErrorInfo;
    };
}