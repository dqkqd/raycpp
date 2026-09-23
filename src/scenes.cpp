#include "scenes.hpp"
#include "bvh.hpp"
#include "camera.hpp"
#include "color.hpp"
#include "constant_medium.hpp"
#include "material.hpp"
#include "point.hpp"
#include "quad.hpp"
#include "sphere.hpp"
#include "texture.hpp"
#include "transform.hpp"
#include "utils.hpp"
#include "vec3.hpp"
#include "world.hpp"
#include <memory>
#include <utility>

int bouncing_spheres() {
  auto cam =
      Camera::init(16.0 / 9.0, 400, 100, 50, 20, Point{.x = 13, .y = 2, .z = 3},
                   {.x = 0, .y = 0, .z = 0}, {.x = 0, .y = 1, .z = 0}, 0.6,
                   10.0, {.r = 0.7, .g = 0.8, .b = 1.});

  auto world = World();

  auto checker = std::make_shared<CheckerTexture>(
      0.32, Color{.r = .2, .g = .3, .b = .1}, Color{.r = .9, .g = .9, .b = .9});

  auto material_ground = std::make_shared<Lambertian>(checker);
  world.add(std::make_unique<Sphere>(Point{.x = 0, .y = -1000, .z = 0}, 1000,
                                     material_ground));

  for (int a = -11; a < 11; a++) {
    for (int b = -11; b < 11; b++) {
      auto choose_mat = random_double();
      const Point center{.x = a + (0.9 * random_double()),
                         .y = 0.2,
                         .z = b + (0.9 * random_double())};
      if ((center - Point{.x = 4, .y = 0.2, .z = 0}).length() > 0.9) {
        if (choose_mat < 0.8) {
          auto albedo = Vec3::random() * Vec3::random();
          auto mat = std::make_shared<Lambertian>(
              Color{.r = albedo.x, .g = albedo.y, .b = albedo.z});
          auto center2 =
              center + Vec3{.x = 0, .y = random_double(0, 0.5), .z = 0};
          world.add(std::make_unique<Sphere>(center, center2, 0.2, mat));
        } else if (choose_mat < 0.95) {
          auto albedo = Vec3::random(0.5, 1);
          auto fuzz = random_double(0, 0.5);
          auto mat = std::make_shared<Metal>(
              Color{.r = albedo.x, .g = albedo.y, .b = albedo.z}, fuzz);
          world.add(std::make_unique<Sphere>(center, 0.2, mat));
        } else {
          auto mat = std::make_shared<Dielectrics>(1.5);
          world.add(std::make_unique<Sphere>(center, 0.2, mat));
        }
      }
    }
  }

  auto mat1 = std::make_shared<Dielectrics>(1.5);
  world.add(std::make_unique<Sphere>(Point{.x = 0, .y = 1, .z = 0}, 1, mat1));

  auto mat2 = std::make_shared<Lambertian>(Color{.r = 0.4, .g = 0.2, .b = 0.1});
  world.add(std::make_unique<Sphere>(Point{.x = -4, .y = 1, .z = 0}, 1, mat2));

  auto mat3 = std::make_shared<Metal>(Color{.r = 0.7, .g = 0.6, .b = 0.5}, 0);
  world.add(std::make_unique<Sphere>(Point{.x = 4, .y = 1, .z = 0}, 1, mat3));

  auto world_tree = BvhNode(std::move(world));
  if (!cam.render(world_tree)) {
    return 1;
  }

  return 0;
}

int checker_spheres() {
  auto cam =
      Camera::init(16.0 / 9.0, 400, 100, 50, 20, Point{.x = 13, .y = 2, .z = 3},
                   {.x = 0, .y = 0, .z = 0}, {.x = 0, .y = 1, .z = 0}, 0.6,
                   10.0, {.r = 0.7, .g = 0.8, .b = 1.});

  auto world = World();

  auto checker = std::make_shared<CheckerTexture>(
      0.32, Color{.r = .2, .g = .3, .b = .1}, Color{.r = .9, .g = .9, .b = .9});

  world.add(std::make_unique<Sphere>(Point{.x = 0, .y = -10, .z = 0}, 10,
                                     std::make_shared<Lambertian>(checker)));
  world.add(std::make_unique<Sphere>(Point{.x = 0, .y = 10, .z = 0}, 10,
                                     std::make_shared<Lambertian>(checker)));

  auto world_tree = BvhNode(std::move(world));
  if (!cam.render(world_tree)) {
    return 1;
  }

  return 0;
}

