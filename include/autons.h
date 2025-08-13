#include "lemlib/api.hpp" // IWYU pragma: keep

#pragma once

extern std::vector<std::tuple<std::string, void(*)()>> autons;
extern void autonLeft();
extern void autonRight();
extern void autonSkills();
