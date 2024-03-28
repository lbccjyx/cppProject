#include <iostream>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <thread>
#include <vector>
#include <bitset>    
#include "nlohmann/json.hpp"
#include "socket.h"
#include <string>

#pragma once

using json = nlohmann::json;
static json myCmdDataJson;
void init();