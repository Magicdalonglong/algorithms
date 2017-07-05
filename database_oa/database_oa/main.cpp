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
        vector<string> col_name = column_names;
        map<string, int> col_index;
        for(int i = 0; i < column_names_.size(); i++) {
            col_index[column_names_[i]] = i;
        }
        
        vector<vector<string>> row_data;
        for ( auto row : data_){
            row_data.emplace_back(vector<string> {});
            for(auto c : col_name) {
                row_data.back().emplace_back(row[col_index[c]]);
            }
        }
        return new Table("Select Table", col_name, row_data);
        //return result;
        
    }
    
    // Callee will own the returned pointer
    Table* Where(const string& column_name, const string& value) const {
        // IMPLEMENT ME
        int pos = -1;
        for (int i = 0; i < column_names_.size(); i++ ) {
            if(column_names_[i] == column_name) {
                pos = i;
                break;
            }
        }
        vector<vector<string>> row_data;
        for(auto data : data_) {
            if(pos == -1 || data[pos] == value) {
                row_data.push_back(data);
            }
        }
        return new Table("Where Table", column_names_, row_data);
    }
    
    void Print() {
        cout<<endl;
        for(int i = 0; i < column_names_.size(); i++) {
            i == column_names_.size() - 1 ? cout<<column_names_[i] : cout<<column_names_[i] <<", ";
        }
        cout<<endl;
        for(int row = 0; row < data_.size(); row++){
            for(int i = 0; i < data_[row].size(); i++) {
                i == data_[row].size() - 1 ? cout<<data_[row][i] : cout<<data_[row][i] <<", ";
            }
            cout<<endl;
        }
    }
    
private:
    
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
    
    void GetColAndIndex(const Table* left_table, const string& left_table_key_name,
                  const Table* right_table, const string& right_table_key_name, int& left_pos, int& right_pos, vector<string> & col_name) {
        for(auto name : left_table -> column_names()) {
            col_name.emplace_back(left_table ->name() + "." + name);
        }
        for(auto name : right_table -> column_names()) {
            col_name.emplace_back(right_table ->name() + "." + name);
        }
        
        
        for(int i = 0; i < left_table -> column_names().size(); i++) {
            if(left_table -> column_names()[i] == left_table_key_name) {
                left_pos = i;
                break;
            }
        }
        for(int i = 0; i < right_table -> column_names().size(); i++) {
            if(right_table -> column_names()[i] == right_table_key_name) {
                right_pos = i;
                break;
            }
        }
    }
    // Callee will own the returned pointer
    Table* InnerJoin(
                     const Table* left_table, const string& left_table_key_name,
                     const Table* right_table, const string& right_table_key_name) {
        
        vector<string> col_name;
        int left_pos = -1, right_pos = -1;
        GetColAndIndex(left_table, left_table_key_name, right_table, right_table_key_name, left_pos, right_pos, col_name);
        
        vector<vector<string>> row_data;
        for(auto left_row : left_table -> data()){
            for(auto right_row : right_table -> data()){
                if(left_row[left_pos] == right_row[right_pos]) {
                    row_data.emplace_back(left_row);
                    row_data.back().insert(row_data.back().end(), right_row.begin(), right_row.end());
                }
            }
        }
        
        return new Table("InnerJoin", col_name, row_data);
    }
    
    // Callee will own the returned pointer
    Table* LeftJoin(
                    const Table* left_table, const string& left_table_key_name,
                    const Table* right_table, const string& right_table_key_name) {
        
        vector<string> col_name;
        int left_pos = -1, right_pos = -1;
        GetColAndIndex(left_table, left_table_key_name, right_table, right_table_key_name, left_pos, right_pos, col_name);
        vector<vector<string>> row_data;
        for(auto left_row : left_table -> data()){
            vector<int> pos;
            for(int i = 0; i < right_table -> data().size(); i++) {
                if(left_row[left_pos] == right_table -> data()[i][right_pos]) {
                    pos.emplace_back(i);
                }
            }
            if(pos.size()) {
                for(auto p : pos) {
                    row_data.emplace_back(left_row);
                    row_data.back().insert(row_data.back().end(), right_table -> data()[p].begin(), right_table -> data()[p].end());
                }
            }else {
                row_data.emplace_back(left_row);
                row_data.back().insert(row_data.back().end(), right_table -> column_names().size(), "");
            }
        }
        return new Table("LeftJoin", col_name, row_data);
    }
    
    Table* RightJoin(
                     const Table* left_table, const string& left_table_key_name,
                     const Table* right_table, const string& right_table_key_name) {
        
        vector<string> col_name;
        int left_pos = -1, right_pos = -1;
        GetColAndIndex(left_table, left_table_key_name, right_table, right_table_key_name, left_pos, right_pos, col_name);
        
        vector<vector<string>> row_data;
        for(auto right_row : right_table -> data()){
            vector<int> pos;
            for(int i = 0; i < left_table -> data().size(); i++) {
                if(right_row[right_pos] == left_table -> data()[i][left_pos]) {
                    pos.emplace_back(i);
                }
            }
            if(pos.size()) {
                for(auto p : pos) {
                    row_data.emplace_back(left_table -> data()[p]);
                    row_data.back().insert(row_data.back().end(), right_row.begin(), right_row.end());
                }
            }else {
                row_data.emplace_back(vector<string> {});
                row_data.back().insert(row_data.back().end(), left_table -> column_names().size(), "");
                row_data.back().insert(row_data.back().end(), right_row.begin(), right_row.end());
            }
        }
        return new Table("RightJoin", col_name, row_data);
    }
    
    // Callee will own the returned pointer
    Table* OuterJoin(
                     const Table* left_table, const string& left_table_key_name,
                     const Table* right_table, const string& right_table_key_name) {
        
        vector<string> col_name;
        int left_pos = -1, right_pos = -1;
        GetColAndIndex(left_table, left_table_key_name, right_table, right_table_key_name, left_pos, right_pos, col_name);
        
        
        set<int> left_index, right_index;
        for(int i = 0; i < left_table -> data().size(); i++) {
            left_index.insert(i);
        }
        
        for(int i = 0; i < right_table -> data().size(); i++) {
            right_index.insert(i);
        }
        
        
        vector<vector<string>> row_data;
        for(int i = 0; i < left_table -> data().size(); i++) {
            for(int j = 0; j < right_table -> data().size(); j++) {
                if(left_table -> data()[i][left_pos] == right_table -> data()[j][right_pos]) {
                    left_index.erase(i);
                    right_index.erase(j);
                    row_data.push_back(left_table -> data()[i]);
                    row_data.back().insert(row_data.back().end(), right_table -> data()[j].begin(), right_table -> data()[j].end());
                }
            }
        }
        for(auto i : left_index) {
            row_data.emplace_back(left_table -> data()[i]);
            row_data.back().insert(row_data.back().end(), right_table -> column_names().size(), "");
        }
        
        for(auto i : right_index) {
            row_data.emplace_back(vector<string> {});
            row_data.back().insert(row_data.back().end(), left_table -> column_names().size(), "");
            row_data.back().insert(row_data.back().end(), right_table ->data()[i].begin(), right_table ->data()[i].end());
        }
        
        return new Table("OuterJoin", col_name, row_data);

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
        projected_table -> Print();
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
