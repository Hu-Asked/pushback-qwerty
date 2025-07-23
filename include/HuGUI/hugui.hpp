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
    
    // Functions for internal use in the library
    void add_auton(std::function<void()> auton, 
                std::string auton_name, AutonType allianceColor);
    void change_auton_event(lv_event_t* e); 
    void change_selected_auton(int index);
    void load_selected_auton();
    void run_selected_auton();     

    void create_home_screen(bool addLogo);
    void create_tab_view();

    void show_home_screen(lv_event_t* e);
    void show_tab_view(lv_event_t* e);
    
    lv_obj_t* create_button(lv_obj_t* parent, lv_coord_t x, 
                            lv_coord_t y, lv_coord_t width, 
                            lv_coord_t height, int id, const char* text);

    /**
     * @brief Initalizes the UI on the brain with an auton selector.
     * 
     * @param autons A vector of Auton objects to populate the selector with.
     * @param addLogo If true, adds the gif named "logo.gif" to the home screen from the microSD
     */
    void initialize_auton_selector(std::vector<Auton> autons, bool addLogo = true);      
   
    /**
     * @brief Prints string to the console
     * 
     * @param text The text to print
     * @param line A line from 0 - 8 where the text will be printed
     */
    void console_print(std::string text, int line);

    /**
     * @brief Runs the auton selected via the auton selected
     */
    void run_selected_auton();

    /**
     * @brief Updates the odometry position to be displayed on the brain
     * 
     * @param x The x position of the robot
     * @param y The y position of the robot
     * @param theta The heading of the robot in degrees
     * @param precision the number of decimal places to display
     */
    void update_pos(double x, double y, double theta, int precision = 2);

    /**
     * @brief Adds a toggle button to the config tab
     * 
     * @param toggleVariable A pointer to a boolean variable that will be toggled when the button is pressed
     * @param name The name of the toggle button
     */
    void add_config_toggle(bool* toggleVariable, std::string name);

    /**
     * @brief WIP do not use
     * 
     * @param SliderVariable A pointer to a double variable that will be updated when the slider is moved
     * @param name The name of the slider
     * @param min The minimum value of the slider
     * @param max The maximum value of the slider
     * @param step The step size of the slider
     */
    void add_config_slider(double* SliderVariable, std::string name, int min, int max, int step);
}