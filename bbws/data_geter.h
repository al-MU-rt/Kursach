#pragma once

#include<atlstr.h>
#include<string>



std::string get_value_photo(std::string name, int id);

std::string get_value_html(std::string name, int id);

std::string get_value_set(std::string name);

std::string get_all_sets( int id);

bool get_save_by_id(int num, int& result);

bool get_id_by_num(int num, int& result);

bool get_num_by_id(int num, int& result);

bool get_device_by_num(int num, CString& result);