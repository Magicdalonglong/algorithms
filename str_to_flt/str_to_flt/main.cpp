#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <climits>
#include <set>

using namespace std;

class Table {
public:
    Table(const string& name, const vector<string>& column_names, const vector<vector<string> > data) : name_(name), column_names_(column_names), data_(data) {}
    
    const string& name() const { return name_; }
    const vector<string>& column_names() const { return column_names_; }
    const vector<vector<string> >& data() const { return data_; }
    
    // Callee will own the returned pointer
    Table* Select(const vector<string>& column_names) const {
        // IMPLEMENT ME
        map<string, int> lookup;
        const vector<string> all_names = this->column_names();
        for(int i=0; i<all_names.size(); ++i){
            lookup[all_names[i]] = i;
        }
        
        //Table* result = new Table("Select", { }, vector<vector<string> >());
        vector<string> line;
        vector<vector<string>> lines;
        for(auto d : this->data() ){
            line.clear();
            for(auto n : column_names){
                if(lookup.count(n)){
                    line.push_back(d[lookup[n]]);
                }
            }
            lines.push_back(line);
        }
        return new Table("Select", column_names, lines);
        //return result;
    }
    
    // Callee will own the returned pointer
    Table* Where(const string& column_name, const string& value) const {
        // IMPLEMENT ME
        int targetPos = -1;
        const vector<string> all_names = this->column_names();
        for(int i=0; i<all_names.size(); ++i){
            if(all_names[i] == column_name){
                targetPos = i;
                break;
            }
        }
        
        vector<vector<string>> lines;
        for(auto & d : this->data() ){
            if(d[targetPos] == value){
                lines.push_back(d);
            }
        }
        return new Table("WhereTable", this->column_names() , lines);
    }
    
    void Print() {
        string output = JoinStringVector(column_names_);
        output += "\n";
        for (size_t row_index = 0; row_index < data_.size(); ++row_index) {
            output += JoinStringVector(data_[row_index]);
            output += "\n";
        }
        cout << output << endl;
    }
    
private:
    string JoinStringVector(const vector<string>& input) {
        string output = "";
        bool has_data = false;
        for (size_t i = 0; i < input.size(); ++i) {
            has_data = true;
            output += input[i];
            output += ", ";
        }
        if (has_data) {
            output = output.substr(0, output.length() - 2);
        }
        return output;
    }
    const string name_;
    const vector<string> column_names_;
    const vector<vector<string> > data_; // only support string type for simplicity
};


class Database {
public:
    Database(map<string, const Table*> table_map) : table_map_(table_map) {}
    ~Database() {
        for(map<string, const Table*>::iterator iterator = table_map_.begin(); iterator != table_map_.end(); ++iterator) {
            delete iterator->second;
        }
    }
    
    const Table* GetTable(const string& table_name) { return table_map_[table_name]; }
    
    void GetAllNames(const Table* left_table, const string& left_table_key_name,
                     const Table* right_table, const string& right_table_key_name,
                     vector<string> & all_names, int & targetLeft, int & targetRight){
        
        string left_name = left_table->name();
        string right_name = right_table->name();
        
        all_names.push_back(left_name+"_"+right_name);
        const vector<string> left_names = left_table->column_names();
        for(int i=0; i<left_names.size(); ++i){
            if(left_names[i] == left_table_key_name){
                targetLeft = i;
            }
            else{
                all_names.push_back(left_name+"."+left_names[i]);
            }
        }
        
        const vector<string> right_names = right_table->column_names();
        for(int i=0; i<right_names.size(); ++i){
            if(right_names[i] == right_table_key_name){
                targetRight = i;
            }
            else{
                all_names.push_back(right_name+"."+right_names[i]);
            }
        }
        
    }
    
