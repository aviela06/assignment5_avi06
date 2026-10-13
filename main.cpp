#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "pixel.h"

void average_colors(std::vector<Pixel> &pixel_list) // function to calculate average RGB values
{
    float total_r = 0;
    float total_g = 0;
    float total_b = 0;

    for (int i = 0; i < pixel_list.size(); i++)
    {
        total_r += pixel_list[i].r;
        total_g += pixel_list[i].g;
        total_b += pixel_list[i].b;
    }

    std::cout << "average r = " << total_r / pixel_list.size() << "\n";
    std::cout << "average g = " << total_g / pixel_list.size() << "\n";
    std::cout << "average b = " << total_b / pixel_list.size() << "\n";
}

void flip_vertically(std::vector<Pixel> &pixel_list) // function to flip the image vertically
{
    int x_length = 512;
    int y_length = 256;

    for (int x = 0; x < x_length; x++) // loop going through each column
    {
        for (int y = 0; y < y_length / 2; y++) // loop going through the top half
        {
            // find a pixel and its vertical partner by index
            int top = x * y_length + y;
            int bottom = x * y_length + (y_length - 1 - y);

            // swap the colors between the two pixels
            float temp_r = pixel_list[top].r;
            float temp_g = pixel_list[top].g;
            float temp_b = pixel_list[top].b;

            pixel_list[top].r = pixel_list[bottom].r;
            pixel_list[top].g = pixel_list[bottom].g;
            pixel_list[top].b = pixel_list[bottom].b;

            pixel_list[bottom].r = temp_r;
            pixel_list[bottom].g = temp_g;
            pixel_list[bottom].b = temp_b;
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2) // check that a filename was given
    {
        std::cout << "invalid filename\n";
        return 1; // exit
    }

    std::vector<Pixel> pixel_list; // vector to store all pixels

    std::ifstream file(argv[1]); // open the file from the command line

    if (!file.is_open()) // check the file opened
    {
        std::cout << "could not open file\n";
        return 1; // exit
    }

    // Read the file one line at a time. For each line, use find(',') to locate
    // each comma and substr() to grab the value before it, then chop that part
    // off the front of the line. Repeat for x, y, r, g. The last value (b) is
    // whatever remains. Convert characters to numbers with stoi (ints) and stof (floats).
    std::string line;
    while (std::getline(file, line)) // read each line until the file ends
    {
        int pos; // position of the comma

        // x value
        pos = line.find(',');
        int x = std::stoi(line.substr(0, pos)); // grab text before the comma and convert to int
        line = line.substr(pos + 1); // chop the value and comma off the front

        // y value
        pos = line.find(',');
        int y = std::stoi(line.substr(0, pos));
        line = line.substr(pos + 1);

        // r value
        pos = line.find(',');
        float r = std::stof(line.substr(0, pos));
        line = line.substr(pos + 1);

        // g value
        pos = line.find(',');
        float g = std::stof(line.substr(0, pos));
        line = line.substr(pos + 1);

        // b value
        float b = std::stof(line);

        // fill a Pixel with the parsed values
        Pixel p;
        p.x = x;
        p.y = y;
        p.r = r;
        p.g = g;
        p.b = b;

        pixel_list.push_back(p); // add the pixel to the vector
    }

    file.close(); // close file

    // calculate and print the average r, g, b values
    average_colors(pixel_list);

    // flip the image vertically
    flip_vertically(pixel_list);

    // write the flipped pixels to a new file in the same format
    std::ofstream outfile("flipped.dat"); // open the output file

    for (int i = 0; i < pixel_list.size(); i++) // loop through every pixel
    {
        // write x, y, r, g, b separated by commas
        outfile << pixel_list[i].x << ","
                << pixel_list[i].y << ","
                << pixel_list[i].r << ","
                << pixel_list[i].g << ","
                << pixel_list[i].b << "\n";
    }

    outfile.close(); // close the output file

    return 0;
}
