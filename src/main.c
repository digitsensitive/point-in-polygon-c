#include <stdio.h>
#include <stdlib.h>  // atof()

struct point {
  float x;
  float y;
};

void command_line_message(struct point p, int is_odd);
float find_smallest_element(float *arr, size_t length);
float find_largest_element(float *arr, size_t length);
int pnpoly(int nvert, float *vertx, float *verty, float testx, float testy);

int main(int argc, char *argv[]) {
  // Check command-line arguments
  if (argc != 3) {
    printf("\n");
    printf("Point in Polygon v0.1:\n");
    printf("----------------------\n");
    printf("Usage: ./pnp 2.0 4.0\n");
    printf("Please pass an x and y float value as the test point.\n");
    printf("Currently it is not supported to pass polygon values.\n");
    printf("\n");
    return 1;
  }

  // Define test point
  struct point test_point = {atof(argv[1]), atof(argv[2])};

  // Set number of crossed polygon edges at the beginning to 0 (= false),
  // meaning it is even (= test point is outside of the polygon)
  int is_number_crossed_edges_odd = 0;

  // Set the x and y values of our polygon
  float vertx[] = {2.0f, 5.0f, 5.0f, 2.0f, 3.0f, 3.0f, 2.0f};
  float verty[] = {2.0f, 3.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f};

  // Get the length of the x and y polygon point arrays
  // Information: The sizeof operator returns size_t as the type
  size_t length_vertx = sizeof(vertx) / sizeof(vertx[0]);
  size_t length_verty = sizeof(verty) / sizeof(verty[0]);

  // Find the smallest and largest x and y values
  float x_min = find_smallest_element(vertx, length_vertx);
  float x_max = find_largest_element(vertx, length_vertx);
  float y_min = find_smallest_element(verty, length_verty);
  float y_max = find_largest_element(verty, length_verty);

  // Perform axis-aligned bounding box (AABB) check
  if (test_point.x < x_min || test_point.x > x_max || test_point.y < y_min ||
      test_point.y > y_max) {
    // The point is outside of the polygon!
    command_line_message(test_point, is_number_crossed_edges_odd);
    return 0;
  }

  // Perform the main point in polygon check
  is_number_crossed_edges_odd =
      pnpoly(length_vertx, vertx, verty, test_point.x, test_point.y);

  // Output the result
  command_line_message(test_point, is_number_crossed_edges_odd);
  return 0;
}

void command_line_message(struct point p, int is_odd) {
  printf("\n");
  printf("Point in Polygon v0.1:\n");
  printf("----------------------\n");
  printf("The test point P(%.2f, %.2f) is ", p.x, p.y);
  printf(is_odd ? "inside" : "outside");
  printf(" the polygon.\n");
  printf("\n");
}

float find_smallest_element(float *arr, size_t length) {
  // Get the first array element
  float min = arr[0];

  // Loop through the array, start with the second element of the array
  for (int i = 1; i < length; i++) {
    if (arr[i] < min) {
      min = arr[i];
    }
  }

  return min;
}

float find_largest_element(float *arr, size_t length) {
  // Get the first array element
  float max = arr[0];

  // Loop through the array, start with the second element of the array
  for (int i = 1; i < length; i++) {
    if (arr[i] > max) {
      max = arr[i];
    }
  }

  return max;
}

int pnpoly(int nvert, float *vertx, float *verty, float testx, float testy) {
  int i, j = 0;
  int is_number_crossed_edges_odd = 0;

  for (i = 0, j = nvert - 1; i < nvert; j = i++) {
    if (((verty[i] > testy) != (verty[j] > testy)) &&
        (testx <
         (vertx[j] - vertx[i]) * (testy - verty[i]) / (verty[j] - verty[i]) +
             vertx[i])) {
      is_number_crossed_edges_odd = !is_number_crossed_edges_odd;
    }
  }
  return is_number_crossed_edges_odd;
}
