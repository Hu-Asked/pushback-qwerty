#pragma once

#include "liblvgl/lvgl.h"
#include "gifclass.hpp"
#include <string>
#include <vector>
#include <unordered_map>
#include <utility>
#include <sstream>
#include <iomanip>
#include <fstream>

namespace hugui { 
    enum AutonType {
        RED,
        BLUE,
        OTHER
    };

    struct Auton {
        std::function<void()> auton;
        std::string auton_name;
        AutonType alliance;

        Auton(std::function<void()> a, std::string name, AutonType type)
            : auton(a), auton_name(name), alliance(type) {}
    };
    
    void initialize_auton_selector(std::vector<Auton>, bool addLogo = true);       
    void add_auton(std::function<void()> auton, 
                    std::string auton_name, AutonType allianceColor);
    void console_print(std::string text, int line);
    void run_selected_auton();

    void update_pos(double x, double y, double theta, int precision = 2);
    void change_auton_event(lv_event_t* e); 
    void change_selected_auton(int index);
    void load_selected_auton();
    void run_selected_auton();

    void add_config_toggle(bool* toggleVarialbe, std::string name);
    void add_config_slider(double* SliderVarialbe, std::string name, int min, int max, int step);

    void create_home_screen(bool addLogo);
    void create_tab_view();

    void show_home_screen(lv_event_t* e);
    void show_tab_view(lv_event_t* e);
    
    lv_obj_t* create_button(lv_obj_t* parent, lv_coord_t x, 
                            lv_coord_t y, lv_coord_t width, 
                            lv_coord_t height, int id, const char* text);
}