int earth() {
  auto cam =
      Camera::init(16.0 / 9.0, 400, 100, 50, 20, Point{.x = 0, .y = 0, .z = 12},
                   {.x = 0, .y = 0, .z = 0}, {.x = 0, .y = 1, .z = 0}, 0, 10.0,
                   {.r = 0.7, .g = 0.8, .b = 1.});

  auto world = World();

  auto earth_texture = std::make_shared<ImageTexture>("images/earthmap.jpg");
  auto earth_surface = std::make_shared<Lambertian>(earth_texture);
  auto globe =
      std::make_unique<Sphere>(Point{.x = 0, .y = 0, .z = 0}, 2, earth_surface);

  world.add(std::move(globe));
  if (!cam.render(world)) {
    return 1;
  }

  return 0;
};

int perlin_spheres() {
  auto cam =
      Camera::init(16.0 / 9.0, 400, 100, 50, 20, Point{.x = 13, .y = 2, .z = 3},
                   {.x = 0, .y = 0, .z = 0}, {.x = 0, .y = 1, .z = 0}, 0, 10.0,
                   {.r = 0.7, .g = 0.8, .b = 1.});

  auto world = World();

  auto pertext = std::make_shared<NoiseTexture>(4);
  world.add(std::make_unique<Sphere>(Point{.x = 0, .y = -1000, .z = 0}, 1000,
                                     std::make_shared<Lambertian>(pertext)));
  world.add(std::make_unique<Sphere>(Point{.x = 0, .y = 2, .z = 0}, 2,
                                     std::make_shared<Lambertian>(pertext)));

  auto world_tree = BvhNode(std::move(world));
  if (!cam.render(world_tree)) {
    return 1;
  }

  return 0;
};

int quads() {
  auto cam = Camera::init(1.0, 400, 100, 50, 80, Point{.x = 0, .y = 0, .z = 9},
                          {.x = 0, .y = 0, .z = 0}, {.x = 0, .y = 1, .z = 0}, 0,
                          10.0, {.r = 0.7, .g = 0.8, .b = 1.});

  auto world = World();

  auto left_red = std::make_shared<Lambertian>(Color{.r = 1, .g = .2, .b = .2});
  auto back_green =
      std::make_shared<Lambertian>(Color{.r = .2, .g = 1, .b = .2});
  auto right_blue =
      std::make_shared<Lambertian>(Color{.r = .2, .g = .2, .b = 1});
  auto upper_orange =
      std::make_shared<Lambertian>(Color{.r = 1, .g = .5, .b = 0});
  auto lower_teal =
      std::make_shared<Lambertian>(Color{.r = .2, .g = .8, .b = .8});

  world.add(std::make_unique<Quad>(Point{.x = -3, .y = -2, .z = 5},
                                   Vec3{.x = 0, .y = 0, .z = -4},
                                   Vec3{.x = 0, .y = 4, .z = 0}, left_red));
  world.add(std::make_unique<Quad>(Point{.x = -2, .y = -2, .z = 0},
                                   Vec3{.x = 4, .y = 0, .z = 0},
                                   Vec3{.x = 0, .y = 4, .z = 0}, back_green));
  world.add(std::make_unique<Quad>(Point{.x = 3, .y = -2, .z = 1},
                                   Vec3{.x = 0, .y = 0, .z = 4},
                                   Vec3{.x = 0, .y = 4, .z = 0}, right_blue));
  world.add(std::make_unique<Quad>(Point{.x = -2, .y = 3, .z = 1},
                                   Vec3{.x = 4, .y = 0, .z = 0},
                                   Vec3{.x = 0, .y = 0, .z = 4}, upper_orange));
  world.add(std::make_unique<Quad>(Point{.x = -2, .y = -3, .z = 5},
                                   Vec3{.x = 4, .y = 0, .z = 0},
                                   Vec3{.x = 0, .y = 0, .z = -4}, lower_teal));

  auto world_tree = BvhNode(std::move(world));
  if (!cam.render(world_tree)) {
    return 1;
  }

  return 0;
};

