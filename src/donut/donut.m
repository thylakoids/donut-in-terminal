syms R1 R2 phi theta A B;

% XYZ
circle = [ R2+R1*cos(theta), R1*sin(theta), 0];
rotation_torus = [ cos(phi) 0 sin(phi); 0 1 0; -sin(phi) 0 cos(phi)];
rotation_A = [ 1 0 0; 0  cos(A) sin(A); 0 -sin(A) cos(A)];
rotation_B = [cos(B) sin(B) 0; -sin(B) cos(B) 0; 0 0 1];

XYZ = circle * rotation_torus * rotation_A * rotation_B;

% luminance, light: [0, 1 , -1]
normal = [cos(theta) sin(theta) 0];
light = [0, 1, -1];
luminance = normal * rotation_torus * rotation_A * rotation_B * light';

% given k1, k2, calculate image plane coordinate (x, y)
% (x,y) = ( k1*X/(Z+K2), k1*Y(X+k2) ) 
%
% k1: z for camera coordinate(image plane)
% k2: Z for world coordinate(3D object)

% map image plane coordinate (x, y) to pixel coordinate (u, v)
%
% zbuffer, framebuffer, int