    // Callee will own the returned pointer
    Table* InnerJoin(
                     const Table* left_table, const string& left_table_key_name,
                     const Table* right_table, const string& right_table_key_name) {
        
        vector<string> all_names;
        int targetLeft = -1, targetRight = -1;
        
        GetAllNames(left_table, left_table_key_name, right_table, right_table_key_name,
                    all_names, targetLeft, targetRight );
        
        vector<string> line;
        vector<vector<string>> lines;
        //string to_match;
        for(auto & l : left_table->data() ){
            for(auto & r : right_table->data()){
                if(l[targetLeft] == r[targetRight] ){
                    line = l;
                    for(int i=0; i<r.size(); ++i){
                        if(i!=targetRight)
                            line.push_back(r[i]);
                    }
                    lines.push_back(line);
                }
            }
        }
        
        return new Table("InnerJoin", all_names, lines);
    }
    
    // Callee will own the returned pointer
    Table* LeftJoin(
                    const Table* left_table, const string& left_table_key_name,
                    const Table* right_table, const string& right_table_key_name) {
        
        vector<string> all_names;
        int targetLeft = -1, targetRight = -1;
        
        GetAllNames(left_table, left_table_key_name, right_table, right_table_key_name,
                    all_names, targetLeft, targetRight );
        int rightSize = right_table->column_names().size();
        
        vector<string> line;
        vector<vector<string>> lines;
        bool matched = false;
        for(auto & l : left_table->data() ){
            matched = false;
            
            for(auto & r : right_table->data()){
                if(l[targetLeft] == r[targetRight] ){
                    matched = true;
                    line = l;
                    for(int i=0; i<r.size(); ++i){
                        if(i!=targetRight)
                            line.push_back(r[i]);
                    }
                    lines.push_back(line);
                }
            }
            
            if(!matched){
                line = l;
                for(int i=0; i<rightSize-1; ++i){
                    line.push_back("");
                }
                lines.push_back(line);
            }
        }
        
        return new Table("LeftJoin", all_names, lines);
    }
    
    Table* RightJoin(
                     const Table* left_table, const string& left_table_key_name,
                     const Table* right_table, const string& right_table_key_name) {
        
        vector<string> all_names;
        int targetLeft = -1, targetRight = -1;
        
        GetAllNames(left_table, left_table_key_name, right_table, right_table_key_name,
                    all_names, targetLeft, targetRight );
        int leftSize = left_table->column_names().size();
        
        vector<string> line;
        vector<vector<string>> lines;
        bool matched = false;
        for(auto & r : right_table->data() ){
            line.clear();
            matched = false;
            
            for(auto & l : left_table->data()){
                if(l[targetLeft] == r[targetRight] ){
                    matched = true;
                    line = r;
                    for(int i=0; i<leftSize; ++i){
                        if(i!=targetRight)
                            line.push_back(l[i]);
                    }
                    lines.push_back(line);
                }
            }
            
            if(!matched){
                line = r;
                for(int i=0; i<leftSize-1; ++i){
                    line.push_back("");
                }
                lines.push_back(line);
            }
        }
        
        return new Table("RightJoin", all_names, lines);
    }
    
    // Callee will own the returned pointer
    Table* OuterJoin(
                     const Table* left_table, const string& left_table_key_name,
                     const Table* right_table, const string& right_table_key_name) {
        vector<string> all_names;
        int targetLeft = -1, targetRight = -1;
        
        GetAllNames(left_table, left_table_key_name, right_table, right_table_key_name,
                    all_names, targetLeft, targetRight );
        int leftSize = left_table->column_names().size();
        int rightSize = right_table->column_names().size();
        
        vector<string> line;
        vector<vector<string>> lines;
        bool matched = false;
        for(auto & l : left_table->data() ){
            matched = false;
            
            for(auto & r : right_table->data()){
                if(l[targetLeft] == r[targetRight] ){
                    matched = true;
                    line = l;
                    for(int i=0; i<r.size(); ++i){
                        if(i!=targetRight)
                            line.push_back(r[i]);
                    }
                    lines.push_back(line);
                }
            }
            
            if(!matched){
                line = l;
                for(int i=0; i<rightSize-1; ++i){
                    line.push_back("");
                }
                lines.push_back(line);
            }
        }
        //deal with the outer for right
        for(auto & r : right_table->data() ){
            matched = false;
            for(auto & l : left_table->data()){
                if(l[targetLeft] == r[targetRight] ){
                    matched = true;
                    break;
                }
            }
            if(!matched){
                line.clear();
                line.push_back(r[targetRight]);
                for(int i=0; i<leftSize-1; ++i){
                    line.push_back("");
                }
                
                for(int i=0; i<rightSize; ++i){
                    if(i!=targetRight)
                        line.push_back(r[i]);
                }
                lines.push_back(line);
            }
        }
        
        return new Table("Outer", all_names, lines);
    }
    
private:
    map<string, const Table*> table_map_;
};