int simple_light() {
  auto cam =
      Camera::init(16.0 / 9.0, 400, 100, 50, 20, Point{.x = 26, .y = 3, .z = 6},
                   {.x = 0, .y = 2, .z = 0}, {.x = 0, .y = 1, .z = 0}, 0, 10.0,
                   {.r = 0, .g = 0, .b = 0});

  auto world = World();

  auto pertext = std::make_shared<NoiseTexture>(4);
  world.add(std::make_unique<Sphere>(Point{.x = 0, .y = -1000, .z = 0}, 1000,
                                     std::make_shared<Lambertian>(pertext)));
  world.add(std::make_unique<Sphere>(Point{.x = 0, .y = 2, .z = 0}, 2,
                                     std::make_shared<Lambertian>(pertext)));

  auto difflight =
      std::make_shared<DiffuseLight>(Color{.r = 4, .g = 4, .b = 4});
  world.add(std::make_unique<Quad>(Point{.x = 3, .y = 1, .z = -2},
                                   Vec3{.x = 2, .y = 0, .z = 0},
                                   Vec3{.x = 0, .y = 2, .z = 0}, difflight));

  auto world_tree = BvhNode(std::move(world));
  if (!cam.render(world_tree)) {
    return 1;
  }

  return 0;
}

int cornell_box() {
  auto cam =
      Camera::init(1.0, 600, 100, 50, 40, Point{.x = 278, .y = 278, .z = -800},
                   {.x = 278, .y = 278, .z = 0}, {.x = 0, .y = 1, .z = 0}, 0,
                   10.0, {.r = 0, .g = 0, .b = 0});

  auto world = World();

  auto red = std::make_shared<Lambertian>(Color{.r = .65, .g = .05, .b = .05});
  auto white =
      std::make_shared<Lambertian>(Color{.r = .73, .g = .73, .b = .73});
  auto green =
      std::make_shared<Lambertian>(Color{.r = .12, .g = .45, .b = .15});
  auto light = std::make_shared<DiffuseLight>(Color{.r = 15, .g = 15, .b = 15});

  world.add(std::make_unique<Quad>(Point{.x = 555, .y = 0, .z = 0},
                                   Vec3{.x = 0, .y = 555, .z = 0},
                                   Vec3{.x = 0, .y = 0, .z = 555}, green));
  world.add(std::make_unique<Quad>(Point{.x = 0, .y = 0, .z = 0},
                                   Vec3{.x = 0, .y = 555, .z = 0},
                                   Vec3{.x = 0, .y = 0, .z = 555}, red));
  world.add(std::make_unique<Quad>(Point{.x = 343, .y = 554, .z = 332},
                                   Vec3{.x = -130, .y = 0, .z = 0},
                                   Vec3{.x = 0, .y = 0, .z = -105}, light));
  world.add(std::make_unique<Quad>(Point{.x = 0, .y = 0, .z = 0},
                                   Vec3{.x = 555, .y = 0, .z = 0},
                                   Vec3{.x = 0, .y = 0, .z = 555}, white));
  world.add(std::make_unique<Quad>(Point{.x = 555, .y = 555, .z = 555},
                                   Vec3{.x = -555, .y = 0, .z = 0},
                                   Vec3{.x = 0, .y = 0, .z = -555}, white));
  world.add(std::make_unique<Quad>(Point{.x = 0, .y = 0, .z = 555},
                                   Vec3{.x = 555, .y = 0, .z = 0},
                                   Vec3{.x = 0, .y = 555, .z = 0}, white));

  std::unique_ptr<Hittable> box1 =
      box({.x = 0, .y = 0, .z = 0}, {.x = 165, .y = 330, .z = 165}, white);
  box1 = std::make_unique<RotateY>(std::move(box1), 15);
  box1 = std::make_unique<Translate>(std::move(box1),
                                     Vec3{.x = 265, .y = 0, .z = 295});
  world.add(std::move(box1));

  std::unique_ptr<Hittable> box2 =
      box({.x = 0, .y = 0, .z = 0}, {.x = 165, .y = 165, .z = 165}, white);
  box2 = std::make_unique<RotateY>(std::move(box2), -18);
  box2 = std::make_unique<Translate>(std::move(box2),
                                     Vec3{.x = 130, .y = 0, .z = 65});
  world.add(std::move(box2));

  auto world_tree = BvhNode(std::move(world));
  if (!cam.render(world_tree)) {
    return 1;
  }

  return 0;
}

