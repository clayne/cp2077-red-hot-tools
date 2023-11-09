#pragma once

namespace Red
{
enum FrustumResult
{
    Outside = 0,
    Intersecting = 1,
    Inside = 2,
};

struct Frustum
{
    static constexpr auto NumberOfPlanes = 6;

    FrustumResult Test(const Box& aBox)
    {
        auto result = FrustumResult::Inside;

        const auto& boxMin = *reinterpret_cast<const __m128*>(&aBox.Min);
        const auto& boxMax = *reinterpret_cast<const __m128*>(&aBox.Max);

        for (auto i = 0; i < NumberOfPlanes; ++i)
        {
            auto v24 = _mm_mul_ps(_mm_or_ps(_mm_and_ps(masks[i], boxMax), _mm_andnot_ps(masks[i], boxMin)), planes[i]);
            auto v25 = _mm_mul_ps(_mm_or_ps(_mm_andnot_ps(masks[i], boxMax), _mm_and_ps(masks[i], boxMin)), planes[i]);
            auto v26 = _mm_hadd_ps(v24, v24);
            auto v27 = _mm_hadd_ps(v25, v25);
            auto v28 = _mm_hadd_ps(v27, v27);

            if (_mm_movemask_ps(_mm_xor_ps(_mm_hadd_ps(v26, v26), v28)))
            {
                result = FrustumResult::Intersecting;
            }
            else if (_mm_movemask_ps(v28))
            {
                result = FrustumResult::Outside;
                break;
            }
        }

        return result;
    }

    __m128 planes[NumberOfPlanes]{};
    __m128 masks[NumberOfPlanes]{};
};
}

namespace Raw::CameraSystem
{
constexpr auto GetCameraFrustum = Core::RawVFunc<
    /* addr = */ 0x250,
    /* type = */ void (Red::gameICameraSystem::*)(Red::Frustum& aOut)>();
}