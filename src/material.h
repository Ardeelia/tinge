#pragma once
#include "camera.h"
#include "math.h"
#include "random.h"

class AbstractMaterial {
  public:
    Vec3 color;
    virtual Vec3 Le(const Ray &wo, Vec3 x) const = 0; // light emitted
    virtual Vec3 Fr(const Ray &wi, const Ray &wo,
                    Vec3 n) const = 0; // light reflected
    virtual Vec3 sample_wi(const Ray &w_o, const Vec3 &n, Random &r) = 0;
};

class MaterialDiffuse : public AbstractMaterial {
  public:
    MaterialDiffuse(const Vec3 &color) { this->color = color; }
    Vec3 Fr(const Ray &wi, const Ray &wo, Vec3 n) const override {
        /*Vec3 return_col = color * dot(wi.direction, n);*/
        return color; // light observed because of reflection
    }
    // as, most of the reflective surfaces do not emit light
    Vec3 Le(const Ray &wi, Vec3 x) const override { return Vec3(0, 0, 0); }

    Vec3 sample_wi(const Ray &w_o, const Vec3 &n, Random &random_gen) override {
        return random_gen.GenerateUniformPointHemisphere(n);
    }
};

class MaterialEmissive : public AbstractMaterial {
  public:
    MaterialEmissive(const Vec3 &color) { this->color = color; }
    // light observed because of emission
    Vec3 Le(const Ray &wi, Vec3 x) const override { return color; }
    // as, most of the emissive surfaces do not reflect
    Vec3 Fr(const Ray &wi, const Ray &wo, Vec3 n) const override {
        return Vec3(0, 0, 0);
    }
    Vec3 sample_wi(const Ray &w_o, const Vec3 &n, Random &random_gen) override {
        return Vec3(0, 0, 0);
    }
};

class MaterialMetallic : public AbstractMaterial {
  public:
    float p;
    MaterialMetallic(const Vec3 &color, float roughness_constant)
        : p(roughness_constant) {
        this->color = color;
    }
    // light observed because of emission
    Vec3 Le(const Ray &wi, Vec3 x) const override { return Vec3(0, 0, 0); }
    // as, most of the emissive surfaces do not reflect
    Vec3 Fr(const Ray &wi, const Ray &wo, Vec3 n) const override {
        return color;
    }
    Vec3 sample_wi(const Ray &w_o, const Vec3 &n, Random &random_gen) override {
        return random_gen.GenerateUniformPointHemisphere(n);
        /*return (w_o.direction + n * 2 * dot(n, w_o.direction)).normalized();*/
    }
};