int cornell_smoke() {
  auto cam =
      Camera::init(1.0, 600, 100, 50, 40, Point{.x = 278, .y = 278, .z = -800},
                   {.x = 278, .y = 278, .z = 0}, {.x = 0, .y = 1, .z = 0}, 0,
                   10.0, {.r = 0, .g = 0, .b = 0});

  auto world = World();

  auto red = std::make_shared<Lambertian>(Color{.r = .65, .g = .05, .b = .05});
  auto white =
      std::make_shared<Lambertian>(Color{.r = .73, .g = .73, .b = .73});
  auto green =
      std::make_shared<Lambertian>(Color{.r = .12, .g = .45, .b = .15});
  auto light = std::make_shared<DiffuseLight>(Color{.r = 7, .g = 7, .b = 7});

  world.add(std::make_unique<Quad>(Point{.x = 555, .y = 0, .z = 0},
                                   Vec3{.x = 0, .y = 555, .z = 0},
                                   Vec3{.x = 0, .y = 0, .z = 555}, green));
  world.add(std::make_unique<Quad>(Point{.x = 0, .y = 0, .z = 0},
                                   Vec3{.x = 0, .y = 555, .z = 0},
                                   Vec3{.x = 0, .y = 0, .z = 555}, red));
  world.add(std::make_unique<Quad>(Point{.x = 113, .y = 554, .z = 127},
                                   Vec3{.x = 330, .y = 0, .z = 0},
                                   Vec3{.x = 0, .y = 0, .z = 305}, light));
  world.add(std::make_unique<Quad>(Point{.x = 0, .y = 0, .z = 0},
                                   Vec3{.x = 555, .y = 0, .z = 0},
                                   Vec3{.x = 0, .y = 0, .z = 555}, white));
  world.add(std::make_unique<Quad>(Point{.x = 555, .y = 555, .z = 555},
                                   Vec3{.x = -555, .y = 0, .z = 0},
                                   Vec3{.x = 0, .y = 0, .z = -555}, white));
  world.add(std::make_unique<Quad>(Point{.x = 0, .y = 0, .z = 555},
                                   Vec3{.x = 555, .y = 0, .z = 0},
                                   Vec3{.x = 0, .y = 555, .z = 0}, white));

  std::unique_ptr<Hittable> box1 =
      box({.x = 0, .y = 0, .z = 0}, {.x = 165, .y = 330, .z = 165}, white);
  box1 = std::make_unique<RotateY>(std::move(box1), 15);
  box1 = std::make_unique<Translate>(std::move(box1),
                                     Vec3{.x = 265, .y = 0, .z = 295});
  box1 = std::make_unique<ConstantMedium>(std::move(box1), 0.01,
                                          Color{.r = 0, .g = 0, .b = 0});
  world.add(std::move(box1));

  std::unique_ptr<Hittable> box2 =
      box({.x = 0, .y = 0, .z = 0}, {.x = 165, .y = 165, .z = 165}, white);
  box2 = std::make_unique<RotateY>(std::move(box2), -18);
  box2 = std::make_unique<Translate>(std::move(box2),
                                     Vec3{.x = 130, .y = 0, .z = 65});
  box2 = std::make_unique<ConstantMedium>(std::move(box2), 0.01,
                                          Color{.r = 1, .g = 1, .b = 1});
  world.add(std::move(box2));

  auto world_tree = BvhNode(std::move(world));
  if (!cam.render(world_tree)) {
    return 1;
  }

  return 0;
}