#ifndef __main__
#define __main__

int main(int argc, char* argv[]) {
    const Table* department_table = new Table(
                                              "departments",
                                              { "id", "name" },
                                              {
                                                  { "0", "engineering" },
                                                  { "1", "finance" }
                                              });
    
    const Table* user_table = new Table(
                                        "users",
                                        { "id", "department_id", "name" },
                                        {
                                            { "0", "0", "Ian" },
                                            { "1", "0", "John" },
                                            { "2", "1", "Eddie" },
                                            { "3", "1", "Mark" },
                                        });
    
    const Table* salary_table = new Table(
                                          "salaries",
                                          { "id", "user_id", "amount" },
                                          {
                                              { "0", "0", "100" },
                                              { "1", "1", "150" },
                                              { "2", "1", "200" },
                                              { "3", "3", "200" },
                                              { "4", "3", "300" },
                                              { "5", "4", "400" },
                                          });
    
    map<string, const Table*> table_map = map<string, const Table*>();
    table_map["departments"] = department_table;
    table_map["users"] = user_table;
    table_map["salaries"] = salary_table;
    Database* db = new Database(table_map);
    
    // should print
    // id, department_id, name
    // 1, 0, John
    {
        Table* filtered_table = db->GetTable("users")->Where("id", "1");
        Table* projected_table = filtered_table->Select({ "id", "department_id", "name" });
        projected_table->Print();
        delete projected_table;
        delete filtered_table;
    }
    
    // should print
    // users.name, departments.name
    // Ian, engineering
    // John, engineering
    {
        Table* table = db->InnerJoin(
                                     db->GetTable("users"),
                                     "department_id",
                                     db->GetTable("departments"),
                                     "id");
        Table* filtered_table = table->Where("departments.name", "engineering");
        Table* projected_table = filtered_table->Select({ "users.name", "departments.name" });
        projected_table->Print();
        delete projected_table;
        delete filtered_table;
        delete table;
    }
    
    // should print
    // users.name, salaries.amount
    // Ian, 100
    // John, 150
    // John, 200
    // Mark, 200
    // Mark, 300
    // Eddie,
    {
        Table* table = db->LeftJoin(
                                    db->GetTable("users"),
                                    "id",
                                    db->GetTable("salaries"),
                                    "user_id");
        Table* projected_table = table->Select({ "users.name", "salaries.amount" });
        projected_table->Print();
        delete projected_table;
        delete table;
    }
    
    // should print
    // users.name, salaries.amount
    // Ian, 100
    // John, 150
    // John, 200
    // Mark, 200
    // Mark, 300
    // , 400
    {
        Table* table = db->RightJoin(
                                     db->GetTable("users"),
                                     "id",
                                     db->GetTable("salaries"),
                                     "user_id");
        Table* projected_table = table->Select({ "users.name", "salaries.amount" });
        projected_table->Print();
        delete projected_table;
        delete table;
    }
    
    // should print
    // users.name, salaries.amount
    // Ian, 100
    // John, 150
    // John, 200
    // Mark, 200
    // Mark, 300
    // Eddie,
    // , 400
    {
        Table* table = db->OuterJoin(
                                     db->GetTable("users"),
                                     "id",
                                     db->GetTable("salaries"),
                                     "user_id");
        Table* projected_table = table->Select({ "users.name", "salaries.amount" });
        projected_table->Print();
        delete projected_table;
        delete table;
    }
    
    delete db;
}

#endif
