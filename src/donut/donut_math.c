#include <math.h>
#include <stdio.h>

const int screen_width = 30;
const int screen_height = 30;
const float theta_spacing = 0.07;
const float phi_spacing = 0.02;
const float pi = 3.14;

const float R1 = 1;
const float R2 = 2;
const float K2 = 5;
// Calculate K1 based on screen size: the maximum x-distance occurs
// roughly at the edge of the torus, which is at x=R1+R2, z=0.  we
// want that to be displaced 3/8ths of the width of the screen, which
// is 3/4th of the way from the center to the side of the screen.
// screen_width*3/8 = K1*(R1+R2)/(K2+0)
// screen_width*K2*3/(8*(R1+R2)) = K1
const float K1 = screen_width * K2 * 3 / (8 * (R1 + R2));
const float K1_h = screen_height * K2 * 3 / (8 * (R1 + R2));
const int size = screen_width * screen_height;

void render_frame(float A, float B) {
  // precompute sines and cosines of A and B
  float cosA = cos(A), sinA = sin(A);
  float cosB = cos(B), sinB = sin(B);

  char output[size];
  float zbuffer[size];
  for (int i = 0; i < size; i++) {
    output[i] = ' ';
    zbuffer[i] = 0;
  }

  // theta goes around the cross-sectional circle of a torus
  for (float theta = 0; theta < 2 * pi; theta += theta_spacing) {
    // precompute sines and cosines of theta
    float costheta = cos(theta), sintheta = sin(theta);

    // phi goes around the center of revolution of a torus
    for (float phi = 0; phi < 2 * pi; phi += phi_spacing) {
      // precompute sines and cosines of phi
      float cosphi = cos(phi), sinphi = sin(phi);

      // the x,y coordinate of the circle, before revolving (factored
      // out of the above equations)
      float circlex = R2 + R1 * costheta;
      float circley = R1 * sintheta;

      // final 3D (x,y,z) coordinate after rotations, directly from
      // our math above
      float x = circlex * (cosB * cosphi + sinA * sinB * sinphi) -
                circley * cosA * sinB;
      float y = circlex * (sinB * cosphi - sinA * cosB * sinphi) +
                circley * cosA * cosB;
      float z = K2 + cosA * circlex * sinphi + circley * sinA;
      float ooz = 1 / z; // "one over z"

      // x and y projection.  note that y is negated here, because y
      // goes up in 3D space but down on 2D displays.
      int xp = (int)(screen_width / 2 + K1 * ooz * x);
      int yp = (int)(screen_height / 2 - K1_h * ooz * y);

      // calculate luminance.  ugly, but correct.
      float L = cosphi * costheta * sinB - cosA * costheta * sinphi -
                sinA * sintheta +
                cosB * (cosA * sintheta - costheta * sinA * sinphi);
      // L ranges from -sqrt(2) to +sqrt(2).  If it's < 0, the surface
      // is pointing away from us, so we won't bother trying to plot it.
      int pos = yp * screen_width + xp;
      if (xp > 0 && xp < screen_width && yp > 0 && yp < screen_height) {
        // test against the z-buffer.  larger 1/z means the pixel is
        // closer to the viewer than what's already plotted.
        if (ooz > zbuffer[pos]) {
          zbuffer[pos] = ooz;
          int luminance_index = L * 8;
          // luminance_index is now in the range 0..11 (8*sqrt(2) = 11.3)
          // now we lookup the character corresponding to the
          // luminance and plot it in our output:
          output[pos] =
              ".,-~:;=!*#$@"[luminance_index > 0 ? luminance_index : 0];
        }
      }
    }
  }

  // now, dump output[] to the screen.
  // bring cursor to "home" location, in just about any currently-used
  // terminal emulation mode
  printf("\x1b[H");
  for (int i = 0; i < size + 1; i++) {
    putchar(i % screen_width ? output[i] : 10);
  }
  printf("\x1b[23A");
}

int main() {
  float A = 0;
  float B = 0;
  while (1) {
    render_frame(A, B);
    A += 0.0007;
    B += 0.00035;
  }
  return 0;
}
