#include <cassert>
#include <cstdio>
#include <cstdlib>
using namespace std;

#include "Testbench.h"


Testbench::Testbench(sc_module_name n)
    : sc_module(n), initiator("initiator"), output_rgb_raw_data_offset(54) {
  SC_THREAD(do_sobel);
}

Testbench::~Testbench() = default;

const float x_input_signal[] = {0.500,   0.525,   0.549,   0.574,   0.598,   0.622,   0.646,   0.670,
                            0.693,   0.715,   0.737,   0.759,   0.780,   0.800,   0.819,   0.838,
                            0.856,   0.873,   0.889,   0.904,   0.918,   0.931,   0.943,   0.954,
                            0.964,   0.972,   0.980,   0.986,   0.991,   0.995,   0.998,   1.000,
                            1.000,   0.999,   0.997,   0.994,   0.989,   0.983,   0.976,   0.968,
                            0.959,   0.949,   0.937,   0.925,   0.911,   0.896,   0.881,   0.864,
                            0.847,   0.829,   0.810,   0.790,   0.769,   0.748,   0.726,   0.704,
                            0.681,   0.658,   0.634,   0.610,   0.586,   0.562,   0.537,   0.512,
                            0.488,   0.463,   0.438,   0.414,   0.390,   0.366,   0.342,   0.319,
                            0.296,   0.274,   0.252,   0.231,   0.210,   0.190,   0.171,   0.153,
                            0.136,   0.119,   0.104,   0.089,   0.075,   0.063,   0.051,   0.041,
                            0.032,   0.024,   0.017,   0.011,   0.006,   0.003,   0.001,   0.000,
                            0.000,   0.002,   0.005,   0.009,   0.014,   0.020,   0.028,   0.036,
                            0.046,   0.057,   0.069,   0.082,   0.096,   0.111,   0.127,   0.144,
                            0.162,   0.181,   0.200,   0.220,   0.241,   0.263,   0.285,   0.307,
                            0.330,   0.354,   0.378,   0.402,   0.426,   0.451,   0.475,   0.500}

void Testbench::do_sobel() {

  word data;
  unsigned char mask[4];
  wait(5 * CLOCK_PERIOD, SC_NS);
  for (int i = 0; i < 64; i++) {
    
    for (int k = 0; k < 3; k++) {
        
        index = a*2-k+1;
        if (index < 0) {
          data[k] = 0;
        } else {
          data[k] = x_input_signal[index];
        }
      }
      data[3] = 0
      
      for (int i = 0; i < 4; i ++){
        mask[i] = 0xff
      }
      
    initiator.write_to_socket(SOBEL_MM_BASE + SOBEL_FILTER_R_ADDR, mask, header, output_rgb_raw_data_offset);
  }
  initiator.write_to_socket(RAM_MM_BASE, mask, header,
                            output_rgb_raw_data_offset);
  initiator.write_to_socket(RAM_MM_BASE + output_rgb_raw_data_offset, mask,
                            target_bitmap, bytes_per_pixel * height * width);
  sc_stop();
}
