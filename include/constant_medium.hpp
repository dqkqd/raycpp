#include "hit.hpp"
#include "material.hpp"
#include "texture.hpp"

class ConstantMedium : public Hittable {
public:
  ConstantMedium(std::unique_ptr<Hittable> boundary, double density,
                 std::shared_ptr<Texture> tex);
  ConstantMedium(std::unique_ptr<Hittable> boundary, double density,
                 Color albedo);

  [[nodiscard]] std::optional<HitRecord> hit(const Ray &ray,
                                             Interval interval) const override;

  [[nodiscard]] AABB bounding_box() const override;

private:
  std::unique_ptr<Hittable> boundary_;
  std::shared_ptr<Material> phase_function_;
  double neg_inv_density;
};
