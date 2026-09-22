#include "bvh.hpp"
#include "aabb.hpp"
#include "hit.hpp"
#include "interval.hpp"
#include "ray.hpp"
#include "world.hpp"
#include <algorithm>
#include <iterator>
#include <memory>
#include <optional>
#include <utility>
#include <vector>

BvhNode::BvhNode(World &&world) : BvhNode(std::move(world).objects) {}

BvhNode::BvhNode(std::vector<std::unique_ptr<Hittable>> objects)
    : bbox(AABB::empty) {

  for (const auto &object : objects) {
    bbox = bbox.merge(object->bounding_box());
  }

  if (objects.size() == 1) {
    left = std::move(objects[0]);
  } else if (objects.size() == 2) {
    left = std::move(objects[0]);
    right = std::move(objects[1]);
  } else {
    auto axis = bbox.longest_axis();
    auto comparator = box_x_compare;
    if (axis == AABB::Axis::Y) {
      comparator = box_y_compare;
    } else if (axis == AABB::Axis::Z) {
      comparator = box_z_compare;
    }
    std::ranges::sort(objects, comparator);

    auto mid = objects.begin() + (std::ssize(objects) / 2);
    std::vector<std::unique_ptr<Hittable>> left_objects{
        std::make_move_iterator(objects.begin()), std::make_move_iterator(mid)};
    std::vector<std::unique_ptr<Hittable>> right_objects{
        std::make_move_iterator(mid), std::make_move_iterator(objects.end())};

    left = std::make_unique<BvhNode>(std::move(left_objects));
    right = std::make_unique<BvhNode>(std::move(right_objects));
  }
}

AABB BvhNode::bounding_box() const { return bbox; }

std::optional<HitRecord> BvhNode::hit(const Ray &ray, Interval interval) const {
  if (!bbox.hit(ray, interval)) {
    return {};
  }

  std::optional<HitRecord> rec;

  if (left) {
    auto temp_rec = left->hit(ray, interval);
    if (temp_rec.has_value()) {
      interval.max = temp_rec->distance_;
      rec = temp_rec;
    }
  }

  if (right) {
    auto temp_rec = right->hit(ray, interval);
    if (temp_rec.has_value()) {
      interval.max = temp_rec->distance_;
      rec = temp_rec;
    }
  }

  return rec;
}
