#include <iostream>
#include "Controller.h"

int main() {
    auto controller = Controller(); //Create an instance of the Controller class
    controller.run();               //Call the run() function on the controller object

    return EXIT_SUCCESS;
}
